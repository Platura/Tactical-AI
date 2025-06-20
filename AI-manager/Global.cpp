#include "Global.h"
#include "MeleeAction.h"
#include "RunToTargetAction.h"
#include "ShootTargetAction.h"
#include "TakeCoverAction.h"

std::unordered_map<std::string, std::function<ActionFactoryMethod>> actionMapper = { 
	{"melee",MeleeAction::create}, 
	{"run", RunToTargetAction::create }, 
	{"shoot", ShootTargetAction::create},
	{"take_cover", TakeCoverAction::create}};