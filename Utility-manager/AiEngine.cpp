#include "AiEngine.h"
#include <fstream>
#include <fmt/format.h>
#include "imgui.h"
#include "LifeTimeSensor.h"
#include "PositionSensor.h"
#include "HealthSensor.h"
#include "TestMovementSensor.h"
#include "LinearFunction.h"
#include "IdentityFunction.h"
#include "UtilityReasoner.h"
#include "DistanceConsideration.h"
#include "BlackboardValueConsideration.h"
#include "ConstConsideration.h"
#include "StanceSensor.h"
#include "ThreatSensor.h"
#include "VisibilitySensor.h"
#include "AmbushSensor.h"
#include "CoverSensor.h"
#include "GlobalVisibilitySensor.h"
#include "FrontSensor.h"
#include "CostSensor.h"
#include "SpottedSensor.h"
#include "IncrementAction.h"
#include "SleepAction.h"
#include "SetAction.h"
#include "MoveToAction.h"
#include "SelectPositionAction.h"
#include "SelectHoldAction.h"
#include "SelectTargetAction.h"
#include "ComputeAmbushAction.h"
#include "ComputeCostAction.h"
#include "ShootAtAction.h"
#include "LookAroundAction.h"
#include "SelectFrontAction.h"
#include "TakeAimAction.h"
#include "HealAction.h"
#include "RemoveTargetAction.h"
#include "ComputeHiddenCoverAction.h"
#include "SelectCoverAction.h"
#include "ReloadAction.h"
#include "SelectFollowAction.h"
#include "ThreatConsideration.h"
#include "NearestTargetConsideration.h"
#include "InRangeConsideration.h"
#include "HasTargetConsideration.h"
#include "IsAliveConsideration.h"
#include "HealthConsideration.h"
#include "AmmunitionConsideration.h"
#include "VisibleConsideration.h"
#include "DangerConsideration.h"
#include "IsSpottedConsideration.h"
#include "NearestFrontConsideration.h"
#include "IsHitConsideration.h"
#include "IsCloseConsideration.h"
#include "HasFollowConsideration.h"


void AiEngine::setupFactories()
{
	m_sensor_factory.setup<LifeTime>("LifeTimeSensor");
	m_sensor_factory.setup<PositionSensor>("PositionSensor");
	m_sensor_factory.setup<StanceSensor>("StanceSensor");
	m_sensor_factory.setup<ThreatSensor>("ThreatSensor");
	m_sensor_factory.setup<VisibilitySensor>("VisibilitySensor");
	m_sensor_factory.setup<AmbushSensor>("AmbushSensor");
	m_sensor_factory.setup<CoverSensor>("CoverSensor");
	m_sensor_factory.setup<GlobalVisibilitySensor>("GlobalVisibilitySensor");
	m_sensor_factory.setup<CostSensor>("CostSensor");
	m_sensor_factory.setup<SpottedSensor>("SpottedSensor");
	m_sensor_factory.setup<FrontSensor>("FrontSensor");
	m_sensor_factory.setup<HealthSensor>("HealthSensor");
	m_sensor_factory.setup<TestMovementSensor>("TestMovement");

	m_action_factory.setup<IncrementAction>("increment");
	m_action_factory.setup<SleepAction>("sleep");
	m_action_factory.setup<SetAction>("Set");
	m_action_factory.setup<MoveToAction>("MoveTo");
	m_action_factory.setup<SelectPositionAction>("SelectPosition");
	m_action_factory.setup<SelectTargetAction>("SelectTarget");
	m_action_factory.setup<ComputeAmbushAction>("ComputeAmbush");
	m_action_factory.setup<ComputeCostAction>("ComputeCost");
	m_action_factory.setup<ShootAtAction>("ShootAt");
	m_action_factory.setup<TakeAimAction>("TakeAim");
	m_action_factory.setup<RemoveTargetAction>("RemoveTarget");
	m_action_factory.setup<ComputeHiddenCoverAction>("ComputeHiddenCover");
	m_action_factory.setup<SelectCoverAction>("SelectCover");
	m_action_factory.setup<SelectFrontAction>("SelectFront");
	m_action_factory.setup<ReloadAction>("Reload");
	m_action_factory.setup<LookAroundAction>("LookAround");
	m_action_factory.setup<SelectHoldAction>("SelectHold");
	m_action_factory.setup<HealAction>("Heal");
	m_action_factory.setup<SelectFollowAction>("SelectFollow");

	m_function_factory.setup<LinearFunction>("Linear");
	m_function_factory.setup<IdentityFunction>("Identity");

	m_reasoner_factory.setup<UtilityReasoner>("UtilityReasoner");


	m_consideration_factory.setup<DistanceConsideration>("Distance");
	m_consideration_factory.setup<BlackboardValueConsideration>("BlackboardValue");
	m_consideration_factory.setup<ThreatConsideration>("Threat");
	m_consideration_factory.setup<ConstConsideration>("Const");
	m_consideration_factory.setup<NearestTargetConsideration>("NearestTarget");
	m_consideration_factory.setup<InRangeConsideration>("InRange");
	m_consideration_factory.setup<HasTargetConsideration>("HasTarget");
	m_consideration_factory.setup<IsAliveConsideration>("IsAlive");
	m_consideration_factory.setup<HealthConsideration>("Health");
	m_consideration_factory.setup<AmmunitionConsideration>("Ammunition");
	m_consideration_factory.setup<VisibleConsideration>("Visible");
	m_consideration_factory.setup<DangerConsideration>("Danger");
	m_consideration_factory.setup<IsSpottedConsideration>("IsSpotted");
	m_consideration_factory.setup<IsHitConsideration>("IsHit");
	m_consideration_factory.setup<NearestFrontConsideration>("NearestFront");
	m_consideration_factory.setup<IsCloseConsideration>("IsClose");
	m_consideration_factory.setup<HasFollowConsideration>("HasFollow");

	m_backboards.getGlobal().setValue("max_ammunition", 100);
	m_backboards.getGlobal().setValue("max_health", 100);
}

