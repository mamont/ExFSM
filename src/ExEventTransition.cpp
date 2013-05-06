#include "ExEventTransition.h"

#include <QtCore/QState>
#include <QtCore/QStateMachine>
#include <QtCore/QRegExp>
#include <QDebug>

namespace ExFSM {

//--------------------------------------------------------------------------------------------------
ExTransitionAction::ExTransitionAction()
{
    ;
}

//--------------------------------------------------------------------------------------------------
ExTransitionAction::ExTransitionAction(QObject * obj, QByteArray const& methodSignature, Qt::ConnectionType type)
    : m_obj(obj)
    , m_methodSignature(QMetaObject::normalizedSignature(methodSignature))
    , m_type(type)
{
    QMetaObject const * mo = obj->metaObject();
    const int methodIdx = mo->indexOfMethod(m_methodSignature);

    m_metaMethod = mo->method(methodIdx);
}

//--------------------------------------------------------------------------------------------------
ExTransitionAction::ExTransitionAction(ExTransitionAction const& other)
{
    m_obj = other.m_obj;
    m_methodSignature = other.m_methodSignature;
    m_type = other.m_type;
    m_metaMethod = other.m_metaMethod;
}

//--------------------------------------------------------------------------------------------------
bool ExTransitionAction::isValid() const
{
    return (m_obj && m_metaMethod.isValid());
}

//--------------------------------------------------------------------------------------------------
ExTransitionActionsSequence::ExTransitionActionsSequence()
{
    ;
}

//--------------------------------------------------------------------------------------------------
ExTransitionActionsSequence::ExTransitionActionsSequence(ExTransitionAction const&)
{
    ;
}

//--------------------------------------------------------------------------------------------------
ExTransitionActionsSequence & ExTransitionActionsSequence::operator<<(ExTransitionAction const & o)
{
    m_actions.append(o);
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
void ExEventTransition::setActions(ExTransitionActionsSequence const& actions)
{
    m_actions = actions;

    Q_FOREACH(ExTransitionAction const& action, m_actions.actions())
    {
        if(action.isValid())
            connect(this, SIGNAL(triggered(QEvent *)), action.object(), action.methodSignature());
    }
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

    if(!m_actions.actions().isEmpty())
    {
        Q_FOREACH(ExTransitionAction const& action, m_actions.actions())
        {
            action.method().invoke(action.object()
                                    , action.connectionType()
                                    , Q_ARG(QEvent*, ev));
        }
    }

    QEventTransition::onTransition(ev);
    Q_EMIT triggered(ev);
}

} // ExFSM

