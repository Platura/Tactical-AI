#pragma once
#include "../AI-manager/Field.h"
#include <unordered_map>
#include <string>

class EngineDebugData
{
	std::unordered_map<std::string, Field<float>*> m_data_field;

	std::string m_current_map;
public:

	static EngineDebugData* getInstance() {
		static EngineDebugData instance;
		return &instance;
	}
	
	void register_map(Field<float>* data, std::string name)
	{
		m_data_field.insert({ name, data });
	}

	void remove(Field<float>* map)
	{
		auto it = std::find_if(m_data_field.begin(), m_data_field.end(), [&map](auto& pair) {
			return pair.second == map;
			});
		if (it != m_data_field.end())
			m_data_field.erase(it->first);
	}


	void setCurrenMap(std::string key)
	{
		m_current_map = key;
	}

	void setCurrenMap(Field<float>* map)
	{
		auto it = std::find_if(m_data_field.begin(), m_data_field.end(), [&map](auto& pair) {
			return pair.second == map;
			});
		if (it != m_data_field.end())
			setCurrenMap(it->first);
	}

	bool hasValidSelection() const {
		return m_data_field.contains(m_current_map);
	}

	std::string const& getCurrentMap() const {
		return m_current_map;
	}

	auto const& getData() {
		return m_data_field;
	}
	auto& getSelectedMap() {
		return m_data_field[m_current_map];
	}
};

