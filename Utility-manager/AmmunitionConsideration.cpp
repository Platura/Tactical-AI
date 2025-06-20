#include "AmmunitionConsideration.h"

AmmunitionConsideration::AmmunitionConsideration()
{
}

float AmmunitionConsideration::compute(BlackboardManager& bm)
{
   auto ammunition = bm.getAgentBlackboard(m_agent).getValue<aiInt>("ammunition");
   auto max_ammo = bm.getGlobal().getValue<aiInt>("max_ammunition");
   float result = 0.f;
   if (ammunition.has_value())
   {
       //Bsp 30 current / 100 max = 0.3
       result = (float)ammunition.value() / (float)max_ammo.value();
   }
   return result;
}

std::unique_ptr<IConsideration> AmmunitionConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<AmmunitionConsideration>();
    if (parameter.contains("max_ammunition"))
    {
        result->m_max_munition.init(agent, team, parameter["max_ammunition"]);
    }
    return result;
}
