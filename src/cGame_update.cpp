#include "cGame_update.h"
void cGame_update::create_points_number()
{
	mPoints = 0;
}
void cGame_update::create_Player()
{
	(*this).mPlayer = new cPlayer(mWindow, "Images/player_ship.png");
	mIs_fire = false;
}
void cGame_update::enemy_1_create_time()
{
	mEnemy_1_timer_limit = 50;
	mEnemy_1_timer = mEnemy_1_timer_limit;
}
void cGame_update::enemy_2_create_time()
{
	mEnemy_2_timer_limit = 60;
	mEnemy_2_timer = mEnemy_2_timer_limit;
}
void cGame_update::enemy_3_create_time()
{
	mEnemy_3_timer_limit = 60;
	mEnemy_3_timer = mEnemy_3_timer_limit;
}
void cGame_update::heart_create_time()
{
	mTime_heart= 0;
	mTime_heart_max = 24000;
}
void cGame_update::shield_create_time()
{
	mTime_shield = 0;
	mTime_shield_max = 50000;
	mTime_shield_doing = 0;
	mTime_shield_doing_max = 1000;
	mShield_is_going = false;
}
void cGame_update::create_boss()
{
	(*this).mBoss = new cBoss(mWindow, "images/boss.png");
}
cGame_update::cGame_update(sf::RenderWindow&win):mWindow(win)
{
	create_points_number();
	create_Player();
	enemy_1_create_time();
	enemy_2_create_time();
	enemy_3_create_time();
	heart_create_time();
	shield_create_time();
	create_boss();
	cr_men();
}
cGame_update::~cGame_update()
{
	delete mPlayer;
	delete mBoss;
	for (auto* i : mVector_enemy_1)
	{
		delete i;
	}
	for (auto* i : mVector_enemy_2)
	{
		delete i;
	}
	for (auto* i : mVector_enemy_3)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_player)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_boss_1)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_boss_2)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_boss_3)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_boss_4)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_enemy_1)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_enemy_2)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_enemy_3_gun_1)
	{
		delete i;
	}
	for (auto* i : mBullet_vector_enemy_3_gun_2)
	{
		delete i;
	}
}
void cGame_update::update()
{
			update_keyboard_fire_player();
			update_player();
			update_bullet_player();
			update_hp_player();
			//if (mPoints <= 150 || mPoints >= 500)
				create_and_update_enemy_1();
			//if (mPoints > 150 && mPoints < 300)
				create_and_update_enemy_2();
			//if (mPoints >= 300 && mPoints < 500)
				create_and_update_enemy_3();
			if (mPoints >= 500)
				create_and_update_boss();
			kill_enemy();
			create_and_update_heart();
			create_and_update_shield();
			update_shield_going_timer();
	
}
void cGame_update::update_player()
{
	this->mPlayer->update_position();
	this->mPlayer->attack_cd();
}
void cGame_update::update_keyboard_fire_player()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&mPlayer->attack())
	{
		mBullet_vector_player.push_back(new cBullet(mPlayer->getpos().x + 40, mPlayer->getpos().y, 0, -1, 5, sf::Color(255, 215, 0)));
		mIs_fire = true;
	}
	mIs_fire = false;
}
void cGame_update::update_bullet_player()
{
	unsigned count_bullet_mPlayer = 0;
	for(auto*bullet_mPlayer: mBullet_vector_player)
	{
		bullet_mPlayer->update_bullet();
		if (bullet_mPlayer->getGranica().top + bullet_mPlayer->getGranica().height < 0)
		{
			delete mBullet_vector_player.at(count_bullet_mPlayer);
			mBullet_vector_player.erase(mBullet_vector_player.begin() + count_bullet_mPlayer);
		}
		count_bullet_mPlayer++;
	}
}
void cGame_update::update_hp_player()
{
	unsigned counter_enemy_1_update_mPlayer_hp = 0;
	unsigned counter_enemy_2_update_mPlayer_hp = 0;
	unsigned counter_enemy_3_1_update_mPlayer_hp = 0;
	unsigned counter_enemy_3_2_update_mPlayer_hp = 0;
	for (size_t i = 0; i < mVector_enemy_1.size(); i++)
	{
		for (size_t j = 0; j < mBullet_vector_enemy_1.size();j++)
		{
			if (mPlayer->getGranica().intersects(mBullet_vector_enemy_1[j]->getGranica()))
			{
				if (!mShield_is_going)
				{
					mPlayer->minus_hp(mVector_enemy_1.at(counter_enemy_1_update_mPlayer_hp)->get_damage());
				}
				delete mBullet_vector_enemy_1[j];
				mBullet_vector_enemy_1.erase(mBullet_vector_enemy_1.begin() + j);
			}
		}
		counter_enemy_1_update_mPlayer_hp++;
	}
	for (size_t c = 0; c < mVector_enemy_2.size(); c++)
	{
		for (size_t v = 0; v < mBullet_vector_enemy_2.size(); v++)
		{
			if (mPlayer->getGranica().intersects(mBullet_vector_enemy_2[v]->getGranica()))
			{
				if (!mShield_is_going)
				{
					mPlayer->minus_hp(mVector_enemy_2.at(counter_enemy_2_update_mPlayer_hp)->get_damage());
				}
				delete mBullet_vector_enemy_2[v];
				mBullet_vector_enemy_2.erase(mBullet_vector_enemy_2.begin() + v);
			}
		}
		counter_enemy_2_update_mPlayer_hp++;
	}
	for (size_t n = 0; n < mVector_enemy_3.size(); n++)
	{
		for (size_t enemy_3_1 = 0; enemy_3_1 < mBullet_vector_enemy_3_gun_1.size(); enemy_3_1++)
		{
			if (mPlayer->getGranica().intersects(mBullet_vector_enemy_3_gun_1[enemy_3_1]->getGranica()))
			{
				if (!mShield_is_going)
				{
					mPlayer->minus_hp(mVector_enemy_3.at(counter_enemy_3_1_update_mPlayer_hp)->get_damage());
				}
				delete mBullet_vector_enemy_3_gun_1[enemy_3_1];
				mBullet_vector_enemy_3_gun_1.erase(mBullet_vector_enemy_3_gun_1.begin() + enemy_3_1);
			}
		}
		counter_enemy_3_1_update_mPlayer_hp++;
		for (size_t enemy_3_2 = 0; enemy_3_2 < mBullet_vector_enemy_3_gun_2.size(); enemy_3_2++)
		{
			if (mPlayer->getGranica().intersects(mBullet_vector_enemy_3_gun_2[enemy_3_2]->getGranica()))
			{
				if (!mShield_is_going)
				{
					mPlayer->minus_hp(mVector_enemy_3.at(counter_enemy_3_2_update_mPlayer_hp)->get_damage());
				}
				delete mBullet_vector_enemy_3_gun_2[enemy_3_2];
				mBullet_vector_enemy_3_gun_2.erase(mBullet_vector_enemy_3_gun_2.begin() + counter_enemy_3_2_update_mPlayer_hp);
			}
		}
		counter_enemy_3_2_update_mPlayer_hp++;
	}
	for (size_t mBoss_gun_1 = 0; mBoss_gun_1 < mBullet_vector_boss_1.size(); mBoss_gun_1++)
	{
		if (mPlayer->getGranica().intersects(mBullet_vector_boss_1[mBoss_gun_1]->getGranica()))
		{
			if (!mShield_is_going)
			{
				mPlayer->minus_hp(mBoss->get_damage_boss());
			}
			delete mBullet_vector_boss_1.at(mBoss_gun_1);
			mBullet_vector_boss_1.erase(mBullet_vector_boss_1.begin() + mBoss_gun_1);
		}
	}
	for (size_t mBoss_gun_2 = 0; mBoss_gun_2 < mBullet_vector_boss_2.size(); mBoss_gun_2++)
	{
		if (mPlayer->getGranica().intersects(mBullet_vector_boss_2[mBoss_gun_2]->getGranica()))
		{
			if (!mShield_is_going)
			{
				mPlayer->minus_hp(mBoss->get_damage_boss());
			}
			delete mBullet_vector_boss_2.at(mBoss_gun_2);
			mBullet_vector_boss_2.erase(mBullet_vector_boss_2.begin() + mBoss_gun_2);
		}
	}
	for (size_t mBoss_gun_3 = 0; mBoss_gun_3 < mBullet_vector_boss_3.size(); mBoss_gun_3++)
	{
		if (mPlayer->getGranica().intersects(mBullet_vector_boss_3[mBoss_gun_3]->getGranica()))
		{
			if (!mShield_is_going)
			{
				mPlayer->minus_hp(mBoss->get_damage_boss());
			}
			delete mBullet_vector_boss_3.at(mBoss_gun_3);
			mBullet_vector_boss_3.erase(mBullet_vector_boss_3.begin() + mBoss_gun_3);
		}
	}
	for (size_t mBoss_gun_4 = 0; mBoss_gun_4 < mBullet_vector_boss_4.size(); mBoss_gun_4++)
	{
		if (mPlayer->getGranica().intersects(mBullet_vector_boss_4[mBoss_gun_4]->getGranica()))
		{
			if (!mShield_is_going)
			{
				mPlayer->minus_hp(mBoss->get_damage_boss());
			}
			delete mBullet_vector_boss_4.at(mBoss_gun_4);
			mBullet_vector_boss_4.erase(mBullet_vector_boss_4.begin() + mBoss_gun_4);
		}
	}
}
void cGame_update::create_and_update_bullets_enemy_1()
{
	unsigned count_bullet_enemy_1 = 0;
	//create bullet_enemy_1
	for (unsigned i = 0; i < mVector_enemy_1.size(); i++)
	{
		if (rand() % 35 == 10)
		{
			mBullet_vector_enemy_1.push_back(new cBullet(mVector_enemy_1[i]->getpos().x + 40, mVector_enemy_1[i]->getpos().y + 70, 0, 1, 5, sf::Color(0, 124, 173)));
		}
	}
	//update bullet_enemy_1
	for (auto* bullet_enemy_1 : mBullet_vector_enemy_1)
	{
		bullet_enemy_1->update_bullet();
		if (bullet_enemy_1->getGranica().top + bullet_enemy_1->getGranica().height < 0)
		{
			delete mBullet_vector_enemy_1.at(count_bullet_enemy_1);
			mBullet_vector_enemy_1.erase(mBullet_vector_enemy_1.begin() + count_bullet_enemy_1);
		}
		count_bullet_enemy_1++;
	}
}
void cGame_update::create_and_update_enemy_1()
{
	mEnemy_1_timer += 0.5;
	int count_enemy_1 = 0;
	//create enemy_1
	if (mEnemy_1_timer >= mEnemy_1_timer_limit && (mPoints <= 150 || mPoints >= 500))
	{
		mVector_enemy_1.push_back(new cEnemy_type_1(mWindow, "Images/enemy_1.png", rand() % (int)mWindow.getSize().x - 50, -100));
		mEnemy_1_timer = 0;
	}
	//update enemy_1
	for (auto* enemy_1 : mVector_enemy_1)
	{
			enemy_1->update_position();
			create_and_update_bullets_enemy_1();

			//delete enemy 
			if (enemy_1->getGranica().top > mWindow.getSize().y)
			{
				if (mPoints > 0)
					mPoints--;
				delete mVector_enemy_1.at(count_enemy_1);
				mVector_enemy_1.erase(mVector_enemy_1.begin() + count_enemy_1);
			}
			else if (enemy_1->getGranica().intersects(mPlayer->getGranica()))
			{
				mPlayer->minus_hp(1);
				delete mVector_enemy_1.at(count_enemy_1);
				mVector_enemy_1.erase(mVector_enemy_1.begin() + count_enemy_1);
			}
			count_enemy_1++;
	}
}
void cGame_update::create_and_update_bullets_enemy_2()
{
	//create bullet enemy_2
	unsigned count_bullet_enemy_2 = 0;
	for (unsigned i = 0; i < mVector_enemy_2.size(); i++)
	{
		if (rand() % 40 == 10)
		{
			mBullet_vector_enemy_2.push_back(new cBullet(mVector_enemy_1[i]->getpos().x + 40, mVector_enemy_1[i]->getpos().y + 70, 0, 1, 6, sf::Color(255, 0, 0)));
		}
	}
	//update bullet_enemy_2
	for (auto* bullet_enemy_2 : mBullet_vector_enemy_2)
	{
		bullet_enemy_2->update_bullet();
		if (bullet_enemy_2->getGranica().top + bullet_enemy_2->getGranica().height < 0)
		{
			delete mBullet_vector_enemy_2.at(count_bullet_enemy_2);
			mBullet_vector_enemy_2.erase(mBullet_vector_enemy_2.begin() + count_bullet_enemy_2);
		}
		count_bullet_enemy_2++;
	}
}
void cGame_update::create_and_update_enemy_2()
{
	mEnemy_2_timer += 0.5;
	int count_enemy_2 = 0;
	//create enemy_2
	if (mEnemy_2_timer >= mEnemy_2_timer_limit && (mPoints > 150 && mPoints <= 300))
	{
		mVector_enemy_2.push_back(new cEnemy_type_2(mWindow, "Images/enemy_2.png", rand() % (int)mWindow.getSize().x - 50, -100));
		mEnemy_2_timer = 0;
	}
	//update enemy_2
	for (auto* enemy_2 : mVector_enemy_2)
	{
		enemy_2->update_position();
		create_and_update_bullets_enemy_2();

		//delete enemy 
		if (enemy_2->getGranica().top > mWindow.getSize().y)
		{
			if (mPoints > 0)
				mPoints--;
			delete mVector_enemy_2.at(count_enemy_2);
			mVector_enemy_2.erase(mVector_enemy_2.begin() + count_enemy_2);
		}
		else if (enemy_2->getGranica().intersects(mPlayer->getGranica()))
		{
			mPlayer->minus_hp(3);
			delete mVector_enemy_2.at(count_enemy_2);
			mVector_enemy_2.erase(mVector_enemy_2.begin() + count_enemy_2);
		}
		count_enemy_2++;
	}
}
void cGame_update::create_and_update_bullets_enemy_3()
{
	unsigned count_bullet_enemy_3_gun_1 = 0;
	unsigned count_bullet_enemy_3_gun_2 = 0;
	//create bullet enemy_3
	for (unsigned i = 0; i < mVector_enemy_3.size(); i++)
	{
		if (rand() % 50 == 10)
		{
			mBullet_vector_enemy_3_gun_1.push_back(new cBullet(mVector_enemy_3[i]->getpos().x + 13, mVector_enemy_3[i]->getpos().y + 80, 0, 1, 7, sf::Color::Magenta));
			mBullet_vector_enemy_3_gun_2.push_back(new cBullet(mVector_enemy_3[i]->getpos().x + 76, mVector_enemy_3[i]->getpos().y + 80, 0, 1, 7, sf::Color::Magenta));
		}
	}
	//update bullet enemy_3_gun_1
	for (auto* bullet_enemy_3_gun_1 : mBullet_vector_enemy_3_gun_1)
	{
		bullet_enemy_3_gun_1->update_bullet();
		if (bullet_enemy_3_gun_1->getGranica().top + bullet_enemy_3_gun_1->getGranica().height < 0)
		{
			delete mBullet_vector_enemy_3_gun_1.at(count_bullet_enemy_3_gun_1);
			mBullet_vector_enemy_3_gun_1.erase(mBullet_vector_enemy_3_gun_1.begin() + count_bullet_enemy_3_gun_1);

		}
		count_bullet_enemy_3_gun_1++;
	}
	//update bullet enemy_3_gun_2
	for (auto* bullet_enemy_3_gun_2 : mBullet_vector_enemy_3_gun_2)
	{
		bullet_enemy_3_gun_2->update_bullet();
		if (bullet_enemy_3_gun_2->getGranica().top + bullet_enemy_3_gun_2->getGranica().height < 0)
		{
			delete mBullet_vector_enemy_3_gun_2.at(count_bullet_enemy_3_gun_2);
			mBullet_vector_enemy_3_gun_2.erase(mBullet_vector_enemy_3_gun_2.begin() + count_bullet_enemy_3_gun_2);
		}
		count_bullet_enemy_3_gun_2++;
	}
}
void cGame_update::create_and_update_enemy_3()
{
	mEnemy_3_timer += 0.5;
	unsigned count_enemy_3 = 0;
	if (mEnemy_3_timer >= mEnemy_3_timer_limit &&(mPoints>300&&mPoints<=500))
	{
		mVector_enemy_3.push_back(new cEnemy_type_3(mWindow, "Images/enemy_3.png", rand() % mWindow.getSize().x, -100));
		mEnemy_3_timer = 0;
	}
	for (auto* enemy_3 : mVector_enemy_3)
	{
		enemy_3->update_position();
		create_and_update_bullets_enemy_3();
		if (enemy_3->getGranica().top > mWindow.getSize().y)
		{
			if (mPoints > 0)
				mPoints--;
			delete mVector_enemy_3.at(count_enemy_3);
			mVector_enemy_3.erase(mVector_enemy_3.begin() + count_enemy_3);
		}
		else if (enemy_3->getGranica().intersects(mPlayer->getGranica()))
		{
			mPlayer->minus_hp(5);
			delete mVector_enemy_3.at(count_enemy_3);
			mVector_enemy_3.erase(mVector_enemy_3.begin() + count_enemy_3);
		}
		count_enemy_3++;
	}
}
void cGame_update::create_and_update_bullets_boss()
{
	if (rand() % 60 == 10)
	{
		mBullet_vector_boss_1.push_back(new cBullet(mBoss->getpos().x, mBoss->getpos().y + 125, static_cast<float>(rand() % 2000 - 1400) / 1000, 1, 3, sf::Color(255, 168, 18)));
		mBullet_vector_boss_2.push_back(new cBullet(mBoss->getpos().x + 224, mBoss->getpos().y + 125, -static_cast<float>(rand() % 2000 - 1400) / 1000, 1, 3, sf::Color(255, 168, 18)));
		mBullet_vector_boss_3.push_back(new cBullet(mBoss->getpos().x + 51, mBoss->getpos().y + 230, 0, 1, 6, sf::Color(250, 109, 221)));
		mBullet_vector_boss_4.push_back(new cBullet(mBoss->getpos().x + 198, mBoss->getpos().y + 230, 0, 1, 6, sf::Color(250, 109, 221)));
	}
	unsigned count_mBoss_gun_1 = 0;
	unsigned count_mBoss_gun_2 = 0;
	unsigned count_mBoss_gun_3 = 0;
	unsigned count_mBoss_gun_4 = 0;
	for (auto* mBoss_gun_1 : mBullet_vector_boss_1)
	{
		mBoss_gun_1->update_bullet();
		if (mBoss_gun_1->getGranica().top + mBoss_gun_1->getGranica().height < 0)
		{
			delete mBullet_vector_boss_1.at(count_mBoss_gun_1);
			mBullet_vector_boss_1.erase(mBullet_vector_boss_1.begin() + count_mBoss_gun_1);
		}
		count_mBoss_gun_1++;
	}
	for (auto* mBoss_gun_2 : mBullet_vector_boss_2)
	{
		mBoss_gun_2->update_bullet();
		if (mBoss_gun_2->getGranica().top + mBoss_gun_2->getGranica().height < 0)
		{
			delete mBullet_vector_boss_2.at(count_mBoss_gun_2);
			mBullet_vector_boss_2.erase(mBullet_vector_boss_2.begin() + count_mBoss_gun_2);
		}
		count_mBoss_gun_2++;
	}
	for(auto * mBoss_gun_3:mBullet_vector_boss_3)
	{
		mBoss_gun_3->update_bullet();
		if (mBoss_gun_3->getGranica().top + mBoss_gun_3->getGranica().height < 0)
		{
			delete mBullet_vector_boss_3.at(count_mBoss_gun_3);
			mBullet_vector_boss_3.erase(mBullet_vector_boss_3.begin() + count_mBoss_gun_3);
		}
		count_mBoss_gun_3++;
	}
	for (auto* bullet_gun_4 : mBullet_vector_boss_4)
	{
		bullet_gun_4->update_bullet();
		if (bullet_gun_4->getGranica().top + bullet_gun_4->getGranica().height < 0)
		{
			delete mBullet_vector_boss_4.at(count_mBoss_gun_4);
			mBullet_vector_boss_4.erase(mBullet_vector_boss_4.begin() + count_mBoss_gun_4);
		}
		count_mBoss_gun_4++;
	}

}
void cGame_update::create_and_update_boss()
{
	//create mBoss
	if (mPoints > 500)
	{
		(*this).mBoss = new cBoss(mWindow, "Images/mBoss.png");
	}
	//update position mBoss
	if (mBoss->getpos().y <= 10)
	{
		mBoss->update_position();
	}
	else
	{
		mBoss->update_position_2();
		if (mBoss->getpos().x + mBoss->getGranica().width < 0)
		{
			mBoss->set_pos(mWindow.getSize().x, (const int)mBoss->getpos().y);
		}
	}
	create_and_update_bullets_boss();
}
void cGame_update::create_and_update_heart()
{
	int counert_heart = 0;
	if (mTime_heart>= mTime_heart_max)
	{
		mVector_heart.push_back(new cHeart_item(mWindow, "Images/heart.png", rand() % mWindow.getSize().x, -100));
		std::cout << mVector_heart[counert_heart]->getpos().x << "  " << mVector_heart[counert_heart]->getpos().y << std::endl;
		mTime_heart_max = (double)(rand()) / RAND_MAX * (30000 - 15000) + 15000;
		std::cout << mTime_heart_max << std::endl;
		mTime_heart= 0;
	}
	for (auto* heart : mVector_heart)
	{
		heart->update_position();
		if (heart->getGranica().top > mWindow.getSize().y)
		{
			delete mVector_heart.at(counert_heart);
			mVector_heart.erase(mVector_heart.begin() + counert_heart);
		}
		if (heart->getGranica().intersects(mPlayer->getGranica()))
		{
			mPlayer->plus_hp(heart->get_update_hp());
			delete mVector_heart.at(counert_heart);
			mVector_heart.erase(mVector_heart.begin() + counert_heart);
		}
		counert_heart++;
	}
}
void cGame_update::create_and_update_shield()
{
	int counter_shield = 0;
	if (mTime_shield >= mTime_shield_max)
	{
		mVector_shield.push_back(new cShield_item(mWindow, "Images/shield.png", rand() % mWindow.getSize().x, -100));
		{
			mTime_shield_max = (double)(rand()) / RAND_MAX * (70000 - 35000) + 35000;
			mTime_shield = 0;
		}
	}
	for (auto* shield : mVector_shield)
	{
		shield->update_position();
		if (shield->getGranica().top > mWindow.getSize().y)
		{
			delete mVector_shield.at(counter_shield);
			mVector_shield.erase(mVector_shield.begin() + counter_shield);
		}
		if (shield->getGranica().intersects(mPlayer->getGranica()))
		{
			mShield_is_going = true;
			delete mVector_shield.at(counter_shield);
			mVector_shield.erase(mVector_shield.begin() + counter_shield);
		}
	}
}
void cGame_update::update_shield_going_timer()
{
	if (mShield_is_going)
	{
		mTime_shield_doing += 1;
		if (mTime_shield_doing >= mTime_shield_doing_max)
		{
			mTime_shield_doing = 0;
			mShield_is_going = false;
		}
	}
}
void cGame_update::kill_enemy()
{
	for (unsigned i = 0; i < mVector_enemy_1.size(); i++)
	{
		bool enemy_1_dye = false;
		for (size_t k = 0; k < mBullet_vector_player.size()&&enemy_1_dye==false; k++)
		{
			if (mVector_enemy_1[i]->getGranica().intersects(mBullet_vector_player[k]->getGranica()))
			{
				mPoints += mVector_enemy_1.at(i)->get_score();
				delete mVector_enemy_1.at(i);
				mVector_enemy_1.erase(mVector_enemy_1.begin() + i);
				delete mBullet_vector_player.at(k);
				mBullet_vector_player.erase(mBullet_vector_player.begin() + k);
				enemy_1_dye = true;
			}
		}
	}
	for (unsigned j = 0; j < mVector_enemy_2.size(); j++)
	{
		bool enemy_2_dye = false;
		for (size_t l = 0; l < mBullet_vector_player.size() && enemy_2_dye == false; l++)
		{
			if (mVector_enemy_2[j]->getGranica().intersects(mBullet_vector_player[l]->getGranica()))
			{
				mPoints += mVector_enemy_2.at(j)->get_score();
				delete mVector_enemy_2.at(j);
				mVector_enemy_2.erase(mVector_enemy_2.begin() + j);
				delete mBullet_vector_player.at(l);
				mBullet_vector_player.erase(mBullet_vector_player.begin() + l);
				enemy_2_dye = true;
			}
		}
	}
	for (unsigned p = 0; p < mVector_enemy_3.size(); p++)
	{
		bool enemy_3_dye = false;
		for (size_t q = 0; q < mBullet_vector_player.size()&&enemy_3_dye==false; q++)
		{
			if (mVector_enemy_3[p]->getGranica().intersects(mBullet_vector_player[q]->getGranica()))
			{
				mPoints += mVector_enemy_3.at(p)->get_score();
				delete mVector_enemy_3.at(p);
				mVector_enemy_3.erase(mVector_enemy_3.begin() + p);
				delete mBullet_vector_player.at(q);
				mBullet_vector_player.erase(mBullet_vector_player.begin() + p);
				enemy_3_dye = true;
			}
		}
	}
	for (size_t b = 0; b < mBullet_vector_player.size(); b++)
	{
		if (mBoss->getGranica().intersects(mBullet_vector_player[b]->getGranica()))
		{
			mBoss->hp_minus(mPlayer->get_damage_player());
			delete mBullet_vector_player.at(b);
			mBullet_vector_player.erase(mBullet_vector_player.begin() + b);
		}
	}
}
void cGame_update::set_time_heart(double aTime_h)
{
	mTime_heart+= aTime_h;
}
void cGame_update::set_time_shield(double aTime_s)
{
	mTime_shield += aTime_s;
}
cPlayer *cGame_update::get_player()
{
	return mPlayer;
}
cBoss *cGame_update::get_boss()
{
	return mBoss;
}
void cGame_update::draw()
{
	mPlayer->draw_obj();
	for (auto* bull : mBullet_vector_player)
	{
		bull->draw_bullet(&mWindow);
	}
	for (auto* e_1 : mVector_enemy_1)
	{
		e_1->draw_obj();
	}
	for (auto* e_2 : mVector_enemy_2)
	{
		e_2->draw_obj();
	}
	for (auto* e_3 : mVector_enemy_3)
	{
		e_3->draw_obj();
	}
	for(auto * b_1:mBullet_vector_enemy_1)
	{
		b_1->draw_bullet(&mWindow);
	}
	for (auto* b_2 : mBullet_vector_enemy_2)
	{
		b_2->draw_bullet(&mWindow);
	}
	for (auto* b_3_1 : mBullet_vector_enemy_3_gun_1)
	{
		b_3_1->draw_bullet(&mWindow);
	}
	for (auto* b_3_2 : mBullet_vector_enemy_3_gun_2)
	{
		b_3_2->draw_bullet(&mWindow);
	}
	for (auto* b_b_1 : mBullet_vector_boss_1)
	{
		b_b_1->draw_bullet(&mWindow);
	}
	for (auto* b_b_2 : mBullet_vector_boss_2)
	{
		b_b_2->draw_bullet(&mWindow);
	}
	for (auto* b_b_3 : mBullet_vector_boss_3)
	{
		b_b_3->draw_bullet(&mWindow);
	}
	for (auto* b_b_4 : mBullet_vector_boss_4)
	{
		b_b_4->draw_bullet(&mWindow);
	}
	for (auto* heart : mVector_heart)
	{
		heart->draw_obj();
	}
	for (auto* shield : mVector_shield)
	{
		shield->draw_obj();
	}
}
bool cGame_update::get_s()
{
	return mShield_is_going;
}
unsigned short cGame_update::get_mPoints() const
{
	return mPoints;
}
double cGame_update::get_doing_max()
{
	return mTime_shield_doing_max;
}
double cGame_update::get_doing()
{
	return mTime_shield_doing;
}
bool cGame_update::get_is_fire_player()
{
	return mIs_fire;
}
