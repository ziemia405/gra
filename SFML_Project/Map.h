#pragma once
#include "Player.h"
#include "Platform.h"
#include <fstream>
#include <unordered_map>

struct Map
{
	Player* player;
	std::vector<Platform*> platforms;
	Platform* princess;
	float max_dist;

	Map(Player* player, Platform* princess, std::vector<Platform*>& platforms);
	~Map();

	void draw(sf::RenderWindow& window);
	bool update(const sf::Time& dt);
	bool playerCollisions();

	static Map* loadFromFile(std::unordered_map<std::string, sf::Texture*>& textures, const std::string& filename);
};

