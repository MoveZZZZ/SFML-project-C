#pragma once
#include"cEnemy_type_1.h"
class cEnemy_type_2:public cEnemy_type_1
{
	void create_wartosci();
public:
	cEnemy_type_2(sf::RenderWindow& window, std::string link, float x, float y);
	virtual ~cEnemy_type_2();
};

