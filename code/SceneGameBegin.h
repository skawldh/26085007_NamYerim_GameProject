#pragma once

#include <Windows.h>
#include "glc2d.h"

struct ButtonRect
{
    int x;
    int y;
    int width;
    int height;

    bool Contains(int mouseX, int mouseY) const
    {
        return mouseX >= x &&
            mouseX <= x + width &&
            mouseY >= y &&
            mouseY <= y + height;
    }
};

class SceneGameBegin
{
public:
    int Init();
    int Destroy();
    int Update(const KEYCODE* keys = nullptr);
    int Render();

private:
    bool IsKeyPressed(int key);
    bool IsMouseClicked();

private:
    // 배경 및 팝업 텍스처
    int m_txMain = -1;
    int m_txHowTo = -1;

    // 버튼 텍스처 (800x600 전체 크기 캔버스 이미지)
    int m_txBtnStartNormal = -1;
    int m_txBtnStartHover = -1;

    int m_txBtnHowToNormal = -1;
    int m_txBtnHowToHover = -1;

    int m_txBtnExitNormal = -1;
    int m_txBtnExitHover = -1;

    // 마우스 클릭 판정 영역 (800x600 화면 기준 좌표)
    // ※ 실행해보고 마우스 클릭 범위가 살짝 어긋나면 여기 숫자만 조금씩 조절하시면 됩니다.
    ButtonRect m_btnStart{ 320, 390, 160, 45 };  // "게임 시작" 위치
    ButtonRect m_btnHowTo{ 320, 440, 160, 45 };  // "게임 방법" 위치
    ButtonRect m_btnExit{ 320, 490, 160, 45 };  // "나 가 기" 위치

    bool m_showHowTo = false;
    bool m_prevEnter = false;
    bool m_prevMouse = false;

    int m_mouseX = 0;
    int m_mouseY = 0;
};