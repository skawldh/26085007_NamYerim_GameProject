#pragma once
#include "glc2d.h"

class ScenceGameBegin
{
public:
    int Init();
    int Destroy();
    int Update(const KEYCODE* keys = nullptr);
    int Render();

private:
    int m_txMain = -1;   // 배경 이미지 (Main.png)
    int m_txMario = -1;  // 메뉴/타이틀 텍스처
};