#include "Game.h"
#include "gameconst.h"

Game::Game() : 
	m_window(sf::VideoMode(WIN_W, WIN_H), "Ice Jump King"),
	m_map(nullptr),
	m_cam(sf::View(sf::Vector2f(WIN_W, WIN_H)*0.5f, sf::Vector2f(WIN_W, WIN_H))),
	m_game_over(false),
	m_screen_bg(sf::Vector2f(WIN_W, WIN_H)),
	m_next_map_btn(sf::Vector2f(260.0f, 80.0f)),
	m_map_idx(0)
{
	loadTextures();

	m_map_filenames.emplace_back("map1.map");
	m_map_filenames.emplace_back("map2.map");
	m_map_filenames.emplace_back("map3.map");

	m_screen_bg.setFillColor(sf::Color(0, 0, 0, 180));
	m_font.loadFromFile("assets/font.ttf");

	m_next_map_btn.setOrigin(130.0f, 40.0f);
	m_next_map_btn.setFillColor(sf::Color(96, 14, 102));
	
	m_btn_text.setFont(m_font);
	m_btn_text.setString("Next map!");
	m_btn_text.setFillColor(sf::Color::White);
	m_btn_text.setCharacterSize(42u);

	m_score_text.setFont(m_font);
	m_score_text.setString("Score: 0");
	m_score_text.setFillColor(sf::Color::White);
	m_score_text.setCharacterSize(32u);

	m_game_over_text.setFont(m_font);
	m_game_over_text.setString("Game Over!");
	m_game_over_text.setFillColor(sf::Color::White);
	m_game_over_text.setCharacterSize(50u);

	m_map = Map::loadFromFile(m_textures, m_map_filenames[m_map_idx]);
}

Game::~Game()
{
	delete m_map;
}

void Game::events()
{
	sf::Event event;
	if (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Game::loop()
{
	while (m_window.isOpen())
	{
		events();
		m_window.clear();
		update();
		draw();
		
		if (m_game_over)
		{
			gameOver();
		}
		else
		{
			keyboardInput();
		}

		
		m_window.display();
	}
}

void Game::loadTextures()
{
	sf::Texture* player_texture = new sf::Texture();
	player_texture->loadFromFile("assets/player.png");
	m_textures.insert(std::make_pair("player", player_texture));

	sf::Texture* platform_texture = new sf::Texture();
	platform_texture->loadFromFile("assets/platform.png");
	m_textures.insert(std::make_pair("platform", platform_texture));

	sf::Texture* princess_texture = new sf::Texture();
	princess_texture->loadFromFile("assets/princess.png");
	m_textures.insert(std::make_pair("princess", princess_texture));
}

void Game::keyboardInput()
{
	float x_acc = 0.0f;
	//float y_acc = 0.0f;

	bool l_a = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool r_a = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (l_a) x_acc = -10.0f;
	if (r_a) x_acc = 10.0f;

	if (space) m_map->player->prepareJump(m_dt);
	else m_map->player->jump();

	m_map->player->setAcc(x_acc, m_map->player->getAcc().y);
}

void Game::updateCam()
{
	m_window.setView(m_cam);
	int cam_y = std::floor(m_map->player->getPosition().y / WIN_H) * WIN_H + WIN_H*0.5f;
	m_cam.setCenter(WIN_W*0.5f, cam_y);
}

void Game::updateScore()
{
	if (m_game_over) return;

	m_score_text.setString("Score: " + std::to_string(static_cast<int>(m_map->player->score)));
	auto rect = m_score_text.getGlobalBounds();
	auto cam_pos = m_cam.getCenter();

	float xpos = (WIN_W - rect.width)*0.5f;
	float ypos = cam_pos.y - WIN_H*0.5f + 10.0f;
	m_score_text.setPosition(xpos,ypos);
}

void Game::update()
{
	m_dt = m_timer.restart(); // update deleta time
	if (m_map->update(m_dt))
	{
		m_game_over = true;
	}
	updateCam();
	updateScore();
}

void Game::gameOver()
{
	m_map->player->setVel(0.0f, 0.0f);
	m_map->player->setAcc(0.0f, 0.0f);

	sf::Vector2f center_pos = m_cam.getCenter() -sf::Vector2f(WIN_W, WIN_H) * 0.5f;
	m_screen_bg.setPosition(center_pos);

	m_score_text.setCharacterSize(42u);
	m_score_text.setPosition(center_pos.x + WIN_W*0.5f - m_score_text.getGlobalBounds().width*0.5f, center_pos.y + WIN_H*0.5f - 50.0f);

	m_game_over_text.setPosition(center_pos.x + WIN_W*0.5f - m_game_over_text.getGlobalBounds().width * 0.5f, center_pos.y+ WIN_H*0.5f - 200.0f);
	
	m_next_map_btn.setPosition(m_cam.getCenter() + sf::Vector2f(0.0f, 150.0f));
	m_btn_text.setPosition(m_cam.getCenter().x - m_btn_text.getGlobalBounds().width*0.5f, m_next_map_btn.getPosition().y - 32.0f);
	
	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)) + center_pos;
	auto btn_r = m_next_map_btn.getGlobalBounds();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		mouse_pos.x >= btn_r.left && 
		mouse_pos.x <= btn_r.left + btn_r.width &&
		mouse_pos.y >= btn_r.top && 
		mouse_pos.y <= btn_r.top + btn_r.height
		)
	{
		m_game_over = false;
		m_map_idx = (m_map_idx + 1) % m_map_filenames.size();
		m_map = Map::loadFromFile(m_textures, m_map_filenames[m_map_idx]);
	}


	m_window.draw(m_screen_bg);
	m_window.draw(m_game_over_text);
	m_window.draw(m_score_text);
	m_window.draw(m_next_map_btn);
	m_window.draw(m_btn_text);
}

void Game::draw()
{
	m_map->draw(m_window);
	m_window.draw(m_score_text);
}
