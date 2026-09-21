#include "SceneGameBegin.h"

int SceneGameBegin::Init()
{
    //배경이미지
    m_txMain = g2_TextureLoad("Texture/Main_BG.png");
    m_txHowTo = g2_TextureLoad("Texture/Img_HowTo.png");

    //버튼 이미지 로드
    m_txBtnStartNormal = g2_TextureLoad("Texture/Btn_Start_Normal.png");
    m_txBtnStartHover = g2_TextureLoad("Texture/Btn_Start_Hover.png");

    m_txBtnHowToNormal = g2_TextureLoad("Texture/Btn_HowTo_Normal.png");
    m_txBtnHowToHover = g2_TextureLoad("Texture/Btn_HowTo_Hover.png");

    m_txBtnExitNormal = g2_TextureLoad("Texture/Btn_Exit_Normal.png");
    m_txBtnExitHover = g2_TextureLoad("Texture/Btn_Exit_Hover.png");

    m_showHowTo = false;
    m_prevEnter = false;
    m_prevMouse = false;

    return 0;
}

int SceneGameBegin::Destroy()
{
    if (m_txMain >= 0) { g2_TextureRelease(m_txMain);  m_txMain = -1; }
    if (m_txHowTo >= 0) { g2_TextureRelease(m_txHowTo); m_txHowTo = -1; }

    if (m_txBtnStartNormal >= 0) { g2_TextureRelease(m_txBtnStartNormal); m_txBtnStartNormal = -1; }
    if (m_txBtnStartHover >= 0) { g2_TextureRelease(m_txBtnStartHover);  m_txBtnStartHover = -1; }

    if (m_txBtnHowToNormal >= 0) { g2_TextureRelease(m_txBtnHowToNormal); m_txBtnHowToNormal = -1; }
    if (m_txBtnHowToHover >= 0) { g2_TextureRelease(m_txBtnHowToHover);  m_txBtnHowToHover = -1; }

    if (m_txBtnExitNormal >= 0) { g2_TextureRelease(m_txBtnExitNormal);  m_txBtnExitNormal = -1; }
    if (m_txBtnExitHover >= 0) { g2_TextureRelease(m_txBtnExitHover);   m_txBtnExitHover = -1; }

    return 0;
}

bool SceneGameBegin::IsKeyPressed(int key)
{
    SHORT state = GetAsyncKeyState(key);
    return (state & 0x8000) != 0;
}

bool SceneGameBegin::IsMouseClicked()
{
    bool currentMouse = IsKeyPressed(VK_LBUTTON);
    bool clicked = currentMouse && !m_prevMouse;
    m_prevMouse = currentMouse;

    return clicked;
}

int SceneGameBegin::Update(const KEYCODE* keys)
{
    bool enterPressed = IsKeyPressed(VK_RETURN);
    bool enterDown = enterPressed && !m_prevEnter;
    m_prevEnter = enterPressed;

    // 마우스 좌표 구하기 (클라이언트 창 내부 좌표 기준)
    POINT cursorPosition{ 0, 0 };
    GetCursorPos(&cursorPosition);

    HWND foregroundWindow = GetForegroundWindow();
    if (foregroundWindow != nullptr)
    {
        ScreenToClient(foregroundWindow, &cursorPosition);
    }

    m_mouseX = cursorPosition.x;
    m_mouseY = cursorPosition.y;

    bool mouseClicked = IsMouseClicked();

    // 1. 게임 방법 팝업 출력 중 처리
    if (m_showHowTo)
    {
        if (mouseClicked || enterDown || IsKeyPressed(VK_ESCAPE))
        {
            m_showHowTo = false;
        }
        return 0;
    }

    // 2. 버튼 클릭 이벤트
    if (mouseClicked)
    {
        if (m_btnStart.Contains(m_mouseX, m_mouseY))
        {
            return 1; // 게임 시작
        }

        if (m_btnHowTo.Contains(m_mouseX, m_mouseY))
        {
            m_showHowTo = true;
            return 0;
        }

        if (m_btnExit.Contains(m_mouseX, m_mouseY))
        {
            return -1; // 게임 종료
        }
    }

    return 0;
}

int SceneGameBegin::Render()
{
    g2_DrawAlphaOption(255);

    // 1. 메인 배경 이미지 출력 (화면 전체)
    if (m_txMain >= 0)
    {
        g2_Draw2D(m_txMain, nullptr);
    }

    // 2. 버튼 텍스처 출력 (팝업창이 켜져 있지 않을 때만)
    if (!m_showHowTo)
    {
        // [게임 시작] 버튼 렌더링
        bool isStartHover = m_btnStart.Contains(m_mouseX, m_mouseY);
        int txStart = isStartHover ? m_txBtnStartHover : m_txBtnStartNormal;
        if (txStart >= 0)
        {
            g2_Draw2D(txStart, nullptr); // nullptr을 주면 800x600 캔버스 전체에 딱 맞게 출력됩니다.
        }

        // [게임 방법] 버튼 렌더링
        bool isHowToHover = m_btnHowTo.Contains(m_mouseX, m_mouseY);
        int txHowTo = isHowToHover ? m_txBtnHowToHover : m_txBtnHowToNormal;
        if (txHowTo >= 0)
        {
            g2_Draw2D(txHowTo, nullptr);
        }

        // [나 가 기] 버튼 렌더링
        bool isExitHover = m_btnExit.Contains(m_mouseX, m_mouseY);
        int txExit = isExitHover ? m_txBtnExitHover : m_txBtnExitNormal;
        if (txExit >= 0)
        {
            g2_Draw2D(txExit, nullptr);
        }
    }

    // 3. 게임 방법 팝업창 출력
    if (m_showHowTo && m_txHowTo >= 0)
    {
        g2_Draw2D(m_txHowTo, nullptr);
    }

    return 0;
}