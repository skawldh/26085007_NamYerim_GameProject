#include "SceneGamePlay.h"
#include <ctime>
#include <cstdlib>

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

    // 컴퓨터 카드 이미지 로드
    m_txComScissors = g2_TextureLoad("Texture/Com_Scissors.png");
    m_txComRock = g2_TextureLoad("Texture/Com_Rock.png");
    m_txComPaper = g2_TextureLoad("Texture/Com_Paper.png");

    m_rtScissors = { 20, 470, 260, 570 };
    m_rtRock = { 270, 470, 510, 570 };
    m_rtPaper = { 520, 470, 760, 570 };

    m_isLButtonDown = false;
    m_prevLButtonDown = false;

    // 카운트숫자 로드
    m_txCount1 = g2_TextureLoad("Texture/Count_1.png");
    m_txCount2 = g2_TextureLoad("Texture/Count_2.png");
    m_txCount3 = g2_TextureLoad("Texture/Count_3.png");

    // 말 로드
    m_txPiece = g2_TextureLoad("Texture/Piece.png");

   // 승패 프로필 이미지 로드 
    m_txYoungheeWin = g2_TextureLoad("Texture/Profile_YoungheeWin.png");
    m_txCheolsooWin = g2_TextureLoad("Texture/Profile_CheolsooWin.png");


    ResetGame();

    return 0;
}

// Destroy(): 사용한 텍스처 메모리 해제
int SceneGamePlay::Destroy()
{
    if (m_txBackground >= 0) 
    { 
        g2_TextureRelease(m_txBackground); 
        m_txBackground = -1; 
    }
    if (m_txScissors >= 0) 
    { 
        g2_TextureRelease(m_txScissors); 
        m_txScissors = -1; 
    }
    if (m_txRock >= 0) 
    { 
        g2_TextureRelease(m_txRock); 
        m_txRock = -1; 
    }

    if (m_txPaper >= 0) 
    { 
        g2_TextureRelease(m_txPaper); 
        m_txPaper = -1; 
    }
    if (m_txScissorsHover >= 0) 
    { 
        g2_TextureRelease(m_txScissorsHover); 
        m_txScissorsHover = -1; 
    }
    if (m_txRockHover >= 0) 
    { 
        g2_TextureRelease(m_txRockHover); 
        m_txRockHover = -1; 
    }
    if (m_txPaperHover >= 0) 
    { 
        g2_TextureRelease(m_txPaperHover); 
        m_txPaperHover = -1; 
    }
    if (m_txComScissors >= 0) 
    { 
        g2_TextureRelease(m_txComScissors); 
        m_txComScissors = -1; 
    }
    if (m_txComRock >= 0) 
    { 
        g2_TextureRelease(m_txComRock); 
        m_txComRock = -1; 
    }

    if (m_txComPaper >= 0) 
    { 
        g2_TextureRelease(m_txComPaper); 
        m_txComPaper = -1; 
    }
    if (m_txCount1 >= 0) 
    { 
        g2_TextureRelease(m_txCount1); 
        m_txCount1 = -1; 
    }
    if (m_txCount2 >= 0) 
    { 
        g2_TextureRelease(m_txCount2);
        m_txCount2 = -1; 
    }
    if (m_txCount3 >= 0)
    { 
        g2_TextureRelease(m_txCount3); 
        m_txCount3 = -1; 
    }
    if (m_txPiece >= 0) 
    { 
        g2_TextureRelease(m_txPiece); 
        m_txPiece = -1; 
    }
 
    if (m_txYoungheeWin >= 0) 
    { 
        g2_TextureRelease(m_txYoungheeWin); 
        m_txYoungheeWin = -1; 
    }
    if (m_txCheolsooWin >= 0) 
    { 
        g2_TextureRelease(m_txCheolsooWin); 
        m_txCheolsooWin = -1; 
    }

    return 0;
}

