#include "cGame.h"
void cGame::create_Window()
{
	mWidht = 1280;  mHight = 720;
	this->mWindow = new sf::RenderWindow(sf::VideoMode(mWidht, mHight), "SPACE GAME MAKSIM FILATAU");
	mWindow->setFramerateLimit(60);

}
void cGame::create_menu()
{
	(*this).mMenu = new cStart_Menu((float)mWindow->getSize().x, (float)mWindow->getSize().y);
}
void cGame::create_GUI()
{
	this->mFont.loadFromFile("Font/PixellettersFull.ttf");
	this->mPoint_txt.setPosition(15, (float)mHight-85);
	this->mPoint_txt.setFont(this->mFont);
	this->mPoint_txt.setCharacterSize(30);
	this->mPoint_txt.setFillColor(sf::Color(221, 197, 162));

	this->mGame_over_txt.setFont(this->mFont);
	this->mGame_over_txt.setCharacterSize(80);
	this->mGame_over_txt.setFillColor(sf::Color::Red);
	this->mGame_over_txt.setPosition((float)mWindow->getSize().x / 2 - 150, (float)mWindow->getSize().y / 2 - 100);
	this->mGame_over_txt.setString("GAME OVER");

	this->mGame_win_txt.setFont(mFont);
	this->mGame_win_txt.setCharacterSize(80);
	this->mGame_win_txt.setFillColor(sf::Color::Magenta);
	this->mGame_win_txt.setPosition((float)mWindow->getSize().x / 2 - 100, (float)mWindow->getSize().y / 2 - 100);
	this->mGame_win_txt.setString("YOUR WIN");

	this->mPlayer_hp_rec.setSize(sf::Vector2f(300, 20));
	this->mPlayer_hp_rec.setFillColor(sf::Color::Red);
	this->mPlayer_hp_rec.setPosition(sf::Vector2f(15, (int)mHight-40));
	this->mPlayer_hp_rec_back = mPlayer_hp_rec;
	this->mPlayer_hp_rec_back.setFillColor(sf::Color(25, 25, 25, 200));

	this->mBoss_hp_rec.setSize(sf::Vector2f(250, 5));
	this->mBoss_hp_rec.setFillColor(sf::Color(9, 216, 243));
	this->mBoss_hop_rec_back = mBoss_hp_rec;
	this->mBoss_hop_rec_back.setFillColor(sf::Color(212, 60, 243, 200));

	this->mShield_time_rec.setSize(sf::Vector2f(90,5));
	this->mShield_time_rec.setFillColor(sf::Color(255, 249, 44));
	this->mShield_time_rec_back = mShield_time_rec;
	this->mShield_time_rec_back.setFillColor(sf::Color(78, 76, 18, 200));

	this->mGame_time_txt.setFont(mFont);
	this->mGame_time_txt.setCharacterSize(20);
	this->mGame_time_txt.setFillColor(sf::Color::White);
	this->mGame_time_txt.setPosition(600, 360);

	this->mGo_press.setFont(mFont);
	this->mGo_press.setCharacterSize(40);
	this->mGo_press.setFillColor(sf::Color::Magenta);
	this->mGo_press.setPosition((float)mWindow->getSize().x / 2, (float)mWindow->getSize().y / 2 - 60);
	this->mGo_press.setString("Press ESC to close the game");
}
void cGame::create_background()
{
	this->mWorld_BG_texture.loadFromFile("Images/BG.jpg");
	this->mWorld_BG.setTexture(this->mWorld_BG_texture);
}

