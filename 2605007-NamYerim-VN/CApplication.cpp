#include <stdio.h>
#include "CApplication.h"
#include "glc2d.h"

extern CApplication g_app;

int AppUpdate() { return g_app.Update(); }
int AppRender() { return g_app.Render(); }

int CApplication::InitSdk()
{
    g2_InitSdk();
    g2_SetFrameMove(AppUpdate);
    g2_SetRender(AppRender);

    g2_CreateWin(m_winPos.x, m_winPos.y, m_winSize.cx, m_winSize.cy, m_winName.c_str());
    return 0;
}

int CApplication::Init()
{
    InitSdk();
    m_sceneBegin.Init();
    m_scenePlay.Init();
    m_sceneResult.Init();
    m_nSceneState = 0; // 메뉴 화면 시작
    return 0;
}

int CApplication::Update()
{
    const KEYCODE* keys = g2_GetKeyboard();

    switch (m_nSceneState)
    {
    case 0:
        m_sceneBegin.Update(keys);
        break;
    case 1:
        m_scenePlay.Update(keys);
        break;
    case 2:
        m_sceneResult.Update(keys);
        break;
    }

    return 0;
}

int CApplication::Render()
{
    // 화면 초기화
    g2_SetClearColor(0xFF1B262C);

    // 현재 씬 1개만 단독으로 띄우기
    switch (m_nSceneState)
    {
    case 0:
        m_sceneBegin.Render();
        break;
    case 1:
        m_scenePlay.Render();
        break;
    case 2:
        m_sceneResult.Render();
        break;
    }

    return 0;
}

int CApplication::Destroy()
{
    m_sceneBegin.Destroy();
    m_scenePlay.Destroy();
    m_sceneResult.Destroy();
    g2_DestroyWin();
    return 0;
}