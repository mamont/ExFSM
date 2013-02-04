#include "ExEventTransition.h"

#include <QtCore/QState>
#include <QtCore/QStateMachine>

namespace ExFSM {

//--------------------------------------------------------------------------------------------------
ExTransitionAction::ExTransitionAction(QObject * obj, QByteArray const& slot, Qt::ConnectionType type)
    : m_obj(obj)
    , m_method(slot)
    , m_type(type)
{
    ;
}

ExTransitionAction::ExTransitionAction(ExTransitionAction const& other)
{
    m_obj = other.m_obj;
    m_method = other.m_method;
    m_type = other.m_type;
}

bool ExTransitionAction::isValid() const
{
    return (m_obj && !m_method.isEmpty());
}

//--------------------------------------------------------------------------------------------------
ExTransitionActionsSequence::ExTransitionActionsSequence()
{
    ;
}

ExTransitionActionsSequence::ExTransitionActionsSequence(ExTransitionAction const&)
{
    ;
}

ExTransitionActionsSequence & ExTransitionActionsSequence::operator<<(ExTransitionAction const & o)
{
    this->append(o);
    return * this;
}








//--------------------------------------------------------------------------------------------------
ExEventTransition::ExEventTransition(QState * source)
    : QEventTransition(source)
    , m_nestedEventType(0)
{
    ;
}

//--------------------------------------------------------------------------------------------------
ExEventTransition::ExEventTransition(QObject * object, QEvent::Type type, QState * source, QState * target)
    : QEventTransition(object, QEvent::StateMachineWrapped, source)
    , m_nestedEventType(type)
{
    if(target)
        setTargetState(target);
}

//--------------------------------------------------------------------------------------------------
ExEventTransition::ExEventTransition(QObject * object, QEvent::Type type, QState * source, QState * target, ExTransitionActionsSequence const& actions)
    : QEventTransition(object, QEvent::StateMachineWrapped, source)
    , m_nestedEventType(type)
    , m_actions(actions)
{
    if(target)
        setTargetState(target);
}

//--------------------------------------------------------------------------------------------------
ExEventTransition::~ExEventTransition()
{
    ;
}

//--------------------------------------------------------------------------------------------------
bool ExEventTransition::eventTest(QEvent * ev)
{
    Q_ASSERT(ev);

    if(ev->type() != QEvent::StateMachineWrapped)
		return QEventTransition::eventTest(ev);

    QStateMachine::WrappedEvent * wrapped = dynamic_cast<QStateMachine::WrappedEvent *>(ev);
    Q_ASSERT(wrapped);

	QEvent * rawEvent = wrapped->event();
	Q_ASSERT(rawEvent);

    if(rawEvent->type() == m_nestedEventType)
		return true;

    return false;
}

//--------------------------------------------------------------------------------------------------
void ExEventTransition::onTransition(QEvent *event)
{
    QEvent * ev = event;
    if(event->type() == QEvent::StateMachineWrapped)
    {
        QStateMachine::WrappedEvent * wrapped = dynamic_cast<QStateMachine::WrappedEvent *>(event);
        Q_ASSERT(wrapped);

        ev = wrapped->event();
    }

    if(!m_actions.isEmpty())
    {
        Q_FOREACH(ExTransitionAction const& action, m_actions)
        {
            QMetaObject::invokeMethod(action.object(), action.method(), action.connectionType(), Q_ARG(QEvent*, ev));
        }
    }

    //QEventTransition::onTransition(event);
    QEventTransition::onTransition(ev);

    Q_EMIT triggered(ev);
}

} // ExFSM
