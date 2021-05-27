#pragma once
#include"cObject.h"
#include<iostream>
class cEnemy_type_1:public cObject
{
protected:
	int mPos;
	int mAttack_cd_enemy_1;
	int mAttack_cd_enemy_1_max;
	int mRandom_pos;
	unsigned mCount;
	int mHealth_point, mHealth_point_max,mDamage;
	double mSpeed;
	int mScore;
	void create_wartosci();
	//player->getpos().x+40, player->getpos().y, 0, -1, 5, sf::Color (255, 215, 0))
public:
	cEnemy_type_1(sf::RenderWindow &aWindow, std::string aLink, float aX, float aY);
	const int get_score() const;
	const int get_damage() const;
	void update_position(); // polimorfizm
	void update_position_2(); // polimorfizm
	void set_pos(float aP, float aR);
	int get_hp();
	int get_hp_max();
	virtual void hp_minus(int aMinus);
	/*void fire();
	void update();
	void draw_obj();*/
	


};

