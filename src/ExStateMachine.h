#ifndef __EX_FSM_STATEMACHINE_H__
#define __EX_FSM_STATEMACHINE_H__

#include "ExOutputInterface.h"
#include "ExCommon.h"

namespace ExFSM {

class ExEvent;
class ExFlag;

class EX_FSM_EXPORT ExStateMachine : public QStateMachine, public ExOutputInterface
{
    Q_OBJECT

public:
    explicit ExStateMachine(QObject * parent = 0);
    virtual ~ExStateMachine();

    virtual bool isFlagActive(ExFlag const& flags) const;

    virtual void putEvent(QEvent * event, EventPriority = NormalPriority) override;
    virtual void putEvent(ExEvent * event, EventPriority = NormalPriority) override;

protected:
    virtual void beginSelectTransitions(QEvent *event);
    virtual void endSelectTransitions(QEvent *event);
};

} // ExFSM

#endif //__EX_FSM_STATEMACHINE_H__
