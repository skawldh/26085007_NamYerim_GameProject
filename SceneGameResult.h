#pragma once

#include <Windows.h>
#include "glc2d.h"

class SceneGameResult
{
public:
    int Init();
    int Destroy();
    int Update(const KEYCODE* keys = nullptr);
    int Render();

    void SetPlayerWin(bool playerWin);

private:
    bool IsKeyPressed(int key);

private:
    int m_txPlayerWin = -1;
    int m_txPlayerLose = -1;

    bool m_playerWin = false;
};