#ifndef __EX_FSM_STATE_H__
#define __EX_FSM_STATE_H__

#include <QtCore/QSet>
#include <QtCore/QState>
#include <QtCore/QEvent>
#include <QtCore/QString>

#include "ExFlags.h"
#include "ExCommon.h"

namespace ExFSM {

class ExEvent;

class EX_FSM_EXPORT ExState : public QState
{
    Q_OBJECT
    
    friend class ExStateMachine;
public:
    typedef quint32 Flag;

#ifdef WIN32
    static const QState * None;
#else
    static constexpr QState * None = nullptr;
#endif
    explicit ExState(QString const& name = QString::null, QString const& prefix = QString::null);
    explicit ExState(QState * parent, QString const& name = QString::null, QString const& prefix = QString::null);
    virtual ~ExState();

    QString const & name() const;
    ExFlags const & flags() const;

    void setFlags(ExFlags const & flags);
    void unsetFlags(ExFlags const & flags);

    void addToSavedEventsList(QEvent::Type type);

Q_SIGNALS:
    void unexpectedEvent( ExEvent* e );

protected:
    virtual void onEntry( QEvent* e );
    virtual void onExit( QEvent* e );
    virtual void onUnexpectedEvent( QEvent * );

private:
    void * m_pImpl;
};

} // ExFSM

#endif //!__EX_FSM_STATE_H__
