#pragma once
#include "IAction.h"
#include "MeleeAction.h"
#include <unordered_map>
#include <memory>
#include <functional>


using ActionFactoryMethod = std::unique_ptr<OldAction>(Option*);

extern std::unordered_map<std::string, std::function<ActionFactoryMethod>> actionMapper;