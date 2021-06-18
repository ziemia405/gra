#include "Map.h"

Map::Map(Player* player, Platform* princess, std::vector<Platform*>& platforms): 
	player(player), 
	platforms(platforms),
	princess(princess)
{
	if (player == nullptr)
	{
		throw std::invalid_argument("player cannot be null");
	}

	if (princess == nullptr)
	{
		throw std::invalid_argument("princess cannot be null");
	}

	sf::Vector2f pr_pos = princess->getPosition();
	sf::Vector2f pl_pos = player->getPosition();

	float dx = std::abs(pr_pos.x - pl_pos.x);
	float dy = std::abs(pr_pos.y - pl_pos.y);

	max_dist = std::sqrt(dx * dx + dy * dy);
}

Map::~Map()
{
	delete player;

	for (auto& p : platforms)
	{
		delete p;
	}
}

void Map::draw(sf::RenderWindow& window)
{
	for (auto& pl : platforms)
	{
		pl->draw(window);
	}

	princess->draw(window);
	player->draw(window);
}

bool Map::update(const sf::Time& dt)
{
	sf::Vector2f pr_pos = princess->getPosition();
	sf::Vector2f pl_pos = player->getPosition();

	float dx = std::abs(pr_pos.x - pl_pos.x);
	float dy = std::abs(pr_pos.y - pl_pos.y);

	float dist = std::sqrt(dx * dx + dy * dy);
	player->score = (max_dist-dist)/max_dist * 1000.0f;

	for (auto& pl : platforms)
	{
		pl->update(dt);
	}

	player->update(dt);
	return playerCollisions();
}

bool Map::playerCollisions()
{
	if (player->collision(princess))
	{
		return true; // end game
	}

	for (auto& pl : platforms)
	{
		if (player->collision(pl))
		{
			sf::Vector2f intersection = player->getIntersection(pl);

			if (std::abs(intersection.x) > 0.00001f)
			{
				player->setAcc(-player->getAcc().x, player->getAcc().y);
				player->setVel(-player->getVel().x, player->getVel().y);
			}

			if (std::abs(intersection.y) > 0.00001f)
			{
				player->setAcc(player->getAcc().x, 0.0f);
				player->setVel(player->getVel().x, 0.0f);
			}

			player->move(intersection.x, intersection.y);
		}
	}

	return false;
}

Map* Map::loadFromFile(std::unordered_map<std::string, sf::Texture*>& textures,  const std::string& filename)
{
	Player* player = new Player(textures["player"]);
	std::vector<Platform*> platforms;
	Platform* princess = nullptr;

	std::fstream file(filename, std::ios::in);
	if (!file.good())
		throw std::invalid_argument("couldn't open a map file");

	std::string line;
	float line_ctr = 0.0f;
	while (std::getline(file, line))
	{
		Platform* new_plat = nullptr;
		float pix_w = WIN_W / static_cast<float>(line.size());

		for (int i = 0; i < line.size(); i++)
		{
			float plat_len = 0.0f;
			float plat_xpos = static_cast<float>(i)*pix_w;
			for (int j = i; j < line.size(); j++)
			{
				if (line[j] == 'p')
				{
					player->setPosition(static_cast<float>(j) * pix_w + std::abs(pix_w - player->getSize().x) * 0.5f, PLATFORM_H * (line_ctr+1.0f) - player->getSize().y*0.5f);
				}

				if (line[j] == 'k')
				{
					princess = new Platform(textures["princess"]);
					princess->setPosition(static_cast<float>(j) * pix_w + std::abs(pix_w-princess->getSize().x)*0.5f, PLATFORM_H * (line_ctr+1.0f) - princess->getSize().y*0.5f);
				}

				if (line[j] != '#')
				{
					i = j;
					break;
				}

				plat_len += pix_w;
			}

			if (plat_len > 0.0f)
			{
				new_plat = new Platform(textures["platform"]);
				new_plat->setSize(plat_len, PLATFORM_H);
				new_plat->setPosition(plat_xpos + plat_len*0.5f, line_ctr*PLATFORM_H + PLATFORM_H*0.5f);
				platforms.emplace_back(new_plat);
			}
		}
		line_ctr += 1.0f;
	}

	file.close();
	return new Map(player, princess, platforms);
}