void AiEngine::createAiAgent(aiAgentId agentId, aiTeamId teamId, std::istream& desc)
{
	auto data = json::parse(desc);
	m_backboards.createAgentBlackboard(agentId, teamId);
	m_data_output->setup(agentId);


	if (data.contains("blackboard"))
	{
		descParseBlackboard(agentId, teamId, data["blackboard"]);
	}
	if (data.contains("sensors"))
	{
		descParseSensors(agentId, teamId, data["sensors"]);
	}
	if (!data.contains("reasoner"))
	{
		fmt::print("Missing field reasoner!\n");
			return;
	}

	auto reasoner = descParseReasoner(agentId, teamId, data["reasoner"]);

	m_brains_soup.emplace_back(std::move(AgentBrain(agentId, std::move(reasoner))));

}

void AiEngine::createAiAgentFromFile(aiAgentId agentId, aiTeamId teamId, std::string file_name_desc)
{
	std::fstream file(file_name_desc, std::ios::in);

	if (file)
	{
		createAiAgent(agentId, teamId, file);
	}
}

void AiEngine::createAiAgentFromString(aiAgentId agentId, aiTeamId teamId, std::string const& json_desc)
{
	std::stringstream sstream(json_desc);
	createAiAgent(agentId, agentId, sstream);
}

void AiEngine::removeBrain(aiAgentId agentId)
{
	auto ptr = std::remove_if(m_brains_soup.begin(), m_brains_soup.end(), [agentId](AgentBrain& b) {
		return b.getID() == agentId;
		});

	m_brains_soup.erase(ptr, m_brains_soup.end());

	auto ptr_sensor = std::remove_if(m_sensors.begin(), m_sensors.end(), [agentId](auto& b) {
		return b->getAgentId() == agentId;
		});

	m_sensors.erase(ptr_sensor, m_sensors.end());

	m_backboards.removeAgent(agentId);
}

void AiEngine::sense()
{
	for (auto& sensor : m_sensors)
	{
		sensor->update(m_backboards, m_data_input.get());
	}
}

void AiEngine::think()
{
	for (auto& brain : m_brains_soup)
	{
		brain.think(m_backboards, m_data_output.get());
	}
}

void AiEngine::act()
{
	for (auto& brain : m_brains_soup)
	{
		brain.act(m_backboards, m_data_output.get(), m_data_input.get());
	}
}


void AiEngine::drawDebug()
{
	ImGui::Begin("aiEngine");
	ImGui::BeginTabBar("RootTabBar");

	if (ImGui::BeginTabItem("Global"))

	{
		m_backboards.getGlobal().drawDebug();
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("Team"))

	{
		static aiTeamId selected_team = 0;

		auto const& teams = m_backboards.getTeams();

		if (ImGui::BeginCombo("Team", fmt::format("Team {}", selected_team).c_str()))
		{
			for (auto const& [id, agents] : teams)
			{
				if (ImGui::Selectable(fmt::format("Agent {}", id).c_str(), id == selected_team))
					selected_team = id;
			}
			ImGui::EndCombo();
		}
		ImGui::Separator();


		m_backboards.getTeamBlackboard(selected_team).drawDebug();
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("Blackboard Agent"))
	{
		static aiAgentId selected_agent = 0;

		
		auto agents_id = m_backboards.getAgents();

		if (ImGui::BeginCombo("Agent", fmt::format("Agent {}", selected_agent).c_str()))
		{
			for (auto id : agents_id)
			{
				if (ImGui::Selectable(fmt::format("Agent {}", id).c_str(), id == selected_agent))
					selected_agent = id;
			}
			ImGui::EndCombo();
		}
		ImGui::Separator();

		if (selected_agent != NoAgent)
		{
			m_backboards.getAgentBlackboard(selected_agent).drawDebug();

		}
		ImGui::EndTabItem();

	}

	if (ImGui::BeginTabItem("Agent"))
	{
		static aiAgentId selected_agent = 0;


		auto agents_id = m_backboards.getAgents();

		if (ImGui::BeginCombo("Agent", fmt::format("Agent {}", selected_agent).c_str()))
		{
			for (auto id : agents_id)
			{
				if (ImGui::Selectable(fmt::format("Agent {}", id).c_str(), id == selected_agent))
					selected_agent = id;
			}
			ImGui::EndCombo();
		}
		ImGui::Separator();

		if (selected_agent != NoAgent)
		{
			auto it = std::find_if(m_brains_soup.begin(), m_brains_soup.end(), [id = selected_agent](AgentBrain const& brain) {
				return brain.getID() == id;
				});
			if (it == m_brains_soup.end())
				selected_agent = NoAgent;
			it->DrawDebug();

		}
		ImGui::EndTabItem();

	}

	ImGui::EndTabBar();
	ImGui::End();
}

