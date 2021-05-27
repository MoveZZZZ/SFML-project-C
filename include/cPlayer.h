#pragma once
#include"cObject.h"
#include<SFML/Graphics.hpp>
class cPlayer: public cObject
{
protected:
	float mPosition_x, mPosition_y;
	bool mLeft_key, mUp_key, mRight_key, mDown_key, mSpace_key;
	float mAttack_cooldown;
	float mAttack_cooldown_max;
	int mHp;
	int mHpMax;
	int mDamage_player;
	void pr_wartosci();
public:
	cPlayer(sf::RenderWindow&aWin, std::string aLink);
	void key_pressed(sf::Event&aE,bool aSet_key);
	void update_position();
	const int& get_hp_max() const;
	const int& get_hp() const;
	void set_hp(int aH);
	bool attack();
	void attack_cd();
	void sprite_set_position(float aPosition_x, float aPosition_y);
	void minus_hp(int aWartosc);
	void plus_hp(int aWar);
	int get_damage_player();
};

