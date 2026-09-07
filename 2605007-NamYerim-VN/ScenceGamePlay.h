#pragma once
#include "glc2d.h"
#include "Player.h"

class ScenceGamePlay
{
public:
    int Init();
    int Destroy();
    int Update(const KEYCODE* keys = nullptr);
    int Render();

private:
    Player m_player;
    int m_txBg = -1;
};