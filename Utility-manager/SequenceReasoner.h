#pragma once
#include <iostream>
#include "IReasoner.h"
class SequenceReasoner :
	public IReasoner
{
private:
	std::string m_name = "SequenceReasoner";
public:
	void update(BlackboardManager& bm) override;

	static std::unique_ptr<IReasoner> create(json const& parameter);
	//not implemented
	void DrawDebugUI() {};
};

