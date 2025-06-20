#pragma once
#include <iostream>
#include <string>
#include "IReasoner.h"

#include "Option.h"
class UtilityReasoner : 
	public IReasoner
{
	
private:
	std::string m_name = "UtilityReasoner";
public:
	//void addOption(Option& option) override;
	void update(BlackboardManager& bm) override;

	static std::unique_ptr<IReasoner> create(json const& parameter);
	void DrawDebugUi();
};

