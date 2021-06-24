#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u Im_Counter, float switch_time)
{
	this->Im_Counter = Im_Counter;
	this->switch_time = switch_time;
	total_time = 0.0f;
	Im_Actual.x = 0;
	uvRect.width = texture->getSize().x / float(Im_Counter.x);
	uvRect.height = texture->getSize().y / float(Im_Counter.y);
}


Animation::~Animation()
{}

void Animation::update(ANIMATION anim, float delta_time)
{
	Im_Actual.y = static_cast<int>(anim);
	total_time += delta_time;
	if (total_time >= switch_time)
	{
		total_time -= switch_time;
		Im_Actual.x++;

		if (Im_Actual.x >= Im_Counter.x)
		{
			Im_Actual.x = 0;
		}
	}
	uvRect.left = Im_Actual.x * uvRect.width;
	uvRect.top = Im_Actual.y * uvRect.height;
}
