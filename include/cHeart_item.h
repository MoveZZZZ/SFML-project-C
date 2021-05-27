#pragma once
#include"cObject.h"
class cHeart_item:public cObject
{
	int mUpdate_hp;
	double mSpeed;
public:
	cHeart_item(sf::RenderWindow&aWindow, std::string aLink, float aX, float aY);
	virtual ~cHeart_item();
     int get_update_hp()const;
	void update_position();

};

