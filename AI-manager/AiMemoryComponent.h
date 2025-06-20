#pragma once
#include "IComponent.h"

enum class status {
    idle,
    move,
    shoot,
    cover,
    melee,
    reload,
    active,
    done,
};

class AiMemoryComponent :
    public IComponent
{
public:
    void render(Agent* a, sf::RenderTarget& rt) const override;
    void update(Agent*, float deltaTime, AgentManager*) override;

    status getCurrentStatus() const { return m_current_status; }
    void setCurrentStatus(status new_status) {
        m_current_status = new_status;
        is_finished = false;
    }

    bool isActionRunning() const { return !is_finished; }
    
private:
    status m_current_status = status::idle;
    bool is_finished = false;
};

