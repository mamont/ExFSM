#ifndef __EX_FSM_STATEMACHINE_H__
#define __EX_FSM_STATEMACHINE_H__

#include <QtCore/QStateMachine>

namespace ExFSM {

class ExEvent;
class ExFlag;

class ExStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    explicit ExStateMachine(QObject * parent = 0);
    virtual ~ExStateMachine();

    virtual bool isFlagActive(ExFlag const& flags) const;

    virtual void postEvent(QEvent * event, EventPriority = NormalPriority);
    virtual void postEvent(ExEvent * event, EventPriority = NormalPriority);
};

} // ExFSM

#endif //__EX_FSM_STATEMACHINE_H__
