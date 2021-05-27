#include "cPlayer.h"
void cPlayer::pr_wartosci()
{
    this->mAttack_cooldown_max = 15;
    this->mAttack_cooldown = this->mAttack_cooldown_max;
    this->mHpMax = 100;
    this->mHp = this->mHpMax;
    mPosition_x = 640;
    mPosition_y = 360;
    mDamage_player = rand() % 15 + 5;
    mLeft_key = mUp_key = mRight_key = mDown_key = mSpace_key = false;
}
cPlayer::cPlayer(sf::RenderWindow& win, std::string link):cObject(win, link)
{
    this->pr_wartosci();
}
const int& cPlayer::get_hp_max() const
{
    return this->mHpMax;
}
const int& cPlayer::get_hp() const
{
    return this->mHp;
}
void cPlayer::plus_hp(int aWar)
{
    mHp += aWar;
    if (mHp > mHpMax)
    {
        mHp = mHpMax;
    }
}
void cPlayer::minus_hp(int aWartosc)
{
    mHp -= aWartosc;
    if (mHp < 0)
        mHp = 0;
}
void cPlayer::key_pressed(sf::Event& aE, bool aSet_key)
{
	int key = aE.key.code;
   
        switch (key)
	{
    case 0:
        this->mLeft_key = aSet_key;
        break;
    case 71:
        this->mLeft_key = aSet_key;
        break;
    case 22:
        this->mUp_key = aSet_key;
        break;
    case 73:
        this->mUp_key = aSet_key;
        break;
    case 3:
        this->mRight_key = aSet_key;
        break;
    case 72:
        this->mRight_key = aSet_key;
        break;
    case 18:
        this->mDown_key = aSet_key;
        break;
    case 74:
        this->mDown_key = aSet_key;
        break;
    case 57:
        this->mSpace_key = aSet_key;
	}
}
void cPlayer::sprite_set_position(float aPosition_x, float aPosition_y)
{
    mSprite.setPosition(aPosition_x, aPosition_y);
}
void cPlayer::update_position()
{
    if (this->mLeft_key)
    {
        if (mPosition_x > 0)
            mPosition_x -= 15;
    }
    if (this->mUp_key)
    {
        if (this->mPosition_y > 0)
            this->mPosition_y -= 15;
    }
    if (this->mRight_key)
    {
        if (this->mPosition_x+90 < mWindow.getSize().x)
            this->mPosition_x += 15;
    }
    if (this->mDown_key)
    {
        if (this->mPosition_y+175 < mWindow.getSize().y)
            this->mPosition_y += 15;
    }
    sprite_set_position(mPosition_x, mPosition_y);
}
void cPlayer::attack_cd()
{
    if (mAttack_cooldown < mAttack_cooldown_max)
        mAttack_cooldown += 0.5;
}
bool cPlayer::attack()
{
    if(mAttack_cooldown>=mAttack_cooldown_max)
    {
        mAttack_cooldown = 0; return true;
    }
    return false;
}
void cPlayer::set_hp(int aH)
{
    mHp = aH;
}
int  cPlayer::get_damage_player()
{
    return mDamage_player;
}
