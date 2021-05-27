#include "cBoss.h"
void cBoss::create_wartosci()
{
	mSpeed = 3;
	mHp = mHp_max= 50;
	mScore = 100;
	mDamage =15;
}
cBoss::cBoss(sf::RenderWindow& aWindow, std::string aLink) :cObject(aWindow, aLink)
{
	create_wartosci();
	mSprite.setPosition(mWindow.getSize().x/2+100, -400);
}
void cBoss::update_position()
{
	mSprite.move(0, mSpeed);
}
void cBoss::update_position_2()
{
	mSprite.move(-mSpeed, 0);
}
int cBoss::get_damage_boss()
{
	return mDamage;
}
void cBoss::hp_minus(int aH)
{
	mHp -= aH;
	if (mHp <= 0)
	{
		mHp = 0;
	}
}
void cBoss::set_pos(const int aX, const int aY)
{
	mSprite.setPosition((float)aX, (float)aY);

}
int cBoss::get_hp()
{
	return mHp;
}
int cBoss :: get_hp_max()
{
	return mHp_max;
}
float cBoss::get_speed()
{
	return mSpeed;
}

