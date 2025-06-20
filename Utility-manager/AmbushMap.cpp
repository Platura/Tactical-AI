#include "AmbushMap.h"

TacticalMap AmbushMap::compute(std::vector<TacticalMap> agent_vis, TacticalMap target_vis)
{
    TacticalMap vis_enemy(target_vis.getSizeX(), target_vis.getSizeY(), 0.f);// max(agent_a, agent_b);
    for (int i = 0; i < agent_vis.size(); i++)
    {
        vis_enemy.max(agent_vis[i]);
    }

    vis_enemy.invert();
    return vis_enemy * target_vis;
}
