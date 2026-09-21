#include "SceneGamePlay.h"

// Init(): 게임 리소스 로드 및 초기화

int SceneGamePlay::Init()
{
    // 랜덤 난수 기준값 초기화
    srand((unsigned int)time(NULL));

    // 기존 텍스처 정리
    Destroy();

    // 배경
    m_txBackground = g2_TextureLoad("Texture/InGame_BG.png");

    // 가위바위보 기본 버튼
    m_txScissors = g2_TextureLoad("Texture/Btn_Scissors.png");
    m_txRock = g2_TextureLoad("Texture/Btn_Rock.png");
    m_txPaper = g2_TextureLoad("Texture/Btn_Paper.png");

    // Hover(눌림) 버튼
    m_txScissorsHover = g2_TextureLoad("Texture/Btn_Scissors_Hover.png");
    m_txRockHover = g2_TextureLoad("Texture/Btn_Rock_Hover.png");
    m_txPaperHover = g2_TextureLoad("Texture/Btn_Paper_Hover.png");

    // 카운트숫자 로드
    m_txCount1 = g2_TextureLoad("Texture/Count_1.png");
    m_txCount2 = g2_TextureLoad("Texture/Count_2.png");
    m_txCount3 = g2_TextureLoad("Texture/Count_3.png");

    // 말 로드
    m_txPiece = g2_TextureLoad("Texture/Piece.png");

    ResetGame();

    return 0;
}


// Destroy(): 사용한 텍스처 메모리 해제

int SceneGamePlay::Destroy()
{
    if (m_txBackground >= 0) { g2_TextureRelease(m_txBackground);    m_txBackground = -1; }

    if (m_txScissors >= 0) { g2_TextureRelease(m_txScissors);      m_txScissors = -1; }
    if (m_txRock >= 0) { g2_TextureRelease(m_txRock);          m_txRock = -1; }
    if (m_txPaper >= 0) { g2_TextureRelease(m_txPaper);         m_txPaper = -1; }

    if (m_txScissorsHover >= 0) { g2_TextureRelease(m_txScissorsHover); m_txScissorsHover = -1; }
    if (m_txRockHover >= 0) { g2_TextureRelease(m_txRockHover);     m_txRockHover = -1; }
    if (m_txPaperHover >= 0) { g2_TextureRelease(m_txPaperHover);    m_txPaperHover = -1; }

    if (m_txCount1 >= 0) { g2_TextureRelease(m_txCount1);        m_txCount1 = -1; }
    if (m_txCount2 >= 0) { g2_TextureRelease(m_txCount2);        m_txCount2 = -1; }
    if (m_txCount3 >= 0) { g2_TextureRelease(m_txCount3);        m_txCount3 = -1; }

    if (m_txPiece >= 0) { g2_TextureRelease(m_txPiece);         m_txPiece = -1; }

    return 0;
}


// ResetGame(): 게임 시작 상태로 리셋

void SceneGamePlay::ResetGame()
{
    // 말 위치 초기화 (영희: 5번, 철수: 6번)
    m_younghee.Init(5);
    m_cheolsoo.Init(6);

    m_isEvaluating = false;
    m_isGameOver = false;

    m_countdown = 0;
    m_countdownTimer = 0;

    m_playerChoice = RPSChoice::NONE;

    m_prevKey1 = false;
    m_prevKey2 = false;
    m_prevKey3 = false;
}


// IsKeyPressed(): 키보드가 눌렸는지 확인

bool SceneGamePlay::IsKeyPressed(int key)
{
    SHORT state = GetAsyncKeyState(key);
    return (state & 0x8000) != 0;
}

// StartTurn(): 키 입력 시 3초 타이머 시작

void SceneGamePlay::StartTurn(RPSChoice playerChoice)
{
    if (m_isEvaluating || m_isGameOver)
    {
        return;
    }

    m_playerChoice = playerChoice;

    m_isEvaluating = true;
    m_countdown = 3;       // 3초부터 카운트다운
    m_countdownTimer = 0;
}

// FinishTurn(): rand() 함수 사용해 승패 판정 후 말 이동

void SceneGamePlay::FinishTurn()
{
    int aiChoice = rand() % 3;
    int playerChoice = (int)m_playerChoice; // 0: 가위, 1: 바위, 2: 보

    // 승패 판정
    if (playerChoice == aiChoice)
    {
    }
    // [플레이어 승리 조건] (가위>보, 바위>가위, 보>바위)
    else if ((playerChoice == 0 && aiChoice == 2) ||
        (playerChoice == 1 && aiChoice == 0) ||
        (playerChoice == 2 && aiChoice == 1))
    {
        // 영희/철수 말이 모두 오른쪽(+1)으로 이동
        m_younghee.Move(1);
        m_cheolsoo.Move(1);
    }
    // [플레이어 패배 조건]
    else
    {
        // 영희/철수 말이 모두 왼쪽(-1)으로 밀려남
        m_younghee.Move(-1);
        m_cheolsoo.Move(-1);
    }

    // 승리/패배 조건 체크 (영희는 1번 돌 밑으로, 철수의 경유는 10번 돌을 넘어갈 때)
    if (m_younghee.GetPosition() < 1 || m_cheolsoo.GetPosition() > 10)
    {
        m_isGameOver = true;
    }

    m_isEvaluating = false; 
}