// ResetGame(): 게임 시작 상태로 리셋
void SceneGamePlay::ResetGame()
{
    m_younghee.Init(5); // 5번 위치에서 시작

    m_isEvaluating = false;
    m_isGameOver = false;

    m_countdown = 0;
    m_countdownTimer = 0;
    m_aiChoice = -1;

    m_playerChoice = RPSChoice::NONE;

    m_turnWinner = 0;  
    m_moved = false;   


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

// StartTurn(): 카운트다운 시작
void SceneGamePlay::StartTurn(RPSChoice playerChoice)
{
    if (m_isEvaluating || m_isGameOver) return;

    m_playerChoice = playerChoice;
    m_isEvaluating = true;
    m_countdown = 3;
    m_aiChoice = -1;

    m_turnWinner = 0;   // 이번 턴 승자 초기화
    m_moved = false;    // 말 이동 여부 초기화

    m_turnStartTime = GetTickCount64();
    // 턴 시작 시각 기록 (실제 시간 기준으로 잡지 않으면 컴퓨터 사양에 따라서 속도가 달라지니까 그냥 실제 시간으로 1초 1초 1초 1.2초 순으로 잡기로 함)
}

// FinishTurn(): 승패 판정 후 말 이동 (프로필 표시 구간에서 딱 한 번 호출)
void SceneGamePlay::FinishTurn()
{
    int pChoice = static_cast<int>(m_playerChoice);

    if (pChoice == m_aiChoice)
    {
        m_turnWinner = 0;       // 무승부: 이동 없음
    }
    else if ((pChoice == 0 && m_aiChoice == 2) ||
        (pChoice == 1 && m_aiChoice == 0) ||
        (pChoice == 2 && m_aiChoice == 1))
    {
        m_turnWinner = 1;       // 플레이어(영희) 승 -> 오른쪽
        m_younghee.Move(1);
    }
    else
    {
        m_turnWinner = 2;       // 컴퓨터(철수) 승 -> 왼쪽
        m_younghee.Move(-1);
    }

    // 양쪽 끝(0번 아웃 or 10번 아웃) 도달 시 게임 오버
    int curPos = m_younghee.GetPosition();
    if (curPos <= 0 || curPos >= 10)
    {
        m_isGameOver = true;
    }
}

// Update(): 입력 및 1초 단위 타이머 처리
int SceneGamePlay::Update(const KEYCODE* keys)
{
    if (IsKeyPressed(VK_ESCAPE)) return 0; // 메인 화면으로

    // 게임 오버 상태: Enter를 누르면 결과 화면으로 전환
    if (m_isGameOver)
    {
        if (IsKeyPressed(VK_RETURN))
        {
            return 2; // 결과화면
        }
        return 1; // 결과 화면 가기 전까지 플레이 씬 유지
    }

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(GetActiveWindow(), &pt);
    m_mousePos = pt;

    bool isLDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    bool isLClicked = isLDown && !m_prevLButtonDown;
    m_prevLButtonDown = isLDown;

    // 입력 받기
    if (!m_isEvaluating)
    {
        if (IsKeyPressed('1') || (isLClicked && PtInRect(&m_rtScissors, m_mousePos)))
            StartTurn(RPSChoice::SCISSORS);
        else if (IsKeyPressed('2') || (isLClicked && PtInRect(&m_rtRock, m_mousePos)))
            StartTurn(RPSChoice::ROCK);
        else if (IsKeyPressed('3') || (isLClicked && PtInRect(&m_rtPaper, m_mousePos)))
            StartTurn(RPSChoice::PAPER);
    }
    else
    {
        // 실제 경과 시간(밀리초) 기준 타임라인
        ULONGLONG elapsed = GetTickCount64() - m_turnStartTime;

        if (elapsed < 1000)       
            m_countdown = 3;
        else if (elapsed < 2000)  
            m_countdown = 2;
        else if (elapsed < 3000)  
            m_countdown = 1;
        else if (elapsed < 4200)  // 3.0~4.2초: 컴퓨터 카드 공개
        {
            if (m_aiChoice < 0)
            {
                m_countdown = 0;
                m_aiChoice = rand() % 3;
            }
        }
        else if (elapsed < 5400)  // 4.2~5.4초: 승자 프로필 표시 + 말 이동
        {
            m_countdown = -2;     // 프로필 표시 구간 표식

            if (!m_moved)         // 이 구간에서 딱 한 번만 이동
            {
                m_moved = true;
                FinishTurn();
            }
        }
        else                      // 5.4초 경과: 턴 종료
        {
            m_isEvaluating = false;
        }
    }


    /*
    else
    {
        m_countdownTimer++;
        if (m_countdownTimer >= 60)
        {
            m_countdownTimer = 0;
            m_countdown--; // 3 -> 2 -> 1 -> 0 -> -1

            // 0초가 되면 컴퓨터 랜덤 카드 선택
            if (m_countdown == 0)
            {
                m_aiChoice = rand() % 3; // 0: 가위, 1: 바위, 2: 보
            }
            // -1초가 되면 (컴퓨터 카드가 1초간 보여진 후) 승패 판정 후 이동
            else if (m_countdown < 0)
            {
                FinishTurn();
            }
        }
    }
    */
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

    // 가위/바위/보 버튼 + 눌림버튼
    bool isScissorsHover = PtInRect(&m_rtScissors, m_mousePos) || IsKeyPressed('1');
    bool isRockHover = PtInRect(&m_rtRock, m_mousePos) || IsKeyPressed('2');
    bool isPaperHover = PtInRect(&m_rtPaper, m_mousePos) || IsKeyPressed('3');

    if (isScissorsHover && m_txScissorsHover >= 0)
        g2_Draw2D(m_txScissorsHover, &rFullScreen);
    else if (m_txScissors >= 0)
        g2_Draw2D(m_txScissors, &rFullScreen);

    if (isRockHover && m_txRockHover >= 0)
        g2_Draw2D(m_txRockHover, &rFullScreen);
    else if (m_txRock >= 0)
        g2_Draw2D(m_txRock, &rFullScreen);

    if (isPaperHover && m_txPaperHover >= 0)
        g2_Draw2D(m_txPaperHover, &rFullScreen);
    else if (m_txPaper >= 0)
        g2_Draw2D(m_txPaper, &rFullScreen);

    // 카운트다운 숫자 / 컴퓨터 카드
    if (m_isEvaluating)
    {
        if (m_countdown == 3 && m_txCount3 >= 0)     
            g2_Draw2D(m_txCount3, &rFullScreen);
        else if (m_countdown == 2 && m_txCount2 >= 0) 
            g2_Draw2D(m_txCount2, &rFullScreen);
        else if (m_countdown == 1 && m_txCount1 >= 0) 
            g2_Draw2D(m_txCount1, &rFullScreen);

        else if (m_countdown == 0 && m_aiChoice >= 0)
        {
            if (m_aiChoice == 0 && m_txComScissors >= 0)   
                g2_Draw2D(m_txComScissors, &rFullScreen);
            else if (m_aiChoice == 1 && m_txComRock >= 0)  
                g2_Draw2D(m_txComRock, &rFullScreen);
            else if (m_aiChoice == 2 && m_txComPaper >= 0) 
                g2_Draw2D(m_txComPaper, &rFullScreen);
        }

        // 말보다 먼저 그려서 말이 위에 오게
        else if (m_countdown == -2)
        {
            if (m_turnWinner == 1 && m_txYoungheeWin >= 0)
            {
                g2_Draw2D(m_txYoungheeWin, &rFullScreen);
            }
            else if (m_turnWinner == 2 && m_txCheolsooWin >= 0)
            {
                g2_Draw2D(m_txCheolsooWin, &rFullScreen);
            }
        }

    }

    // 말이 계속 나타나지 않았던 이유: 가려져서... 
    //말은 "가장 마지막에" 그린다 (전체화면 이미지에 가려지지 않도록)
    if (m_txPiece >= 0)
    {
        int posIndex = m_younghee.GetPosition();

        // 혹시 범위를 벗어나면 중앙으로 (안전장치)
        if (posIndex < 0 || posIndex > 10)
        {
            posIndex = 5;
        }

        // 말의 중심을 돌 위치 (m_stoneX[posIndex], m_stoneY)에 맞춤
        // Piece.png 크기 160x95 → 좌상단 좌표는 중심에서 (80, 48)을 뺀 값
        VEC2 piecePos = { (float)(m_stoneX[posIndex] - 80), (float)(m_stoneY - 48) };

        // 두 번째 인자: 소스 영역 = nullptr (이미지 전체)
        // 세 번째 인자: pTranslate = 화면에 그릴 위치
        g2_Draw2D(m_txPiece, nullptr, &piecePos);
    }

    return 0;
}
