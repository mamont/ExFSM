#ifndef __EX_FSM_EVENT_TRANSITION_H__
#define __EX_FSM_EVENT_TRANSITION_H__

#include <QtCore/QEvent>
#include <QtCore/QEventTransition>

#include "ExCommon.h"

namespace ExFSM {

//--------------------------------------------------------------------------------------------------
class EX_FSM_EXPORT ExTransitionAction
{
    QObject * m_obj;
    QByteArray m_method;
    Qt::ConnectionType m_type;

public:
    explicit ExTransitionAction();
    ExTransitionAction(ExTransitionAction const& other);
    ExTransitionAction(QObject * obj, QByteArray const& method, Qt::ConnectionType type = Qt::AutoConnection);

    QObject * object() const { return m_obj; }
    const char * method() const { return m_method.constData(); }
    Qt::ConnectionType connectionType() const { return m_type; }
    bool isValid() const;

    bool operator==(const ExTransitionAction & o) const { return false; }
};

//--------------------------------------------------------------------------------------------------
class EX_FSM_EXPORT ExTransitionActionsSequence
{
protected:
    QList<ExTransitionAction> m_actions;

public:
    explicit ExTransitionActionsSequence();
    explicit ExTransitionActionsSequence(ExTransitionAction const &);
    ExTransitionActionsSequence & operator<<(ExTransitionAction const &);

    QList<ExTransitionAction> const & actions() const { return m_actions; }
};

//--------------------------------------------------------------------------------------------------
class EX_FSM_EXPORT ExEventTransition : public QEventTransition
{
    Q_OBJECT

    int m_nestedEventType;
    ExTransitionActionsSequence m_actions;

protected:
    virtual bool eventTest(QEvent * event);
    virtual void onTransition(QEvent *event);

public:
    ExEventTransition(QState * source);
    ExEventTransition(QObject * object, QEvent::Type, QState * source, QState * target);
    ExEventTransition(QObject * object, QEvent::Type, QState * source, QState * target, ExTransitionActionsSequence const& actions);

    virtual ~ExEventTransition();

    virtual void setActions(ExTransitionActionsSequence const& actions);

Q_SIGNALS:
    void triggered(QEvent * e);

};

} // ExFSM

#endif //!__EX_FSM_EVENT_TRANSITION_H__
