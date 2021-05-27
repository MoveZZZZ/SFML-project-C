#include "cObject.h"

cObject::cObject(sf::RenderWindow& aWin, std::string aFile_link):mWindow(aWin)
{
	this->mTexture.loadFromFile(aFile_link);
	this->mSprite.setTexture(mTexture);
}

const sf::Vector2f& cObject::getpos() const
{
	return mSprite.getPosition();
}

void cObject::draw_obj()
{
	this->mWindow.draw(mSprite);
}
const sf::FloatRect cObject::getGranica() const
{
		return mSprite.getGlobalBounds();
}
