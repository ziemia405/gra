#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Player.h"
#include "Platform.h"
#include "Map.h"

class Game
{
private:
	sf::RenderWindow m_window;
	sf::Clock m_timer;
	sf::Time m_dt;
	std::unordered_map<std::string, sf::Texture*> m_textures;
	sf::View m_cam;
	sf::Text m_score_text;
	std::vector<std::string> m_map_filenames;
	int m_map_idx;
	sf::Font m_font;
	sf::Text m_game_over_text;
	sf::Text m_btn_text;
	sf::RectangleShape m_next_map_btn;
	sf::RectangleShape m_screen_bg; // for game over screen
	// objects
	Map* m_map;
	bool m_game_over;

public:
	Game();
	~Game();

	void events();
	void loop();
	void loadTextures();
	void keyboardInput();
	void updateCam();
	void updateScore();
	void update();
	void gameOver();
	void draw();
};

