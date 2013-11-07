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

    explicit ExEvent(QEvent::Type type = QEvent::None) : QEvent(type) {;}
    virtual QEvent::Type myEventType() = 0;
    virtual ~ExEvent()  {;}

    static ExEvent * fromQEvent(QEvent *);
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

    virtual QEvent::Type myEventType()
    {
        return eventType();
    }
};


class EX_FSM_EXPORT ExWrappedEvent : public QStateMachine::WrappedEvent
{

public:
    ExWrappedEvent(QEvent * e) : QStateMachine::WrappedEvent(0, e) {;}
};

} // ExFSM

Q_DECLARE_METATYPE(ExFSM::ExEvent*);

#endif //!__EX_FSM_EVENT_H__