// Update(): 입력 및 타이머 업데이트

int SceneGamePlay::Update(const KEYCODE* keys)
{
    if (IsKeyPressed(VK_ESCAPE))
    {
        return 0; // ESC 누르면 종료
    }

    // 게임 오버 상태일 때 Enter 누르면 재시작
    if (m_isGameOver)
    {
        if (IsKeyPressed(VK_RETURN))
        {
            ResetGame();
            return 1;
        }
        return 1;
    }

    // 키 누름 체크
    bool key1 = IsKeyPressed('1');
    bool key2 = IsKeyPressed('2');
    bool key3 = IsKeyPressed('3');

    bool newKey1 = key1 && !m_prevKey1;
    bool newKey2 = key2 && !m_prevKey2;
    bool newKey3 = key3 && !m_prevKey3;

    m_prevKey1 = key1;
    m_prevKey2 = key2;
    m_prevKey3 = key3;

    // 카운트다운 아닐 때만 키 입력 받기
    if (!m_isEvaluating)
    {
        if (newKey1) { StartTurn(RPSChoice::SCISSORS); } // 1번: 가위
        else if (newKey2) { StartTurn(RPSChoice::ROCK); }     // 2번: 바위
        else if (newKey3) { StartTurn(RPSChoice::PAPER); }    // 3번: 보
    }
    else
    {
        // 1초 60프레임 단위 카운트다운
        m_countdownTimer++;

        if (m_countdownTimer >= 60)
        {
            m_countdownTimer = 0;
            m_countdown--; // 3 -> 2 -> 1

            if (m_countdown <= 0)
            {
                FinishTurn(); // 0초 되면 승패 판정
            }
        }
    }

    return 1;
}

// Render(): 화면 출력

int SceneGamePlay::Render()
{
    g2_DrawAlphaOption(255);

    RECT rFullScreen = { 0, 0, 800, 600 };

    // 배경
    if (m_txBackground >= 0)
    {
        g2_Draw2D(m_txBackground, &rFullScreen);
    }

    //가위/바위/보 버튼 출력 --> 키 누르면 hover 작ㅇ동
    bool key1 = IsKeyPressed('1');
    bool key2 = IsKeyPressed('2');
    bool key3 = IsKeyPressed('3');

    if (key1 && m_txScissorsHover >= 0)      
        g2_Draw2D(m_txScissorsHover, &rFullScreen);
    else if (m_txScissors >= 0)               
        g2_Draw2D(m_txScissors, &rFullScreen);

    if (key2 && m_txRockHover >= 0)          
        g2_Draw2D(m_txRockHover, &rFullScreen);
    else if (m_txRock >= 0)                   
        g2_Draw2D(m_txRock, &rFullScreen);

    if (key3 && m_txPaperHover >= 0)         
        g2_Draw2D(m_txPaperHover, &rFullScreen);
    else if (m_txPaper >= 0)                  
        g2_Draw2D(m_txPaper, &rFullScreen);

    // 카운트
    if (m_isEvaluating)
    {
        if (m_countdown == 3 && m_txCount3 >= 0)      
            g2_Draw2D(m_txCount3, &rFullScreen);
        else if (m_countdown == 2 && m_txCount2 >= 0) 
            g2_Draw2D(m_txCount2, &rFullScreen);
        else if (m_countdown == 1 && m_txCount1 >= 0) 
            g2_Draw2D(m_txCount1, &rFullScreen);
    }

    // 말 (Piece) 
    if (m_txPiece >= 0)
    {
        int youngheePos = m_younghee.GetPosition();
        int cheolsooPos = m_cheolsoo.GetPosition();

        if (youngheePos >= 1 && youngheePos <= 10)
        {
            int x = m_stoneX[youngheePos - 1];
            RECT rPieceY = { x - 20, m_stoneY - 45, x + 20, m_stoneY + 5 };
            g2_Draw2D(m_txPiece, &rPieceY);
        }

        if (cheolsooPos >= 1 && cheolsooPos <= 10)
        {
            int x = m_stoneX[cheolsooPos - 1];
            RECT rPieceC = { x - 20, m_stoneY - 45, x + 20, m_stoneY + 5 };
            g2_Draw2D(m_txPiece, &rPieceC);
        }
    }

    return 0;
}