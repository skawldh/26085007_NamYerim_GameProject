#include "Player.h"

int Player::Init()
{
    textureKey_ = g2_TextureLoad("Texture/Player.png");
    return 0;
}

int Player::Update(const KEYCODE* keys)
{
    return 0;
}

int Player::Render()
{
    if (textureKey_ >= 0)
    {
        g2_DrawAlphaOption(1);
        g2_Draw2D(textureKey_, nullptr);
        g2_DrawAlphaOption(0);
    }
    return 0;
}

void Player::SetTexture(int textureKey)
{
    textureKey_ = textureKey;
}

int Player::GetHp() const { return hp_; }
int Player::GetMaxHp() const { return maxHp_; }