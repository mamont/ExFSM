#include "ExState.h"

#include <QtCore/QDebug>

namespace ExFSM {

#ifdef WIN32
const QState * ExState::None = 0;
#endif

ExState::ExState(QString const& name, QString const& prefix)
    : m_name(name)
    , m_prefix(prefix)
{
    ;
}

ExState::ExState(QState * parent, QString const& name, QString const& prefix )
    : QState(parent)
    , m_name(name)
    , m_prefix(prefix)
{
    ;
}

//-----------------------------------------------------------------------------
void ExState::setFlags(ExFlags const & flags)
{
    m_flags |= flags;
}

//-----------------------------------------------------------------------------
void ExState::unsetFlags(ExFlags const & flags)
{
    m_flags &= ~flags;
}

//-----------------------------------------------------------------------------
void ExState::onEntry( QEvent* e )
{
    //Q_EMIT entered(e);

    // Print out the state we are entering and it's parents
    QString state = m_name;
    ExState* parent = dynamic_cast<ExState*>( parentState() );
    while ( parent != 0 )
    {
        state = parent->name() + "->" + state;
        parent = dynamic_cast<ExState*>( parent->parentState() );
    }
    qDebug() << m_prefix << " >>> Entering state:" << state;

    QState::onEntry(e);
}

//-----------------------------------------------------------------------------
void ExState::onExit( QEvent* e )
{
    // Print out the state we are exiting and it's parents
    QString state = m_name;
    ExState* parent = dynamic_cast<ExState*>( parentState() );
    while ( parent != 0 )
    {
        state = parent->name() + "->" + state;
        parent = dynamic_cast<ExState*>( parent->parentState() );
    }
    qDebug() << m_prefix << " <<< Exiting state:" << state;

    QState::onExit(e);
}

} // ExFSM
