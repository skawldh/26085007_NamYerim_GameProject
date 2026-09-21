#include "SceneGameResult.h"

int SceneGameResult::Init()
{
    m_txPlayerWin =
        g2_TextureLoad("Resource/Img_Win_Younghee.png");

    m_txPlayerLose =
        g2_TextureLoad("Resource/Img_Win_Cheolsoo.png");

    return 0;
}

int SceneGameResult::Destroy()
{
    if (m_txPlayerWin >= 0)
    {
        g2_TextureRelease(m_txPlayerWin);
        m_txPlayerWin = -1;
    }

    if (m_txPlayerLose >= 0)
    {
        g2_TextureRelease(m_txPlayerLose);
        m_txPlayerLose = -1;
    }

    return 0;
}

bool SceneGameResult::IsKeyPressed(int key)
{
    SHORT state = GetAsyncKeyState(key);

    return (state & 0x8000) != 0;
}

int SceneGameResult::Update(const KEYCODE* keys)
{
    if (IsKeyPressed(VK_RETURN))
    {
        return 0;
    }

    if (IsKeyPressed(VK_ESCAPE))
    {
        return 0;
    }

    return 2;
}

int SceneGameResult::Render()
{
    int textureKey = -1;

    if (m_playerWin)
    {
        textureKey = m_txPlayerWin;
    }
    else
    {
        textureKey = m_txPlayerLose;
    }

    if (textureKey >= 0)
    {
        g2_DrawAlphaOption(1);
        g2_Draw2D(textureKey, nullptr);
        g2_DrawAlphaOption(0);
    }

    return 0;
}

void SceneGameResult::SetPlayerWin(bool playerWin)
{
    m_playerWin = playerWin;
}