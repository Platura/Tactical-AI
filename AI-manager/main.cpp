#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Game.h"
#include "InfluenceMap.h"
#include <fmt/format.h>

int main()
{
    int m_windowWidth = 1000;
    int m_windowHeight = 800;

    Game game(m_windowWidth, m_windowHeight);
    game.init();
    /*std::vector<AgentEntity> m_exampleA;
    m_exampleA = { {{800,800 }, 1},{{800,300},1} };
    InfluenceMap m_influence;
    m_influence.init(25, 25, 32, 32);
    m_influence.createLinearTemplate(1, 10);
    m_influence.compute(m_exampleA,);*/
    sf::Clock clock;

    float lastTime = 0;
    while (game.isRunning() == true)
    {
        game.handleEvents();
        game.update();
        game.render();
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime; //(currentTime - lastTime);
        lastTime = currentTime;
        fmt::print("FPS {} \n", fps);
    }
    game.shutdown();
    
    /*
    auto agent_desc = R"({
        "blackboard": {
            "target": { "x": 0, "y": 50 },
            "target_2": { "x": 10, "y":50 },
            "age": 100.0,
            "counter": 0.0
        },
        "sensors": [
            {
                "Type":"LifeTimeSensor",
                "field_name":"life_time"
            },
            {
                "Type":"PositionSensor",
                "field_name":"positon"
            },
            {
                "Type":"PositionSensor",
                "field_name":"positon_target",
                "Agent_id": {
                    "blackboard": "self.target_agent_id"
                }
            },
            {
                "Type":"StanceSensor",
                "field_name":"stance"
            }
        ],
        "reasoner": {
            "Type": "UtilityReasoner",
            "options": [
                {
                    "name": "xyz",
                    "considerations": [
                        {
                            "Type":"Distance",
                            "from": "self.target",
                            "to":  "target_2",
                            "weight" :{
                                "Type": "Linear",
                                "min": 15,
                                "max": 0
                            }            
                              
                        }
                    ],
                    "actions": []
                },
                {
                    "name": "set_null",
                    "interruptible": false,
                    "considerations": [
                        {
                        "Type": "BlackboardValue",
                        "value": "self.counter"    
                        }
                    ],
                    "actions": [
                        {
                            "Type": "Set",
                            "name": "self.counter",
                            "value": 0.0
                        },
                        {
                            "Type": "sleep",
                            "time": 10
                        
                        }
                    ]
                },
                {
                    "name": "increment",
                    "considerations": [
                        {
                        "Type": "BlackboardValue",
                        "value": "self.counter",
                        "weight" :{
                                "Type": "Linear",
                                "min": 1,
                                "max": 0
                            }  
                        }
                    ],
                    "actions": [
                        {
                            "Type": "increment",
                            "name": "self.counter"
                        },
                        {
                            "Type": "sleep",
                            "time": 10
                        }
                    ]
                }    
            ]    
        }
    })";

   


    //***Agent**
    

   
    auto agentA = new Agent;
    auto enemyA = new Agent(sf::Vector2f{ 500,200 });
    auto targetA = new Agent(sf::Vector2f{ 500,200 });
    auto coverA = new Agent(sf::Vector2f{ 250,100 });

    targetA->addComponent<Target>(map);
    agentA->addComponent<GraphicComponent>(R"(textures\pac.png)");
    enemyA->addComponent<GraphicComponent>(R"(textures\pac.png)");
    enemyA->addComponent<CollisionComponent>();
    //agentA->addComponent<TargetSet>(targetA);
    agentA->update(0, &agentM);
    coverA->addComponent<CollisionComponent>();
    coverA->addComponent<GraphicComponent>(R"(textures\barrel.jpg)");
    coverA->addComponent<Cover>(sf::Vector2f{ 32, 32 });

    auto agentB = new Agent(sf::Vector2f{ 1,1 });
    auto targetB = new Agent(sf::Vector2f{ 50,50 });
    targetB->addComponent<Target>(map);
    agentB->addComponent<GraphicComponent>(R"(textures\pac.png)");
    agentB->addComponent<TargetSet>(targetB);
    
    agentM.addAgent(targetA);
    agentM.addAgent(targetB);
    agentM.addAgent(agentA);
    agentM.addAgent(agentB);
    agentM.addAgent(enemyA);
    agentM.addAgent(coverA);

    m_ai_engine.createAiAgentFromString(1, 1, agent_desc);
    m_ai_engine.createAiAgentFromString(2, 1, agent_desc);

    m_ai_engine.createAiAgentFromString(4, 1, agent_desc);

    /* Move Demo

    auto move_agent = new Agent(sf::Vector2f(200, 600));
    move_agent->addComponent<GraphicComponent>(R"(textures\pac.png)");
    
    m_ai_engine.createAiAgentFromFile(agentM.addAgent(move_agent), 1, "move_demo.json");


    /**Standard image
    sf::Texture m_image;
    sf::Sprite m_sprite;

    //sf::RenderWindow window(sf::VideoMode(m_windowWidth, m_windowHeight), "SFML works!");
    //ImGui::SFML::Init(window);
    //***Camera**
    //Camera camera(window.getView());

    auto& io = ImGui::GetIO();
    io.FontGlobalScale = 3;

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        // *** Handle Events ***
        
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
                fmt::print("New Targetz {} {}  \n", new_target.x, new_target.y);
                targetB->setPosition(new_target);
            }
        }
        //auto deltaTime = deltaClock.restart();
        // *** Update / Tick ***
        //ImGui::SFML::Update(window, deltaTime);
        m_ai_engine.sense();
        m_ai_engine.think();
        m_ai_engine.act();
        m_ai_engine.drawDebug();

        //**ImGui window */
        /*ImGui::Begin("FlowField Controls");
        bool open = true;
        ImGui::BeginTabBar("1");
        if (ImGui::BeginTabItem("General", &open))
        {
            //Load Image from path
            char buf[255]{};
            if (ImGui::InputText("Enter image path", buf, sizeof(buf)))
            {
                if (!m_image.loadFromFile(buf))
                {
                    // Error...
                }
                m_sprite.setTexture(m_image);
            }

            //Load Image from Preset
            static const char* maps[]{ "None", "cat.jpg", "scorn.jpg" };
            static int selectedMap = 0;
            if (ImGui::Combo("Select map preset", &selectedMap, maps, IM_ARRAYSIZE(maps)))
            {
                if (!m_image.loadFromFile(maps[selectedMap]))
                {
                    // Error...
                }
                m_image.setRepeated(true);
                sf::Vector2u size = m_image.getSize();
              
                m_sprite.setTexture(m_image, true);
            }
            ImGui::EndTabItem();
        }

        ImGui::End();
        
        agentM.update(deltaTime.asSeconds());
        agentM.drawDebug();
        // *** Render *** 
        window.clear();

        // Render with camera
        {
            auto backup_view = window.getView();
            window.setView(camera.getView());

            map.draw(window);

            agentM.render(window);

            window.setView(backup_view);
        }

        
        window.draw(m_sprite);
        ImGui::SFML::Render(window);
        window.display();
    }

    
    ImGui::SFML::Shutdown();
    */
    return 0;
}