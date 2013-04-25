#ifndef __EX_FSM_STATE_H__
#define __EX_FSM_STATE_H__

#include <QtCore/QSet>
#include <QtCore/QState>
#include <QtCore/QString>

#include "ExFlags.h"
#include "ExCommon.h"

namespace ExFSM {

class EX_FSM_EXPORT ExState : public QState
{

public:
    typedef quint32 Flag;

#ifdef WIN32
    static const QState * None;
#else
    static constexpr QState * None = nullptr;
#endif
    explicit ExState(QString const& name = QString::null, QString const& prefix = QString::null);
    explicit ExState(QState * parent, QString const& name = QString::null, QString const& prefix = QString::null);

    QString const & name() const { return m_name; }
    ExFlags const & flags() const { return m_flags; }

    void setFlags(ExFlags const & flags);
    void unsetFlags(ExFlags const & flags);

protected:
    virtual void onEntry( QEvent* e );
    virtual void onExit( QEvent* e );

private:
    QString m_name;
    QString m_prefix;
    ExFlags m_flags;
};

} // ExFSM

#endif //!__EX_FSM_STATE_H__
