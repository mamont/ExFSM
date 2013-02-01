#ifndef __EX_FSM_EVENT_TRANSITION_H__
#define __EX_FSM_EVENT_TRANSITION_H__

#include <QtCore/QEvent>
#include <QtCore/QEventTransition>

namespace ExFSM {

//--------------------------------------------------------------------------------------------------
class ExTransitionAction
{
    QObject * m_obj;
    QByteArray m_method;
    Qt::ConnectionType m_type;

public:
    ExTransitionAction(QObject * obj, QByteArray const& method, Qt::ConnectionType type = Qt::AutoConnection);
    explicit ExTransitionAction(ExTransitionAction const& other);

    QObject * object() const { return m_obj; }
    const char * method() const { return m_method.constData(); }
    Qt::ConnectionType connectionType() const { return m_type; }
    bool isValid() const;
};

//--------------------------------------------------------------------------------------------------
class ExTransitionActionsSequence : public QList<ExTransitionAction>
{

public:
    explicit ExTransitionActionsSequence();
    ExTransitionActionsSequence(ExTransitionAction const &);
    ExTransitionActionsSequence & operator<<(ExTransitionAction const &);
};

//--------------------------------------------------------------------------------------------------
class ExEventTransition : public QEventTransition
{
    Q_OBJECT
    int m_nestedEventType;
    ExTransitionActionsSequence m_actions;

protected:
    virtual bool eventTest(QEvent * event);
    virtual void onTransition(QEvent *event);

public:
    ExEventTransition(QState * source);

    ExEventTransition(QEvent::Type, QState * source, QState * target);
    ExEventTransition(QEvent::Type, QState * source, QState * target, ExTransitionActionsSequence const& actions);

    ExEventTransition(QObject * object, QEvent::Type, QState * source, QState * target);
    ExEventTransition(QObject * object, QEvent::Type, QState * source, QState * target, ExTransitionActionsSequence const& actions);

    virtual ~ExEventTransition();

Q_SIGNALS:
    void triggered(QEvent * e);

};

} // ExFSM

#endif //!__EX_FSM_EVENT_TRANSITION_H__
