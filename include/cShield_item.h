#pragma once
#include"cObject.h"
class cShield_item:public cObject
{
	double mSpeed;
public:
	cShield_item(sf::RenderWindow& window, std::string link, float x, float y);
	virtual ~cShield_item();
	void update_position();
};