void AiEngine::descParseSensors(aiAgentId agentId, aiTeamId teamId, json const& data)
{
	if (!data.is_array())
	{
		fmt::print("[aiEngine] Error sensors is not an array.\n");
	}

	for (auto const& el : data)
	{
		if (!el.contains("Type"))
		{
			fmt::print("[aiEngine] Error missing sensor type. {} \n", el.dump());
		}

		std::string type = el["Type"];

		auto sensor = m_sensor_factory.createUnique(type, el);
		sensor->setEntityAndTeam(agentId, teamId);

		m_sensors.push_back(std::move(sensor));
	}
}

IReasoner::ptr AiEngine::descParseReasoner(aiAgentId agentId, aiTeamId teamId, json const& data)
{
	auto reasoner = m_reasoner_factory.createUnique(data["Type"], data);

	if (data.contains("options"))
	{
		for (auto& option : data["options"])
		{
			reasoner->addOption(std::move(descParseOption(agentId, teamId, option)));
		}
	}
	return reasoner;
}

Option::ptr AiEngine::descParseOption(aiAgentId agentId, aiTeamId teamId, json const& data)
{
	auto op = std::make_shared<Option>(data["name"]);
	if (data.contains("interruptible"))
	{
		op->setInterruptible(data["interruptible"]);
	}
	if (data.contains("considerations"))
	{
		for (auto const& con : data["considerations"])
		{
			op->addConsideration(descParseConsideration(agentId, teamId, con));
		}
	}
	if (data.contains("actions"))
	{
		for (auto const& con : data["actions"])
		{
			op->addAction(std::move(descParseAction(agentId, teamId, con)));
		}
	}


	return std::move(op);
}

ConsiderationPtr AiEngine::descParseConsideration(aiAgentId agentId, aiTeamId teamId, json const& data)
{
	auto con = m_consideration_factory.createUnique(data["Type"], data, agentId, teamId);
	con->setName(data["Type"]);
	con->initIds(agentId, teamId);
	if (data.contains("weight"))
	{
		auto const& desc = data["weight"];
		con->addWeightFunction(m_function_factory.createUnique(desc["Type"], desc));
	}

	return con;
}

void AiEngine::descParseBlackboard(aiAgentId agentId, aiTeamId teamId, json const& data)
{
	auto& blackboard = m_backboards.getAgentBlackboard(agentId);
	for (auto const& [key, value] : data.items())
	{
		blackboard.setValue(key, valuesFromJson(value));
		/*
		if (value.is_number_float())
		{
			blackboard.setValue(key, value.get<float>());
		}
		else if (value.is_number())
		{
			blackboard.setValue(key, value.get<aiInt>());
		}
		else if (value.is_object())
		{
			if (value.contains("x") && value.contains("y"))
			{
				blackboard.setValue(key, Vec2D(value["x"], value["y"]));
			}
		}*/

	}
}

IAction::ptr AiEngine::descParseAction(aiAgentId agentId, aiTeamId teamId, json const& data)
{

	auto temp = m_action_factory.createUnique(data["Type"], data, agentId, teamId);
	temp->setName(data["Type"]);
	temp->setupMetadata(agentId, teamId);
	return std::move(temp);
}

/*
class EngineDataInput
{
public:
	virtual Vec2D getVec2D(aiAgentId, std::string field_name) = 0;
};

class MyEngienDataInput : public EngineDataInput

{
public:
	Vec2D getVec2D(aiAgentId, std::string field_name) {
		Agent* a = my_engine.getEntity(aiAgentId);

		if (field_name == "POsaiton")
			return a->positon;
	};

	void* getNativePointer()
};

*/