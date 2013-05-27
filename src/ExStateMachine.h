#ifndef __EX_FSM_STATEMACHINE_H__
#define __EX_FSM_STATEMACHINE_H__

#include <QtCore/QStateMachine>
#include "ExCommon.h"

namespace ExFSM {

class ExEvent;
class ExFlag;

class EX_FSM_EXPORT ExStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    explicit ExStateMachine(QObject * parent = 0);
    virtual ~ExStateMachine();

    virtual bool isFlagActive(ExFlag const& flags) const;

    virtual void postEvent(QEvent * event, EventPriority = NormalPriority);
    virtual void postEvent(ExEvent * event, EventPriority = NormalPriority);

protected:
    virtual void beginSelectTransitions(QEvent *event);
    virtual void endSelectTransitions(QEvent *event);

    /*
    virtual void beginMicrostep(QEvent *event);
    virtual void endMicrostep(QEvent *event);
    */

};

} // ExFSM

#endif //__EX_FSM_STATEMACHINE_H__
