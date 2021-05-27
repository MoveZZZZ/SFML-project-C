#pragma once
#include<map>
#include"cGame_update.h"
#include<string>
#include<sstream>
#include<iomanip>
class cGame
{
protected:
	////////////////////////////////////////////////////
	int mWidht;
	int mHight;
	sf::Clock mClock;
	sf::RenderWindow *mWindow;
	sf::Font mFont;
	sf::Text mPoint_txt;
	sf::Text mGame_over_txt;
	sf::Text mGame_win_txt;
	sf::Text mGame_time_txt;
	sf::Text mGo_press;
	sf::Texture mWorld_BG_texture;
	sf::Sprite mWorld_BG;
	sf::Texture mMenu_bg;
	sf::Sprite mMenu_bg_sprite;
	cGame_update* mGame_up;
	cStart_Menu* mMenu;
	///////////////////////////////////////////////////
	std::map<std::string, sf::Texture*> mTextures;
	sf::RectangleShape mPlayer_hp_rec;
	sf::RectangleShape mPlayer_hp_rec_back;
	sf::RectangleShape mBoss_hp_rec;
	sf::RectangleShape mBoss_hop_rec_back;
	sf::RectangleShape mShield_time_rec;
	sf::RectangleShape mShield_time_rec_back;
	//////////////////////////////////////////////////
	double mTime_game;
	void create_Window();
	void create_menu();
	void create_GUI();
	void create_background();
	void create_game_up();
	//////////////////////////////////////////////////
	//https://www.cplusplus.com/reference/vector/vector/
	//mvc c++
public:
	cGame();
	virtual ~cGame();
	void updatePollEvents();
	void updateGUI();
	void renderGUI();
	void render_world();
	void render();
	void window_run();
};


