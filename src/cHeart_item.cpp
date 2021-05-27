#include "cHeart_item.h"
cHeart_item::cHeart_item(sf::RenderWindow& aWindow, std::string aLink, float aX, float aY) :cObject(aWindow, aLink)
{
	mUpdate_hp = 30;
	mSprite.setPosition(aX, aY);
	mSpeed = 2;
}
cHeart_item::~cHeart_item(){}
int cHeart_item::get_update_hp()const 
{
	return mUpdate_hp;
}
void cHeart_item::update_position()
{
	mSprite.move(0, mSpeed);
}
