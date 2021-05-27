#include "cShield_item.h"
cShield_item::cShield_item(sf::RenderWindow& aWindow, std::string aLink, float aX, float aY) :cObject(aWindow, aLink)
{
	mSpeed = 2.5;
	mSprite.setPosition(aX, aY);
}
cShield_item::~cShield_item(){}
void cShield_item::update_position()
{
	mSprite.move(0, mSpeed);
}
