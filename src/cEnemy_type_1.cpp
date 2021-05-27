#include "cEnemy_type_1.h"

void cEnemy_type_1::create_wartosci()
{
	mCount = rand() % 12 + 5;
	mSpeed = static_cast<float>(mCount / 3);
	mHealth_point = mHealth_point_max = static_cast<int>(mCount * 2);
	mScore = rand() % 5 + 1;
	mDamage = rand()%5+2;
}

cEnemy_type_1::cEnemy_type_1(sf::RenderWindow& aWindow, std::string aLink, float aX, float aY) :cObject(aWindow,aLink)
{
	create_wartosci();
	mSprite.setPosition(aX, aY);
}
const int cEnemy_type_1::get_score() const
{
	return mScore;
}

const int cEnemy_type_1::get_damage() const
{
	return mDamage;
}
void cEnemy_type_1::update_position()
{
	mSprite.move(0, mSpeed);

}
void cEnemy_type_1::update_position_2() // ruch w levo po x, lub w prawo po x
{
		mSprite.move(-mSpeed, 0);
}
void cEnemy_type_1::set_pos(float aP, float aR)
{
	mSprite.setPosition(aP, aR);
}
int cEnemy_type_1::get_hp()
{
	return mHealth_point;
}
int cEnemy_type_1::get_hp_max()
{
	return mHealth_point_max;
}
void cEnemy_type_1::hp_minus(int minus)
{
	mHealth_point -= minus;
}
