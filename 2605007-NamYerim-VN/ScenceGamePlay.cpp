#include "ScenceGamePlay.h"

int ScenceGamePlay::Init()
{
    m_txBg = g2_TextureLoad("Texture/InGame.png");
    m_player.Init();
    return 0;
}

int ScenceGamePlay::Destroy()
{
    if (m_txBg >= 0)
    {
        g2_TextureRelease(m_txBg);
        m_txBg = -1;
    }
    return 0;
}

int ScenceGamePlay::Update(const KEYCODE* keys)
{
    m_player.Update(keys);
    return 0;
}

int ScenceGamePlay::Render()
{
    if (m_txBg >= 0)
    {
        g2_DrawAlphaOption(1);
        g2_Draw2D(m_txBg, nullptr);
        g2_DrawAlphaOption(0);
    }
    m_player.Render();
    return 0;
}