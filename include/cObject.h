#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
class cObject
{
protected:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    sf::RenderWindow& mWindow;
public:
    cObject(sf::RenderWindow& aWin, std::string aFile_link);
    const sf::Vector2f& getpos() const;
    virtual void draw_obj();
    virtual void update_position()=0;
    const sf::FloatRect getGranica() const;
};

