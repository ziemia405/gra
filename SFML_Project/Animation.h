#pragma once
#include <SFML\Graphics.hpp>

enum class ANIMATION {IDLE=0, WALKING_LEFT=1, WALKING_RIGHT=2, JUMPING_LEFT=3, JUMPING_RIGHT=4, JUMPING=5, FALLING_LEFT=6, FALLING_RIGHT=7, FALLING=8};

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u Im_Counter, float switch_time);
	~Animation();

	sf::IntRect uvRect;
	void update(ANIMATION anim, float delta_time);
private:
	sf::Vector2u Im_Counter;
	sf::Vector2u Im_Actual;

	float total_time;
	float switch_time;


};

