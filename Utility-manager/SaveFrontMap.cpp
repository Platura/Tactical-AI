#include "SaveFrontMap.h"
#include <cmath>

SaveFrontMap::SaveFrontMap()
{

}

TacticalMap SaveFrontMap::compute(aiPosition pos, TacticalMap cover, TacticalMap spotted)
{
    TacticalMap tm;
    tm.init(cover.getSizeX(), cover.getSizeY(), 0.f);
    addTemplate(pos.x, pos.y, tm);
    tm *= cover - spotted.invert();
	return tm;
}

void SaveFrontMap::addTemplate(int x, int y, TacticalMap& tm)
{
    const int radius = 7;
    const int shootRange = 5; 
    const float maxDistance = static_cast<float>(radius);

    for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
            int px = x + i;
            int py = y + j;

            if (px >= 0 && px < tm.getSizeX() && py >= 0 && py < tm.getSizeY()) {
                float dist = std::sqrt(static_cast<float>(i * i + j * j));

                float weight = 0.0f;
                if (dist <= shootRange) {
                    weight = 1.0f;
                }
                else if (dist <= maxDistance) {
                    weight = 1.0f - ((dist - shootRange) / (maxDistance - shootRange));
                }
                tm.at(px, py) = std::max(tm.at(px, py), weight);
            }
        }
    }
}
