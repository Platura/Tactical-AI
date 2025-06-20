#include "Game.h"
#include <iostream>
#include <chrono>

#include "AgentManager.h"
#include "Agent.h"
#include "EngineDataInput.h"
#include "EngineDataOutput.h"
#include "Target.h"
#include "MapDebugDisplay.h"
#include "HealthBarComponent.h"
#include "NameTagComponent.h"
#include "DeathComponent.h"


Game::Game(int screenW, int screenH)
{
	window.create(sf::VideoMode(screenW, screenH), " Game window");
	ImGui::SFML::Init(window);
	camera=(window.getView());

    //init();
}

void Game::handleEvents()
{
    //**Handle Events**//
    auto& io = ImGui::GetIO();
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(window, event);

        if (!io.WantCaptureMouse)
        {
            camera.onEvent(event);
        }
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Left " << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
        }
        //Set new Target
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
        {
            auto const new_target = sf::Vector2f(sf::Mouse::getPosition(window));
            fmt::print("New Target {} {}  \n", new_target.x, new_target.y);
        }
    }
}

void Game::update()
{

	deltaTime = deltaClock.restart();
	ImGui::SFML::Update(window, deltaTime);

    auto removed_agents = m_agent_M.getRemovedAgendts();


    //**AICycle**//
    for(auto const agent : removed_agents)
    {
        m_ai_engine.removeBrain(agent);
    }

    m_ai_engine.sense();
    m_ai_engine.think();
    m_ai_engine.act();
    m_ai_engine.drawDebug();


    //**AgentManager**//

    float dt = std::min(deltaTime.asSeconds(), 1 / 30.f);
    m_agent_M.update(dt);
    m_agent_M.drawDebug();
        
}

void Game::render()
{
    window.clear();


    //** Camera**//
    auto backup_view = window.getView();
    window.setView(camera.getView());

    map.draw(window);
    m_agent_M.render(window);
    window.setView(backup_view);

    window.draw(m_sprite);
    ImGui::SFML::Render(window);
    window.display();
}


void Game::init()
{
    //**ImGUI**//
    auto& io = ImGui::GetIO();
    //io.FontGlobalScale = 3;
    //**Game**//
    loadMap();
    initAgents();
}

void Game::shutdown()
{
    ImGui::SFML::Shutdown();
}

void Game::CreateAgent(sf::Vector2f pos, std::string texture, aiTeamId team, std::string ai_config)
{
    auto start = std::chrono::high_resolution_clock::now();

    auto agent_ptr = new Agent(pos);
    auto agent_id = m_agent_M.addAgent(agent_ptr);

    agent_ptr->addComponent<GraphicComponent>(texture);
    agent_ptr->addComponent<HealthBarComponent>();
    agent_ptr->addComponent<NameTagComponent>();
    agent_ptr->addComponent<DeathComponent>();

    m_ai_engine.createAiAgentFromFile(agent_id, team, ai_config);

    auto create_duration = std::chrono::high_resolution_clock::now() - start;

    fmt::print("Agent {} Creating time {}s\n", agent_id, std::chrono::duration_cast<std::chrono::seconds>(create_duration).count());
}

void Game::initAgents()
{
    m_ai_engine.setupFactories();
    m_ai_engine.setEngineDataInput(std::make_shared<EngineDataInput>(&m_agent_M));
    m_ai_engine.setEngineDataOutput(std::make_shared<EngineDataOutput>(&m_agent_M));

    auto sensor = new Agent({ 100,100 });
    auto sensor_id = m_agent_M.addAgent(sensor);
    m_ai_engine.createAiAgentFromFile(sensor_id, 1, ("sensor.json"));
    srand(static_cast<unsigned>(time(nullptr)));

    int flank = 5;
    float spacing = 10;
    //flank_agents
    int minX = 50, maxX = 700;
    int minY = 800, maxY = 1600;

    for (int i = 0; i < flank; ++i)
    {
        int x = rand() % (maxX - minX + 1) + minX;
        int y = rand() % (maxY - minY + 1) + minY;
        CreateAgent(sf::Vector2f{ (float)x,(float)y }, (R"(textures\basic_character.png)"), 1, ("flank_role.json"));
    }
    int front = 5;
    //front_agents
    minX = 750, maxX = 1200;
    minY = 800, maxY = 1600;

    for (int j = 0; j < front; ++j)
    {
        int x = rand() % (maxX - minX + 1) + minX;
        int y = rand() % (maxY - minY + 1) + minY;
        CreateAgent(sf::Vector2f{ (float)x,(float)y }, (R"(textures\basic_character.png)"), 1, ("front_role.json"));
    }
    int rear = 1;
    //rear_agents
    for (int k = 0; k < rear; k++)
    {
        CreateAgent(sf::Vector2f{ 160,160 + k * spacing }, (R"(textures\basic_character.png)"), 1, ("rear_role.json"));
    }

    int enemies = 11;
    //Enemies
    minX = 1200, maxX = 2000;
    minY = 700, maxY = 1600;

    for (int l = 0; l < enemies; ++l)
    {

        int x = rand() % (maxX - minX + 1) + minX;
        int y = rand() % (maxY - minY + 1) + minY;
        CreateAgent(sf::Vector2f{(float)x,(float)y}, (R"(textures\basic_enemy.png)"), 0, ("standard_patrol.json"));
    }

}

void Game::loadMap()
{
    //map.init(R"(tilset_for_load\lone_outpost.txt)", { {15,6} });
    map.init(R"(tilset_for_load\street_map.txt)", { {15,6} });
    MapDebugDisplay mapDD;
}
