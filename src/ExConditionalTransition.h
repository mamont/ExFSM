#ifndef __EX_CONDITIONAL_TRANSITION_H__
#define __EX_CONDITIONAL_TRANSITION_H__

#include "ExEventTransition.h"

#include <functional>

namespace ExFSM { 

class ExConditionalTransition : public ExEventTransition
{
    Q_OBJECT

    std::function<bool(QEvent * )> m_cond;

protected:
    bool eventTest(QEvent *event);

public:

    ExConditionalTransition(QObject * parent, QEvent::Type type, QState * source, QState * target, std::function<bool(QEvent * )> const& condition, ExTransitionActionsSequence const& actions = ExTransitionActionsSequence());
    void setCondition(std::function<bool(QEvent*)> condition);

};


} // ExFSM

#endif //__EX_CONDITIONAL_TRANSITION_H__

