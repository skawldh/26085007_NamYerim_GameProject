#pragma once
#include <Windows.h>
#include <string>
#include "ScenceGameBegin.h"
#include "ScenceGamePlay.h"
#include "ScenceGameResult.h"

class CApplication
{
public:
    int Init();
    int Update();
    int Render();
    int Destroy();

protected:
    int InitSdk();

protected:
    POINT m_winPos{ 50, 50 };
    SIZE m_winSize{ 1586, 992 };

    std::string m_winName = "26085007_NamYerim_ENDLESS RUNNER";

    int m_nSceneState = 0;

    ScenceGameBegin  m_sceneBegin;
    ScenceGamePlay   m_scenePlay;
    ScenceGameResult m_sceneResult;
};