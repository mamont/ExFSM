#include "ExEvent.h"

const QEvent::Type ExFSM::ExEvent::None = QEvent::None;

namespace ExFSM {

ExEvent * ExEvent::fromQEvent(QEvent * ev)
{
    QStateMachine::WrappedEvent * wrappedEvent = dynamic_cast<QStateMachine::WrappedEvent *>(ev);
    if(!wrappedEvent)
        return 0;

	QEvent * rawEvent = wrappedEvent->event();
    if(!rawEvent)
        return 0;

    ExEvent * exEvent = dynamic_cast<ExEvent *>(rawEvent);
    return exEvent;
}

} // ExFSM

