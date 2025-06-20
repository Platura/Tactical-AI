#pragma once
#include "IEngineDataInput.h"
#include "AgentManager.h"
#include "MapManager.h"

class EngineDataInput : public IEngineDataInput
{
	AgentManager* m_agm;
public:
	EngineDataInput(AgentManager* mg ) : m_agm(mg), cmap(MapManager::getInstance()->getCostField()) {
		auto& tm = MapManager::getInstance()->getTileMap();
		m_map_size = DataInputMapSize{
			.tiles_x = (uint32_t)tm.getMapSize().x,
			.tiles_y = (uint32_t)tm.getMapSize().y,
			.tile_size_X = tm.getTileSize().x,
			.tile_size_y = tm.getTileSize().y,
		};
	};

	Costfield &getCostField() const override;
	void* getNativeAgentHandle(aiAgentId) override;
	Vec2D getAgentPosition(aiAgentId) const override;
	Vec2D getAgentDirection(aiAgentId) const override;
	float getAgentRotation(aiAgentId) const override;
	int getAgentStance(aiAgentId)const override;
	int getAgentAmmunition(aiAgentId)const override;
	int getAgentHealth(aiAgentId)const override;
	float getDeltaTime(aiAgentId) const override;
	DataInputMapSize getMapSize() const override;

protected:
	Agent* getAgent(aiAgentId id) const;
	Costfield& cmap;
	DataInputMapSize m_map_size;
};

