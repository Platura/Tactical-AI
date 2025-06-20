#pragma once
#include <unordered_map>
#include "Flowfield.h"

class MapDebugDisplay
{
	std::unordered_map<std::string, Flowfield*> m_flowfields;

	std::string m_currentMap ;
public:

	static MapDebugDisplay* getInstance() {
		static MapDebugDisplay instance;
		return &instance;
	}

	void register_map(Flowfield* map, std::string name)
	{
		m_flowfields.insert({ name, map });
	}

	bool isValid(std::string name)
	{

		return m_flowfields.contains(name);
	}

	void remove(Flowfield* map)
	{
		auto it = std::find_if(m_flowfields.begin(), m_flowfields.end(), [&map](auto& pair) {
			return pair.second == map;
			});
		m_flowfields.erase(it->first);
	}

	

	Flowfield* getCurrentMap()
	{
		return m_flowfields[m_currentMap];
	}

	void setCurrentMap(std::string map)
	{
		m_currentMap = map;
	}

	void setCurrentMap(Flowfield* map)
	{
		auto it = std::find_if(m_flowfields.begin(), m_flowfields.end(), [&map](auto& pair) {
			return pair.second == map;
			});
		if (it != m_flowfields.end())
			setCurrentMap(it->first);
	}

	std::string getCurrentMapName()
	{
		return m_currentMap;
	}

	std::string getCurrentName()
	{
	
		return m_currentMap;
	}

	auto& getData() {
		return m_flowfields;
	}
};

