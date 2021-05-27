#include "cEnemy_type_2.h"
void cEnemy_type_2::create_wartosci()
{
	mCount = rand() % 15 + 4;
	mSpeed = static_cast<double>(mCount / 3);
	mHealth_point = mHealth_point_max = static_cast<int>(mCount * 2);
	mScore = rand() % 3 + 1;
    mDamage = rand() % 5+ 2;

}

cEnemy_type_2::cEnemy_type_2(sf::RenderWindow& aWindow, std::string aLink, float aX, float aY):cEnemy_type_1(aWindow,aLink,aX,aY)
{
	create_wartosci();
}

cEnemy_type_2::~cEnemy_type_2()
{
}

