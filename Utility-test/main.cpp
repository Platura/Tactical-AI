#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui.h>
#include <fmt/format.h>

#include <imgui-SFML.h>

#include "Reasoner.h"
#include "ConstConsideration.h"
//#include "ConsiderationAmmunitionReserve.h"
//#include "ConsiderationEnemyDistance.h"

class Agent {
public:
	std::string name;
};

int main()
{
	//Console text
	std::cout << "Hallo Welt" << std::endl;

	Reasoner reasoner;

	Agent a;
	a.name = "Test";


	Action idle_aktion("idle");
	idle_aktion.addConsideration(ConstConsideration::Create(0.2));
	Action melee_action("melee");
	Action melee_action2("melee2");
	melee_action.setParameter("Target", &a);
	melee_action.setParameter("Speed", 1);
	/*ConsiderationEnemyDistance cDistance;
	ConsiderationAmmunitionReserve cAmmo;
	melee_action.addConsideration(std::make_shared<ConsiderationEnemyDistance>(cDistance));
	melee_action2.addConsideration(std::make_shared<ConsiderationAmmunitionReserve>(cAmmo));*/

	reasoner.addAction(idle_aktion);
	reasoner.addAction(melee_action);
	reasoner.addAction(melee_action2);

	std::cout << "Test set get Agent name: " << melee_action.getParameter<Agent*>("Target")->name << " Speed : " << melee_action.getParameter<int>("Speed") << std::endl;
	
	//Init window
	sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML works!");
	ImGui::SFML::Init(window);
	sf::Clock deltaClock;

	sf::Font font;
	font.loadFromFile("C:/Users/Gesine Wagner/source/repos/AI-manager/AI-manager/fonts/Roboto-Black.ttf");

	while (window.isOpen())
	{
		// == == == Event Handeling == == ==
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed)
				window.close();
		}
		ImGui::SFML::Update(window, deltaClock.restart());

		// == == == Game Update == == ==

		
		sf::Text text;		
		text.setFont(font);
		std::string text_content;
		//text sfml

		reasoner.DrawDebugUi();
		auto possible_aktion = reasoner.update();

		for (auto const& el : possible_aktion)
		{
			text_content += fmt::format("{}: {}\n", el->getName(), el->getLastValue());
			//std::cout << el->getLastValue() << ": " << el->getName() << std::endl;
		}
		text.setString(text_content);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);



		window.clear();
		window.draw(text);
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}