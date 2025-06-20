#pragma once
#include "IAction.h"
class IOneTimeAction :
    public IAction
{
public:
	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override {};
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) final;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override {};

	virtual void action(BlackboardManager& bm) = 0;
};

