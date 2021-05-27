#include "cBullet.h"
cBullet::cBullet(float aPos_x, float aPos_y, float aDirection_x, float aDirection_y, float aSpeed, sf::Color aColor)
{
	//std::cout << pos_x << pos_y << "\n";
	mBullet.setSize(sf::Vector2f(6,4));
	mBullet.setFillColor(aColor);
	mBullet.setPosition(aPos_x, aPos_y);
	mM_speed = aSpeed;
	mDirection.x = aDirection_x;
	mDirection.y = aDirection_y;
}
cBullet::~cBullet() {}
const sf::FloatRect cBullet::getGranica() const
{
	return mBullet.getGlobalBounds();
}
void cBullet::update_bullet()
{
	mBullet.move(mM_speed *mDirection);
}
void cBullet::draw_bullet(sf::RenderWindow*aWindow)
{
	
	aWindow->draw(mBullet);
}
