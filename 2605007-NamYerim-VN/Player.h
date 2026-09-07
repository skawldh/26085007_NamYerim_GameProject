#pragma once
#include "glc2d.h"

class Player
{
public:
    int Init();
    int Update(const KEYCODE* keys = nullptr);
    int Render();

    void SetTexture(int textureKey);
    int GetHp() const;
    int GetMaxHp() const;

private:
    int textureKey_ = -1;
    int hp_ = 100;
    int maxHp_ = 100;
};