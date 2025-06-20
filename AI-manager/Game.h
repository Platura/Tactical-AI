#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "AgentManager.h"
#include "AiEngine.h"
#include "Camera.h"
#include "MapManager.h"

class Game
{
private:
	sf::RenderWindow window;
	Camera camera;
	sf::Clock deltaClock;
	sf::Time deltaTime;
	MapManager& map = *MapManager::getInstance();
	sf::Texture m_image;
	sf::Sprite m_sprite;
	AiEngine m_ai_engine;
	AgentManager m_agent_M;
	
public:
	Game(int screenW, int screenH);
	void handleEvents();
	void update();
	void render();


	void init();
	void shutdown();
	void CreateAgent(sf::Vector2f pos, std::string texture, aiTeamId team, std::string ai_config);
	void initAgents();
	void loadMap();
	bool isRunning() { return window.isOpen(); }
};

