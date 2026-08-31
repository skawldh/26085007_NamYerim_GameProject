#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <glc2d.h> 
#include <stdio.h>
#include <stdlib.h>

#if defined(_DEBUG)
#if defined(_M_X64)
#pragma comment(lib, "glc2d_x64_debug.lib")
#elif defined(_M_IX86)
#pragma comment(lib, "glc2d_win32_debug.lib")
#endif
#else
#if defined(_M_X64)
#pragma comment(lib, "glc2d_x64_release.lib")
#elif defined(_M_IX86)
#pragma comment(lib, "glc2d_win32_release.lib")
#endif
#endif

int g_screenWidth = 1024;
int g_screenHeight = 640;

// 0: MainMenu, 1: HowToPlay, 2: InGamePreview
int g_gameState = 0;
int g_selectedMenu = 0; 

// glc2d 폰트 핸들 변수
int g_fontTitle = -1;
int g_fontMenu = -1;
int g_fontBody = -1;


bool IsKeyDown(const KEYCODE* keys, int key)
{
    if (keys != NULL && *(keys + key) == EINPUT_DOWN)
    {
        return true;
    }
    return false;
}

// 창 닫기
void CloseGame(void)
{
    PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
}

// 메인 메뉴 키보드 입력 , 선택 상태 업데이트 함수
void UpdateMainMenu(const KEYCODE* keys)
{
    // W 키 or 상향키
    if (IsKeyDown(keys, VK_UP) || IsKeyDown(keys, 'W'))
    {
        g_selectedMenu--;
        if (g_selectedMenu < 0) g_selectedMenu = 2; //t순환
    }

    // S 키 or 하향키
    if (IsKeyDown(keys, VK_DOWN) || IsKeyDown(keys, 'S'))
    {
        g_selectedMenu++;
        if (g_selectedMenu > 2) g_selectedMenu = 0; 
    }

    // Enter 키 
    if (IsKeyDown(keys, VK_RETURN))
    {
        if (g_selectedMenu == 0) g_gameState = 2;      // GAME START -> 게임 시작
        else if (g_selectedMenu == 1) g_gameState = 1; // HOW TO PLAY -> 게임 설명
        else if (g_selectedMenu == 2) CloseGame();    // EXIT -> 종료
    }

    // ESC 키 눌림 시 바로 끝
    if (IsKeyDown(keys, VK_ESCAPE))
    {
        CloseGame();
    }
}

int FrameMove(void)
{
    const KEYCODE* keys = g2_GetKeyboard();

    if (keys == NULL) return 0;

    if (g_gameState == 0)
    {
        UpdateMainMenu(keys);
    }
    else
    {
        // 설명 화면 or 시연 화면에서 Enter/ESC 입력 시 메인 메뉴로 복귀
        if (IsKeyDown(keys, VK_RETURN) || IsKeyDown(keys, VK_ESCAPE))
        {
            g_gameState = 0;
        }
    }

    return 0;
}

int Render(void)
{
    // 1. 메인 메뉴 화면 
    if (g_gameState == 0)
    {
        g2_FontDrawText(g_fontTitle, { 280, 50, 760, 110 }, 0xFF57CC99, "ENDLESS RUNNER");
        g2_FontDrawText(g_fontBody, { 355, 120, 760, 160 }, 0xFFC7F9CC, "2D SIDE-SCROLLING GAME");

        // 삼항 연산자 색상 강조 (선택 O : 0xFFFFD166 , 선택 X: 0xFFE6EDF3)
        g2_FontDrawText(g_fontMenu, { 400, 240, 720, 285 }, (g_selectedMenu == 0) ? 0xFFFFD166 : 0xFFE6EDF3, "GAME START");
        g2_FontDrawText(g_fontMenu, { 400, 310, 720, 355 }, (g_selectedMenu == 1) ? 0xFFFFD166 : 0xFFE6EDF3, "HOW TO PLAY");
        g2_FontDrawText(g_fontMenu, { 400, 380, 720, 425 }, (g_selectedMenu == 2) ? 0xFFFFD166 : 0xFFE6EDF3, "EXIT");

        g2_FontDrawText(g_fontBody, { 330, 520, 800, 560 }, 0xFF8FB8DE, "W, S or Arrow Keys: Move");
        g2_FontDrawText(g_fontBody, { 375, 560, 760, 600 }, 0xFF8FB8DE, "Enter: Select   Esc: Exit");
    }
    // 2. 게임 방법 화면 
    else if (g_gameState == 1)
    {
        g2_FontDrawText(g_fontTitle, { 380, 50, 760, 100 }, 0xFF57CC99, "HOW TO PLAY");
        g2_FontDrawText(g_fontBody, { 150, 180, 900, 220 }, 0xFFE6EDF3, "1. Press Spacebar to Jump and avoid obstacles.");
        g2_FontDrawText(g_fontBody, { 150, 240, 900, 280 }, 0xFFE6EDF3, "2. Collect coins to get high scores.");
        g2_FontDrawText(g_fontBody, { 310, 540, 820, 580 }, 0xFF8FB8DE, "Enter or Esc: Return to Main Menu");
    }
    // 3. ㄱㅔ임 내부 프레임워크 시연 화면
    else if (g_gameState == 2)
    {
        g2_FontDrawText(g_fontTitle, { 370, 50, 760, 100 }, 0xFFFFD166, "GAME RUNNING");
        g2_FontDrawText(g_fontBody, { 250, 250, 850, 290 }, 0xFFE6EDF3, "Week 1 Prototype: Runner Game Loop Test");
        g2_FontDrawText(g_fontBody, { 310, 540, 820, 580 }, 0xFF8FB8DE, "Enter or Esc: Return to Main Menu");
    }

    return 0;
}

int main(void)
{
    // Sdk 초기화 및 예외 처리
    if (g2_InitSdk() != 0)
    {
        printf("glc2d SDK 초기화 실패.\n");
        return 0;
    }

    g2_SetClearColor(0xFF1B263B); // 배경색
    g2_SetStateShow(0);
    g2_SetCursorShow(0);
    g2_SetFrameMove(FrameMove);   // 콜백
    g2_SetRender(Render);         // 콜백

    // 창 생성 실패
    if (g2_CreateWin(100, 70, g_screenWidth, g_screenHeight, "26085007_NamYerim_ENDLESS RUNNER", true) != 0)
    {
        printf("게임 창 생성 실패.\n");
        g2_DestroyWin();
        return 0;
    }

    // 폰트 생성 ,생성 실패
    g_fontTitle = g2_FontCreate("Arial", 40, 0);
    g_fontMenu = g2_FontCreate("Arial", 28, 0);
    g_fontBody = g2_FontCreate("Consolas", 20, 0);

    if (g_fontTitle < 0 || g_fontMenu < 0 || g_fontBody < 0)
    {
        printf("폰트 생성 처리 중 오류 발생.\n");
        g2_DestroyWin();
        return 0;
    }

    g2_Run(); // 루프

    g2_DestroyWin();

    return 0;
}