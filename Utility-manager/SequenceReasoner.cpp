#include "SequenceReasoner.h"

void SequenceReasoner::update(BlackboardManager& bm)
{
}

std::unique_ptr<IReasoner> SequenceReasoner::create(json const& parameter)
{
    return std::unique_ptr<IReasoner>();
}
