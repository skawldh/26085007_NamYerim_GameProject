#pragma once
#include "glc2d.h"

class ScenceGameResult
{
public:
    int Init();
    int Destroy();
    int Update(const KEYCODE* keys = nullptr);
    int Render();
};