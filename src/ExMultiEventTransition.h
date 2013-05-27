// =====================================================================================
// 
//       Filename:  ExMultiEventTransition.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/20/2013 09:59:52 PM EEST
//       Revision:  none
//       Compiler:  gcc
// 
//         Author:  Sergey A Chertkov, aka hunter, chertkov.s.a@gmail.com
//        Company:  HSoft
// 
// =====================================================================================

#ifndef  __EX_MULTIEVENT_TRANSITION_H__
#define  __EX_MULTIEVENT_TRANSITION_H__

#include "ExEventTransition.h"

namespace ExFSM {

class EX_FSM_EXPORT ExMultiEventTransition : public ExEventTransition
{
    Q_OBJECT

    QList<QEvent::Type> m_events;
protected:
    virtual bool eventTest(QEvent * );

public:
    ExMultiEventTransition(QObject * object, QList<QEvent::Type> events, QState * source, QState * target, ExTransitionActionsSequence const& actions = ExTransitionActionsSequence());
    
};

} // namespace ExFSM

#endif //__EX_MULTIEVENT_TRANSITION_H__


