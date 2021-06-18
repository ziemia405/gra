#pragma once
#include "GameObject.h"
class Platform :
    public GameObject
{
private:

public:
    Platform(sf::Texture* texture);
    virtual ~Platform();
    virtual void update(const sf::Time& dt);
    void setSize(const float& x, const float& y);
};

