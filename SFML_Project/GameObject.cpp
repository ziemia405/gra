#include "GameObject.h"

GameObject::GameObject(sf::Texture* texture):sf::Sprite(*texture)
{
	setOrigin(getSize() * 0.5f);
}

GameObject::~GameObject()
{
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

bool GameObject::collision(GameObject* obj)
{
	return getGlobalBounds().intersects(obj->getGlobalBounds());
}

sf::Vector2f GameObject::getIntersection(GameObject* obj) const
{
	auto this_rect = getGlobalBounds();
	auto obj_rect = obj->getGlobalBounds();

	sf::Vector2f d = obj->getPosition() - getPosition();

	sf::Vector2f center_distance(
		this_rect.width * 0.5f + obj_rect.width * 0.5f, 
		this_rect.height * 0.5f + obj_rect.height * 0.5f
	);
	
	sf::Vector2f intersection(
		std::abs(d.x) - center_distance.x, 
		std::abs(d.y) - center_distance.y
	);

	sf::Vector2f ret_intersection(0.0f, 0.0f);

	if (intersection.x < 0.0f && intersection.y < 0.0f)
	{
		if (intersection.x > intersection.y)
		{
			if (d.x > 0.0f)
			{
				ret_intersection.x = intersection.x;
			}
			else
			{
				ret_intersection.x = -intersection.x;
			}
		}
		else
		{
			if (d.y > 0.0f)
			{
				ret_intersection.y = intersection.y;
			}
			else
			{
				ret_intersection.y = -intersection.y;
			}
		}
	}

	return ret_intersection;
}

sf::Vector2f GameObject::getSize() const
{
	return sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height);
}
