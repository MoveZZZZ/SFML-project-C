#include "cStart_Menu.h"
void cStart_Menu::menu_1(float aWidht_menu, float aHight_menu)
{
		mMenu_text[0].setFont(mFont_menu);
		mMenu_text[0].setFillColor(sf::Color::Red);
		mMenu_text[0].setString("Start Game");
		mMenu_text[0].setPosition(sf::Vector2f(aWidht_menu / 1.25, aHight_menu / (MAX_NUMBER_MENU+1) * 1));
}
void cStart_Menu::menu_2(float aWidht_menu, float aHight_menu)
{
	mMenu_text[1].setFont(mFont_menu);
	mMenu_text[1].setFillColor(sf::Color::White);
	mMenu_text[1].setString("How to play");
	mMenu_text[1].setPosition(sf::Vector2f(aWidht_menu /1.25, aHight_menu / (MAX_NUMBER_MENU+1) * 2));
}

void cStart_Menu::menu_3(float aWidht_menu, float aHight_menu)
{
	mMenu_text[2].setFont(mFont_menu);
	mMenu_text[2].setFillColor(sf::Color::White);
	mMenu_text[2].setString("Exit");
	mMenu_text[2].setPosition(sf::Vector2f(aWidht_menu /1.25, aHight_menu / (MAX_NUMBER_MENU+1) * 3));
}
void cStart_Menu::how_to_play_update(float aWidht_menu, float aHight_menu)
{
	mSetting_text.setFont(mFont_menu);
	mSetting_text.setFillColor(sf::Color(255, 69, 0));
	mSetting_text.setCharacterSize(32);
	mSetting_text.setString("Przycisk START GAME rozpoczyna gre\nPod czas gry muszisz zdobywac punkty(rozne wrogi daja rozna iliosc punktow). Bron gracza\nma czas odnowienia. Gracz na paczatku gry ma 100 punktow zdrowia. Punkty zdrowia mozna\npowiekszyc, zbierajac serca. Tarcza blokuje uszkodzenia w ciagu 10 secund.\nKierowac statkiem mozna za pomoca klawisz WASD, lub za pomoca strzalek.\nZeby otworzyc mienu pod czas gry, nalezy nacisnac Home\nZeby wrocic do menu poczatkowego - nascisnij Home");
	mSetting_text.setPosition(sf::Vector2f(aWidht_menu/5-200, aHight_menu/5-100));
}
cStart_Menu::cStart_Menu(float aWidht, float aHight):mWidht_menu(aWidht), mHight_menu(aHight)
{
	mIndex_game = 3;
	if(!mFont_menu.loadFromFile("Font/font_menu_paper_cuts_2.ttf"))
	{
		std::cout << "Nie udalo sie otworzyc file ttf (menu.cpp)\n";
	}
	if (!mMenu_texture.loadFromFile("Images/menu_bg.jpg"))
	{
		std::cout << "Nie udalo sie otworzyc file menu_bg(menu.cpp)\n";
	}
	if (!mKeyboard_1.loadFromFile("Images/keyboard_1.png"))
	{
		std::cout << "Nie udalo sie otworzuc keyboard_1 (menu.cpp)";
	}
	if (!mKeyboard_2.loadFromFile("Images/keyboard_2.png"))
	{
		std::cout << "Nie udalo sie otworzuc keyboard_2 (menu.cpp)";
	}
	if (!mBg_how.loadFromFile("Images/how_bg.jpg"))
	{
		std::cout << "Nie udalo sie otworzuc keyboard_3 (menu.cpp)";
	}
	mKeyboard_sprite_1.setTexture(mKeyboard_1);
	mKeyboard_sprite_1.setPosition(mWidht_menu/3-400, mHight_menu/2+100);
	mKeyboard_sprite_2.setTexture(mKeyboard_2);
	mKeyboard_sprite_2.setPosition(mWidht_menu/3-200, mHight_menu/2+100);
	mMenu_sprite.setTexture(mMenu_texture);
	mBg_how_s.setTexture(mBg_how);
	mActual_menu_index = 0;
	menu_1(mWidht_menu,mHight_menu);
	menu_2(mWidht_menu, mHight_menu);
	menu_3(mWidht_menu, mHight_menu);
}
void cStart_Menu::draw_how_to_play(sf::RenderWindow& aWindow)
{
	//std::cout << "Jestem draw_how_to_play\n";
	how_to_play_update(mWidht_menu, mHight_menu);
	aWindow.draw(mBg_how_s);
	aWindow.draw(mSetting_text);
	aWindow.draw(mKeyboard_sprite_1);
	aWindow.draw(mKeyboard_sprite_2);
}
void cStart_Menu::draw_menu(sf::RenderWindow&aWindow)
{
	aWindow.draw(mMenu_sprite);
	for (int i = 0; i < MAX_NUMBER_MENU; i++)
	{
		//std::cout << "Jestem draw_menu() for\n";
		aWindow.draw(mMenu_text[i]);
	}
}

void cStart_Menu::key_pressed_meny_up()
{
	if (mActual_menu_index-1>=0)
	{
		mMenu_text[mActual_menu_index].setFillColor(sf::Color::White);
		mActual_menu_index--;
		mMenu_text[mActual_menu_index].setFillColor(sf::Color::Red);
	}
}

void cStart_Menu::key_pressed_menu_down()
{
	if (mActual_menu_index + 1 <= MAX_NUMBER_MENU)
	{
		mMenu_text[mActual_menu_index].setFillColor(sf::Color::White);
		mActual_menu_index++;
		mMenu_text[mActual_menu_index].setFillColor(sf::Color::Red);
	}
}
int cStart_Menu::get_pressed_item()
{
	//std::cout << actual_menu_index<<std::endl;
	return mActual_menu_index;
}
void cStart_Menu::set_pressed_key_index_game(int aIndex)
{
	mIndex_game = aIndex;
	//std::cout << index_game << std::endl;
}
int cStart_Menu::get_pressed_key_index_game()
{
	//std::cout << index_game << std::endl;
	return mIndex_game;
}


