#include "Platform.h"

Platform::Platform(sf::Texture* texture) : GameObject(texture)
{

}

Platform::~Platform()
{
}

void Platform::update(const sf::Time& dt)
{
}

void Platform::setSize(const float& x, const float& y)
{
	auto size = getSize();
	scale(x / size.x, y / size.y);
}


