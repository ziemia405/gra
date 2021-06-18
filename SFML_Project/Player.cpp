#include "Player.h"

Player::Player(sf::Texture* texture) : GameObject(texture), m_jump_timer(0.0f), m_jumping(true), m_jump_acc(0.0f), score(0.0f)
{
}

Player::~Player()
{
}
#include <iostream>
void Player::update(const sf::Time& dt)
{
	//std::cout << m_acc.x << " " << m_acc.y << ", " << m_vel.x << " " << m_vel.y << " jumping->" << m_jumping << ", time->"<<m_jump_timer<< "\n";

	updateJumping(dt);
	updateMovement(dt);
}

void Player::updateJumping(const sf::Time& dt)
{
	m_jumping = !(m_vel.y == 0.0f);
	if(m_jump_acc<0.0f)	m_jump_acc += GRAVITY * METER * dt.asSeconds();
}

void Player::updateMovement(const sf::Time& dt)
{
	m_vel *= 0.999f;

	if (std::abs(m_acc.x) < 1.0f)
	{
		m_acc.x = 0.0f;
	}

	if (std::abs(m_acc.y) < 1.0f)
	{
		m_acc.y = 0.0f;
	}

	if (std::abs(m_vel.x) < 1.0f)
	{
		m_vel.x = 0.0f;
	}

	if (std::abs(m_vel.y) < 1.0f)
	{
		m_vel.y = 0.0f;
	}

	m_vel += m_acc * dt.asSeconds();
	m_vel.y += METER * GRAVITY * dt.asSeconds(); // gravity
	m_vel.y += METER * m_jump_acc * dt.asSeconds(); // jump

	m_vel.x = clamp(m_vel.x, -MAX_X_SPEED, MAX_X_SPEED);
	m_vel.y = clamp(m_vel.y, -MAX_Y_SPEED, MAX_Y_SPEED);

	move(m_vel * dt.asSeconds());
}

void Player::setAcc(const float& x, const float& y)
{
	if (m_jumping) return;

	m_acc.x = x * METER;
	m_acc.y = y * METER;
}

void Player::addAcc(const float& x, const float& y, const sf::Time& dt)
{
	if (m_jumping) return;

	m_acc.x += x * METER * dt.asSeconds();
	m_acc.y += y * METER * dt.asSeconds();
}

sf::Vector2f Player::getAcc() const
{
	return m_acc;
}

sf::Vector2f Player::getVel() const
{
	return m_vel;
}

void Player::prepareJump(const sf::Time& dt)
{
	if (m_jumping) return;

	m_jump_timer += dt.asSeconds();
	m_jump_timer = clamp(m_jump_timer, 0.0f, MAX_JUMP_LEN);

	if (m_jump_timer >= MAX_JUMP_LEN) jump();
}

void Player::jump()
{	
	if (m_jumping) return;
	if (m_jump_timer < 0.01f) return;
	m_jump_acc = -arduino_map(m_jump_timer, 0.0f, MAX_JUMP_LEN, 100.0f, 200.0f);
	m_jump_timer = 0.0f;
	m_jumping = true;
}

void Player::setVel(const float& x, const float& y)
{
	m_vel.x = x;
	m_vel.y = y;
}

