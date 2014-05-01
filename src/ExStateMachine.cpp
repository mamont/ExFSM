#include "ExStateMachine.h"

#include <QtCore/QDebug>

#include "ExEvent.h"
#include "ExFlags.h"
#include "ExState.h"
#include "ExLogger.h"

namespace ExFSM {

//--------------------------------------------------------------------------------------------------
ExStateMachine::ExStateMachine(QObject * parent)
    : QStateMachine(parent)
{
    qRegisterMetaType<ExEvent*>("ExEvent*");
}

//--------------------------------------------------------------------------------------------------
ExStateMachine::~ExStateMachine()
{
    ;
}

//--------------------------------------------------------------------------------------------------
bool ExStateMachine::isFlagActive(ExFlag const& flag) const
{
    bool result = false;
    QSet<QAbstractState *> const & states = configuration();

    Q_FOREACH(QAbstractState const * state, states)
    {
        ExState const * custate = qobject_cast<ExState const * >(state);
        if(!custate)
            continue;

        result |= custate->flags().testFlag(flag);
    }

    return result;
}

//--------------------------------------------------------------------------------------------------
void ExStateMachine::putEvent(QEvent * event, EventPriority priority)
{
    const int type = event->type();
    if(type > QEvent::User)
        putEvent(new ExWrappedEvent(event), priority);
    else
        QStateMachine::postEvent(event, priority);
}

//--------------------------------------------------------------------------------------------------
void ExStateMachine::putEvent(ExEvent * event, EventPriority priority)
{
#ifdef _EX_FSM_PRINT_INFO_
    LOG_D("ExStateMachine") << "put event: '" << event->name() << "'";
#endif

    QStateMachine::postEvent(new ExWrappedEvent(event), priority);
}

//--------------------------------------------------------------------------------------------------
void ExStateMachine::beginSelectTransitions(QEvent *event)
{
    QStateMachine::beginSelectTransitions(event);

    if(event->type() != QEvent::None)
        event->setAccepted(false);
}

//--------------------------------------------------------------------------------------------------
void ExStateMachine::endSelectTransitions(QEvent *event)
{
    if(event->type() != QEvent::None)
    {
        if(!event->isAccepted())
        {
            QSet<QAbstractState*> const config = configuration();
            QSet<QAbstractState*>::const_iterator it = config.constBegin();
            for(; it != config.constEnd(); ++it)
            {
                ExState * exstate = qobject_cast<ExState *>(*it);
                if(!exstate)
                    continue;

                exstate->onUnexpectedEvent(event);
            }

        }
        else
        {
#ifdef _EX_FSM_PRINT_INFO_
            ExEvent* exEvent = ExEvent::fromQEvent(event);

            if(exEvent)
            {
                QString stateName;
                QSet<QAbstractState*> const config = configuration();
                QSet<QAbstractState*>::const_iterator it = config.constBegin();
                for(; it != config.constEnd(); ++it)
                {
                    ExState * exstate = qobject_cast<ExState *>(*it);
                    if(!exstate)
                        continue;
                    stateName = exstate->name() + (stateName.isEmpty() ? "" : "->") + stateName;
                }

                LOG_D("ExStateMachine") << "In state '" << stateName << "' event '" << exEvent->name() << "' has been accepted";
            }
#endif
        }
    }

    QStateMachine::endSelectTransitions(event);
}


} // ExFSM