void cGame::create_game_up()
{
	mGame_up = new cGame_update(*mWindow);
}
cGame::cGame()
{
	create_Window();
	create_menu();
	create_GUI();
	create_background();
	create_game_up();
}
cGame::~cGame()
{
	delete this->mGame_up;
	delete this->mWindow;
}
void cGame::window_run()
{
	
	while (this->mWindow->isOpen())
	{
		    double time_g = (double)mClock.getElapsedTime().asSeconds();
			double time = (double)mClock.getElapsedTime().asMicroseconds();
			mClock.restart();
			time = time / 800;
			this->updatePollEvents();
			if (mGame_up->get_player()->get_hp()> 0&&mGame_up->get_boss()->get_hp()>0&&mMenu->get_pressed_key_index_game()==0)
				mGame_up->update();
			this->render();
			mGame_up->set_time_heart(time);
			mGame_up->set_time_shield(time);
			if(mGame_up->get_player()->get_hp()>0&&mMenu->get_pressed_key_index_game()==0)
			mTime_game += time_g;
	}
}
void cGame::updatePollEvents()
{
	sf::Event ev;
	while (this->mWindow->pollEvent(ev))
	{
		switch (ev.type)
		{
			case sf::Event::KeyReleased:
			switch (ev.key.code)
			{
			case sf::Keyboard::Up:
				mMenu->key_pressed_meny_up();
				break;
			case sf::Keyboard::Down:
				mMenu->key_pressed_menu_down();
				break;
			case sf::Keyboard::Return:
				switch (mMenu->get_pressed_item())
				{
				case 0: mMenu->set_pressed_key_index_game(0);
					break;
				case 1: mMenu->set_pressed_key_index_game(1);
					break;
				case 2: mMenu->set_pressed_key_index_game(2);
					break;
				}
			}
			break;
		}
		if (ev.type == sf::Event::KeyPressed)
		{
			/*std::cout << "Key pressed\n";*/
			mGame_up->get_player()->key_pressed(ev, true);
		}
		if (ev.type == sf::Event::KeyReleased)
		{
			/*std::cout << "Key released\n";*/
			mGame_up->get_player()->key_pressed(ev, false);
		}
		if (ev.type == sf::Event::Closed) {
			this->mWindow->close();
		}
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Home) {
			mMenu->set_pressed_key_index_game(3);
		}	
	}
}
void cGame::updateGUI()
{
	std::stringstream ss, ssg;
	ss << "SCORE : " << mGame_up->get_mPoints();
	this->mPoint_txt.setString(ss.str());
	if (mTime_game <= 60) 
	{
		ssg << "TIME: " << std::setprecision(2) << this->mTime_game << " SECONDS";
	}
	else if (mTime_game > 60)
	{
		ssg << "TIME: " << std::setprecision(2) << this->mTime_game/60 << " MINUTES";
	}
	mGame_time_txt.setString(ssg.str());
	float hpPercent = static_cast<float>(mGame_up->get_player()->get_hp()) / mGame_up->get_player()->get_hp_max();
	this->mPlayer_hp_rec.setSize(sf::Vector2f(300.f * hpPercent, this->mPlayer_hp_rec.getSize().y));
	float hp_bosPercent = static_cast<float>(mGame_up->get_boss()->get_hp()) / mGame_up->get_boss()->get_hp_max();
	mBoss_hp_rec.setSize(sf::Vector2f(250.f * hp_bosPercent, mBoss_hp_rec.getSize().y));
	float tik_Per_Cent = static_cast<float>(mGame_up->get_doing() / mGame_up->get_doing_max());
	mShield_time_rec.setSize(sf::Vector2f(90.f * tik_Per_Cent, 5));
}
void cGame::renderGUI()
{
	updateGUI();
	this->mWindow->draw(this->mPoint_txt);
	this->mWindow->draw(this->mPlayer_hp_rec_back);
	this->mWindow->draw(this->mPlayer_hp_rec);
	this->mWindow->draw(this->mBoss_hop_rec_back);
	this->mWindow->draw(this->mBoss_hp_rec);
	if (mGame_up->get_s()) {
		mShield_time_rec_back.setPosition(mGame_up->get_player()->getpos().x, mGame_up->get_player()->getpos().y + 195);
		mShield_time_rec.setPosition(mGame_up->get_player()->getpos().x, mGame_up->get_player()->getpos().y+195);
		this->mWindow->draw(this->mShield_time_rec_back);
		this->mWindow->draw(this->mShield_time_rec);
	}
	if (mGame_up->get_boss()->get_hp() > -30)
	{
		mBoss_hp_rec.setPosition(mGame_up->get_boss()->getpos().x, mGame_up->get_boss()->getpos().y+260);
		mBoss_hop_rec_back.setPosition(mGame_up->get_boss()->getpos().x, mGame_up->get_boss()->getpos().y + 260);
	}
	
}
void cGame::render_world()
{
	this->mWindow->draw(this->mWorld_BG);
}
void cGame::render()
{
	this->mWindow->clear();
	if (mMenu->get_pressed_key_index_game() == 3) 
	{
		this->mMenu->draw_menu(*mWindow);
	}
	if (mMenu->get_pressed_key_index_game() == 1) 
	{
		mMenu->draw_how_to_play(*mWindow);
	}
	if (mMenu->get_pressed_key_index_game() == 0) 
	{
		this->render_world();
		mGame_up->draw();
		mGame_up->get_boss()->draw_obj();
		renderGUI();
	}
		if (mGame_up->get_player()->get_hp()<=0)
		{
			mWindow->clear(sf::Color::Black);
			mWindow->draw(mGame_over_txt);
			mPoint_txt.setPosition((float)mWindow->getSize().x / 2-30, (float)mWindow->getSize().y / 2 - 110);
			mWindow->draw(mPoint_txt);
			mGo_press.setPosition((float)mWindow->getSize().x-420, (float)mWindow->getSize().y -60);
			mWindow->draw(mGo_press);
			mGame_time_txt.setPosition((float)mWindow->getSize().x / 2 - 30, (float)mWindow->getSize().y / 2);
			mWindow->draw(mGame_time_txt);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				mWindow->close();
			}
		}
		if (mGame_up->get_boss()->get_hp() <= 0)
		{
			mWindow->clear(sf::Color::Black);
			mWindow->draw(mGame_win_txt);
			mPoint_txt.setPosition((float)mWindow->getSize().x / 2, (float)mWindow->getSize().y / 2 - 100);
			mWindow->draw(mPoint_txt);
			mGo_press.setPosition((float)mWindow->getSize().x - 420, (float)mWindow->getSize().y - 60);
			mWindow->draw(mGo_press);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				mWindow->close();
			}
		}
		this->mWindow->display();
		if (mMenu->get_pressed_key_index_game() == 2)
		{
			this->mWindow->close();
		}
}
