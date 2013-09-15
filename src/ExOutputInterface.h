#ifndef __EX_OUTPUT_INTERFACE_H__
#define __EX_OUTPUT_INTERFACE_H__

#include <QtCore/QStateMachine>

namespace ExFSM {

class ExEvent;

class ExOutputInterface
{
public:
    virtual void putEvent(QEvent * event, QStateMachine::EventPriority = QStateMachine::NormalPriority) = 0;
    virtual void putEvent(ExEvent * event, QStateMachine::EventPriority = QStateMachine::NormalPriority) = 0;

};

} // ExFSM

#endif //__EX_OUTPUT_INTERFACE_H__
