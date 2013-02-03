#include "ExStateMachine.h"

#include "ExEvent.h"
#include "ExFlags.h"
#include "ExState.h"

namespace ExFSM {

//--------------------------------------------------------------------------------------------------
ExStateMachine::ExStateMachine(QObject * parent)
    : QStateMachine(parent)
{
    ;
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
        ExState const * custate = dynamic_cast<ExState const * >(state);
        if(!custate)
            continue;

        result |= custate->flags().testFlag(flag);
    }

    return result;
}

//--------------------------------------------------------------------------------------------------
void ExStateMachine::postEvent(QEvent * event, EventPriority priority)
{
    const int type = event->type();
    if(type > QEvent::User)
        postEvent(new ExWrappedEvent(event), priority);
    else
        QStateMachine::postEvent(event, priority);
}

//--------------------------------------------------------------------------------------------------
void ExStateMachine::postEvent(ExEvent * event, EventPriority priority)
{
    QStateMachine::postEvent(new ExWrappedEvent(event), priority);
}

} // ExFSM
