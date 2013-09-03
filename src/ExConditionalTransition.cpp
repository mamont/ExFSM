#include "ExConditionalTransition.h"

namespace ExFSM {


ExConditionalTransition::ExConditionalTransition(QObject * parent
                                                , QEvent::Type type
                                                , QState * source
                                                , QState * target
                                                , std::function<bool(QEvent * )> const& condition
                                                , ExTransitionActionsSequence const& actions)
    : ExEventTransition(parent, type, source, target)
    , m_cond(condition)
{
    ;
}

void ExConditionalTransition::setCondition(std::function<bool(QEvent*)> condition)
{
    m_cond = condition;
}

bool ExConditionalTransition::eventTest(QEvent *event)
{
    if(!ExEventTransition::eventTest(event))
        return false;

    return m_cond(event);
}


} // ExFSM


