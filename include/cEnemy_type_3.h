#pragma once
#include "cEnemy_type_1.h"
class cEnemy_type_3 : public cEnemy_type_1
{
	void create_wartosci();
public:
	cEnemy_type_3(sf::RenderWindow& aWindow, std::string aLink, float aX, float aY);
	virtual ~cEnemy_type_3();
};

