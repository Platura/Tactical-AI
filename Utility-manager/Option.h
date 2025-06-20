#pragma once
#include <iostream>
#include "IConsideration.h"
#include "IAction.h"
#include <unordered_map>
#include <any>

#include <memory>

class Option
{
	std::string name;
	float last_value = 0;

	std::vector<ConsiderationPtr> considerations ;
	
	std::vector<IAction::ptr> m_actions;
	
	bool is_interruptible = false;
	
	// +TODO: Remove parameter
	std::unordered_map<std::string, std::any> m_parameter;
public:
	using ptr = std::shared_ptr<Option>;
	using ActionIt = std::vector<IAction::ptr>::iterator;
	


	Option(std::string name);
	Option(Option const&) = delete;
	Option(Option &&) noexcept = default;

	void addConsideration(ConsiderationPtr p_consideration);
	void addAction(IAction::ptr&& action);
	
	ActionIt getActionsBegin() {
		return m_actions.begin();
	}
	ActionIt getActionEnd() {
		return m_actions.end();
	}

	size_t getActionCount() {
		return m_actions.size();
	}

	void setInterruptible(bool value) {
		is_interruptible = value;
	}
	bool isInterruptible() const { return is_interruptible; }

	template <typename T>
	void setParameter(std::string key, T data)
	{
		m_parameter.insert({ key, std::any(data) });
	}

	template<typename T>
	T getParameter(std::string key)
	{
		return std::any_cast<T>(m_parameter.at(key));
	}

	float compute(BlackboardManager& bm);

	std::string getName() const { return name; }
	float getLastValue() const { return last_value; }

	void DrawDebugUi();
};

