#pragma once
#include "GameObject.h"
#include <cmath>
class Player :
    public GameObject
{
private:
    sf::Vector2f m_acc;
    sf::Vector2f m_vel;
    float m_jump_acc;
    float m_jump_timer;
    bool m_jumping;

public:
    float score;

    Player(sf::Texture* texture);
    virtual ~Player();

    virtual void update(const sf::Time& dt) override;
    void updateJumping(const sf::Time& dt);
    void updateMovement(const sf::Time& dt);
    void setAcc(const float& x, const float& y); // values in meters
    void addAcc(const float& x, const float& y, const sf::Time& dt); // values in meters/sec
    sf::Vector2f getAcc() const;
    sf::Vector2f getVel() const;
    void prepareJump(const sf::Time& dt);
    void jump();
    void setVel(const float& x, const float& y);
};

