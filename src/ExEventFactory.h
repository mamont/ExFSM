#ifndef __EX_FSM_EVENTS_FACTORY_H__
#define __EX_FSM_EVENTS_FACTORY_H__

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "ExEvent.h"
#include "ExCommon.h"

class QStateMachine;

namespace ExFSM {

/**
 * @brief The ExEventFactory class
 *
 * Construct event objects
 */
class EX_FSM_EXPORT ExEventFactory : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ExEventFactory)

    QStateMachine * m_fsm;

public:
    explicit ExEventFactory(QStateMachine * fsm);
    ~ExEventFactory();

    ExEvent * constructEvent(QVariant const& data);
    bool postEvent(QVariant const& data);

    virtual QEvent * parseEvent(QVariant const& data) const;
};

}

#endif //!__EX_FSM_EVENTS_FACTORY_H__
