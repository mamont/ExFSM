#include "ExMultiEventTransition.h"

#include "ExStateMachine.h"
#include <QtCore/QDebug>

namespace ExFSM {

//------------------------------------------------------------------------------
ExMultiEventTransition::ExMultiEventTransition(QObject * parent, QList<QEvent::Type> events, QState * source, QState * target, ExTransitionActionsSequence const& actions)
    : ExEventTransition(source)
    , m_events(events)
{
    if(m_events.isEmpty())
        qWarning() << "Event types list is empty. Emtpy won't ever be triggered";
}

//------------------------------------------------------------------------------
bool ExMultiEventTransition::eventTest(QEvent * ev)
{

/*    
    Q_ASSERT(ev);

    QStateMachine::WrappedEvent * wrapped = dynamic_cast<QStateMachine::WrappedEvent *>(ev);
    Q_ASSERT(wrapped);

	QEvent * rawEvent = wrapped->event();
	Q_ASSERT(rawEvent);

    if(m_events.contains(rawEvent->type()))
    {
    
    }


    if(rawEvent->type() == m_nestedEventType)
    {
        ev->setAccepted(true);

#ifdef _EX_FSM_DEBUG_
        qDebug() << "Result : true";
#endif
		return true;
    }

#ifdef _EX_FSM_DEBUG_
    qDebug() << "Result : false";
#endif
*/
    return false;
}

} // namespace ExFSM

