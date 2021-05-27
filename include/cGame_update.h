#pragma once
#include"cPlayer.h"
#include"cBullet.h"
#include"cEnemy_type_1.h"
#include"cEnemy_type_2.h"
#include"cEnemy_type_3.h"
#include"cBoss.h"
#include"cHeart_item.h"
#include"cShield_item.h"
#include"cStart_Menu.h"
#include<iomanip>
class cGame_update
{
protected:
	float mEnemy_1_timer;
	float mEnemy_1_timer_limit;
	float mEnemy_2_timer;
	float mEnemy_2_timer_limit;
	float mEnemy_3_timer;
	float mEnemy_3_timer_limit;
	unsigned short mPoints;
	cPlayer* mPlayer;
	cBoss* mBoss;
	bool mIs_fire;
	//bullet player
	std::vector<cBullet*>mBullet_vector_player;
	//bullet enemy_1
	std::vector<cBullet*>mBullet_vector_enemy_1;
	//bullet enemy_2
	std::vector < cBullet*>mBullet_vector_enemy_2;
	//bullet enemy_3
	std::vector<cBullet*>mBullet_vector_enemy_3_gun_1;
	std::vector<cBullet*>mBullet_vector_enemy_3_gun_2;
	/////////////////////////////////////////////////
	//////////////////////////////////////////////////
	//Enemy_1
	std::vector<cEnemy_type_1*>mVector_enemy_1;
	//Enemy_2
	std::vector<cEnemy_type_2*>mVector_enemy_2;
	//Enemy_3
	std::vector<cEnemy_type_3*>mVector_enemy_3;
	//////BOSS////////////////////////
	std::vector<cBullet*>mBullet_vector_boss_1;
	std::vector<cBullet*>mBullet_vector_boss_2;
	std::vector<cBullet*>mBullet_vector_boss_3;
	std::vector<cBullet*>mBullet_vector_boss_4;
	//////////////////////////////////////////////////////////////////////////////
	/////////ITEM/////////////////////
	double mTime_heart;
	double mTime_heart_max;
	double mTime_shield;
	double mTime_shield_max;
	double mTime_shield_doing;
	double mTime_shield_doing_max;
	bool mShield_is_going;
	std::vector<cHeart_item*>mVector_heart;
	std::vector<cShield_item*>mVector_shield;
	sf::RenderWindow& mWindow;
	/////////////////////////
	void create_points_number();
	void create_Player();
	void enemy_1_create_time();
	void enemy_2_create_time();
	void enemy_3_create_time();
	void heart_create_time();
	void shield_create_time();
	//https://www.cplusplus.com/reference/vector/vector/
	//mvc c++
	void create_boss();
public:
	cGame_update(sf::RenderWindow &window);
	virtual ~cGame_update();
	void update();
	void cr_men();
	//player
	void update_player();
	void update_bullet_player();
	void update_keyboard_fire_player();
	void update_hp_player();
	//enemy 1
	void create_and_update_enemy_1();
	void create_and_update_bullets_enemy_1();
	//enemy 2
	void create_and_update_enemy_2();
	void create_and_update_bullets_enemy_2();
	//enemy 3
	void create_and_update_enemy_3();
	void create_and_update_bullets_enemy_3();
	//BOSS
	void create_and_update_boss();
	void create_and_update_bullets_boss();
	//heart
	void create_and_update_heart();
	//shield
	void create_and_update_shield();
	void update_shield_going_timer();
	///////
	void kill_enemy();
	/////
	void set_time_heart(double aTime_h);
	void set_time_shield(double aTime_s);
	cPlayer *get_player();
	cBoss* get_boss();
	void draw();
	bool get_s();
	unsigned short get_mPoints()const;
	double get_doing_max();
	double get_doing();
	bool get_is_fire_player();
};

