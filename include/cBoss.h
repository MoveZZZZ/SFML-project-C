#pragma once
#include"cObject.h"
class cBoss:public cObject
{
	float mSpeed;
	int mHp, mHp_max;
	int mScore;
	int mDamage;
	void create_wartosci();

public:
	cBoss(sf::RenderWindow& aWindow, std::string aLink);
	void update_position();
	void update_position_2();
	int get_damage_boss();
	void hp_minus(int aH);
	void set_pos(const int aX, const int aY);
	int get_hp();
	int get_hp_max();
	float get_speed();
};

