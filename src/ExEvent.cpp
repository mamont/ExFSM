#include "ExEvent.h"

const QEvent::Type ExFSM::ExEvent::None = QEvent::None;

namespace ExFSM {

ExEvent * ExEvent::fromQEvent(QEvent * ev)
{
    if(!ev)
        return 0;

    QStateMachine::WrappedEvent * wrappedEvent = static_cast<QStateMachine::WrappedEvent *>(ev);
    if(!wrappedEvent)
        return 0;

	QEvent * rawEvent = wrappedEvent->event();
    if(!rawEvent)
        return 0;

    ExEvent * exEvent = static_cast<ExEvent *>(rawEvent);
    return exEvent;
}

} // ExFSM

