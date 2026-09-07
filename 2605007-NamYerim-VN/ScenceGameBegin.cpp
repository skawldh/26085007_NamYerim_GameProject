#include "ScenceGameBegin.h"

int ScenceGameBegin::Init()
{
    // 메인 배경 이미지 1개만 정상적으로 로드
    m_txMain = g2_TextureLoad("Texture/Main.png");
    return 0;
}

int ScenceGameBegin::Destroy()
{
    if (m_txMain >= 0)
    {
        g2_TextureRelease(m_txMain);
        m_txMain = -1;
    }
    return 0;
}

int ScenceGameBegin::Update(const KEYCODE* keys)
{
    return 0;
}

int ScenceGameBegin::Render()
{
    if (m_txMain >= 0)
    {
        g2_DrawAlphaOption(1);
        g2_Draw2D(m_txMain, nullptr);
        g2_DrawAlphaOption(0);
    }
    return 0;
}