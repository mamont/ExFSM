#ifndef __EX_FSM_EVENT_H__
#define __EX_FSM_EVENT_H__

#include <QtCore/QEvent>
#include <QtCore/QStateMachine>

#include "ExCommon.h"

namespace ExFSM {

class EX_FSM_EXPORT ExEvent: public QEvent
{
public:
    static const QEvent::Type None;

    explicit ExEvent(QEvent::Type type) : QEvent(type) {;}
};



template <typename T>
class ExEventBase : public ExEvent
{
public:
    ExEventBase() : ExEvent(eventType()) { ; }

    static QEvent::Type eventType()
    {
        static QEvent::Type type = static_cast<QEvent::Type>(registerEventType());
        return type;
    }
};


class EX_FSM_EXPORT ExWrappedEvent : public QStateMachine::WrappedEvent
{

public:
    ExWrappedEvent(QEvent * e) : QStateMachine::WrappedEvent(0, e) {;}
};

} // ExFSM

#endif //!__EX_FSM_EVENT_H__

