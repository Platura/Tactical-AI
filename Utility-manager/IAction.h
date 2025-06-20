#pragma once
#include "BlackboardManager.h"
#include <memory>
#include <nlohmann/json.hpp>
#include "IEngineDataOutput.h"
#include "IEngineDataInput.h"

using json = nlohmann::json;

class IAction
{
protected:
	bool m_isFinished = false;
	std::string m_name;

	aiAgentId m_agent;
	aiTeamId m_team;
public:
	using ptr = std::unique_ptr<IAction>;

	virtual ~IAction() = default;

	void setupMetadata(aiAgentId a, aiTeamId team) {
		m_agent = a;

		m_team = team;
	}

	virtual void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) = 0;
	virtual void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) = 0;
	virtual void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) = 0;

	virtual bool isFinished() {
		return m_isFinished;
	};

	void setisFinished(bool value) {
		m_isFinished = value;
	}

	void setName(std::string name)
	{
		m_name = name;
	}

	std::string const& getName() const { return m_name; }
};

