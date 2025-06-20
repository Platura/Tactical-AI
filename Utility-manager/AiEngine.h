#pragma once
#include <iostream>
#include <vector>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Factory.h"
#include "BlackboardManager.h"
#include "Types.hpp"
#include "ISensor.h"
#include "IEngineDataInput.h"
#include "IEngineDataOutput.h"
#include "IFunction.h"
#include "IReasoner.h"
#include "IAction.h"
#include "IConsideration.h"
#include "AgentBrain.h"


class AiEngine
{
	BlackboardManager m_backboards;
	Factory<ISensor, json> m_sensor_factory;
	Factory<IFunction, json> m_function_factory;
	Factory<IReasoner, json> m_reasoner_factory;
	Factory<IAction, json, aiAgentId, aiTeamId> m_action_factory;
	Factory<IConsideration, json, aiAgentId, aiTeamId> m_consideration_factory;

	std::vector<std::unique_ptr<ISensor>> m_sensors;
	std::vector<AgentBrain> m_brains_soup;

	std::shared_ptr<IEngineDataInput> m_data_input;
	std::shared_ptr<IEngineDataOutput> m_data_output;


public:

	void setEngineDataInput(std::shared_ptr<IEngineDataInput> data_input)
	{
		m_data_input = data_input;
	}

	void setEngineDataOutput(std::shared_ptr<IEngineDataOutput> data_output)
	{
		m_data_output = data_output;
	}

	void setupFactories();

	void createAiAgent(aiAgentId agentId, aiTeamId teamId, std::istream& desc);
	void createAiAgentFromFile(aiAgentId agentId, aiTeamId teamId, std::string file_name_desc);
	void createAiAgentFromString(aiAgentId agentId, aiTeamId teamId, std::string const& json_desc);

	void removeBrain(aiAgentId agendId);

	void sense();
	void think();
	void act();

	void drawDebug();
protected:
	void descParseSensors(aiAgentId agentId, aiTeamId teamId, json const& data);
	IReasoner::ptr descParseReasoner(aiAgentId agentId, aiTeamId teamId, json const& data);
	Option::ptr descParseOption(aiAgentId agentId, aiTeamId teamId, json const& data);
	ConsiderationPtr descParseConsideration(aiAgentId agentId, aiTeamId teamId, json const& data);
	void descParseBlackboard(aiAgentId agentId, aiTeamId teamId, json const& data);
	IAction::ptr descParseAction(aiAgentId agentId, aiTeamId teamId, json const& data);
};

