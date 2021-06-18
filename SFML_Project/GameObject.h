#pragma once
#include <SFML/Graphics.hpp>
#include "gameconst.h"
#include "functions.h"

class GameObject : public sf::Sprite
{
protected:

public:
	GameObject(sf::Texture* texture);
	virtual ~GameObject();

	virtual void draw(sf::RenderWindow& window);
	virtual void update(const sf::Time& dt)=0;
	bool collision(GameObject* obj);
	sf::Vector2f getIntersection(GameObject* obj) const;
	sf::Vector2f getSize() const;
};

