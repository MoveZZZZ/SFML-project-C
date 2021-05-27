#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#define MAX_NUMBER_MENU 3
class cStart_Menu
{
private:
	int mIndex_game;
	float mWidht_menu; 
	float mHight_menu;
	int mActual_menu_index;
	sf::Texture mKeyboard_1;
	sf::Sprite mKeyboard_sprite_1;
	sf::Texture mKeyboard_2;
	sf::Sprite mKeyboard_sprite_2;
	sf::Texture mBg_how;
	sf::Sprite mBg_how_s;
	sf::Texture mMenu_texture;
	sf::Sprite mMenu_sprite;
	sf::Font mFont_menu;
	sf::Text mMenu_text[MAX_NUMBER_MENU];
	sf::Text mSetting_text;
	void how_to_play_update(float aWidht_menu, float aHight_menu);
	void menu_1(float aWidht_menu,float aHight_menu);
	void menu_2(float aWidht_menu, float aHight_menu);
	void menu_3(float aWidht_menu, float aHight_menu);

public:
	cStart_Menu(float aWidht, float aHight);
	//~Start_Menu();
	void draw_menu(sf::RenderWindow &aWindow);
	void draw_how_to_play(sf::RenderWindow &aWindow);
	void key_pressed_meny_up();
	void key_pressed_menu_down();
	int get_pressed_item();
	void set_pressed_key_index_game(int aIndex);
	int get_pressed_key_index_game();

};

