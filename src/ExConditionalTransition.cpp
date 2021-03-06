#include "ExConditionalTransition.h"
#include <QtCore/QStateMachine>


namespace ExFSM {


ExConditionalTransition::ExConditionalTransition(QObject * parent
                                                , QEvent::Type type
                                                , QState * source
                                                , QState * target
                                                , std::function<bool(QEvent * )> const& condition
                                                , ExTransitionActionsSequence const& actions)
    : ExEventTransition(parent, type, source, target, actions)
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

    QStateMachine::WrappedEvent * wrapped = dynamic_cast<QStateMachine::WrappedEvent *>(event);
    Q_ASSERT(wrapped);

    QEvent * rawEvent = wrapped->event();

    return m_cond(rawEvent);
}


} // ExFSM


