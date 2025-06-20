#include "IOneTimeAction.h"

void IOneTimeAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*)
{
	action(bm);
	m_isFinished = true;
	
}
