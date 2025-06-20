#pragma once
#include "Option.h"

class IReasoner
{
private:

public:
	using ptr = std::unique_ptr<IReasoner>;

	virtual void update(BlackboardManager& bm) = 0;
	virtual void addOption(Option::ptr option);


	void enable() { m_enabled = true; };
	void disable() { m_enabled = false; };
	bool isEnabled() const { return m_enabled; };
	Option* getSelectedOption()
	{
		return m_options[m_bestOption].get();
	};

	size_t getSelectedOptionId() const {
		return m_bestOption;
	}

	Option& getOption(size_t id) {
		return *m_options[id];
	}

	virtual void drawDebug();

protected:
	bool m_enabled;
	std::vector<Option::ptr> m_options;
	int m_bestOption;
};

