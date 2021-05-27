#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
class cBullet
{
	sf::RectangleShape mBullet;
	sf::Vector2f mDirection;
	float mM_speed;
public:
	cBullet(float aPos_x, float aPos_y, float aDirection_x, float aDirection_y, float aSpeed, sf::Color aColor);
	virtual ~cBullet();
	const sf::FloatRect getGranica() const;
	void update_bullet();
	void draw_bullet(sf::RenderWindow*aWindow);
};

