#include "cEnemy_type_3.h"

void cEnemy_type_3::create_wartosci()
{
	mCount = rand() % 10 + 5;
	mSpeed = static_cast<double>(mCount / 3);
	mHealth_point = mHealth_point_max = static_cast<int>(mCount * 2);
	mScore = rand() % 10 + 5;
	mDamage = rand() % 8 + 4;
}

cEnemy_type_3::cEnemy_type_3(sf::RenderWindow& aWindow, std::string aLink, float aX, float aY):cEnemy_type_1(aWindow,aLink,aX,aY)
{
	create_wartosci();
}
cEnemy_type_3::~cEnemy_type_3(){
}
