#include "ExState.h"
#include "ExEvent.h"
#include "ExStateMachine.h"

#include <QtCore/QDebug>

#define _EX_FSM_DEBUG_

namespace ExFSM {

struct ExStatePrivate 
{
    QString m_name;
    QString m_prefix;
    ExFlags m_flags;

    QSet<QEvent::Type> m_savedEventTypes;
    QList<QEvent> m_savedEvents;

    ExStatePrivate(QString const& name, QString const& prefix)
        : m_name(name)
        , m_prefix(prefix)
    {;}
};


#ifdef WIN32
const QState * ExState::None = 0;
#endif

//-----------------------------------------------------------------------------
ExState::ExState(QString const& name, QString const& prefix)
    : m_pImpl(new ExStatePrivate(name, prefix))
{
    ;
}

//-----------------------------------------------------------------------------
ExState::ExState(QState * parent, QString const& name, QString const& prefix )
    : QState(parent)
    , m_pImpl(new ExStatePrivate(name, prefix))
{
    ;
}

//-----------------------------------------------------------------------------
ExState::~ExState()
{
    delete static_cast<ExStatePrivate*>(m_pImpl);
}

//-----------------------------------------------------------------------------
void ExState::setFlags(ExFlags const & flags)
{
    static_cast<ExStatePrivate*>(m_pImpl)->m_flags |= flags;
}

//-----------------------------------------------------------------------------
void ExState::unsetFlags(ExFlags const & flags)
{
    static_cast<ExStatePrivate*>(m_pImpl)->m_flags &= ~flags;
}

//-----------------------------------------------------------------------------
void ExState::onEntry( QEvent* e )
{
    //Q_EMIT entered(e);

    // Print out the state we are entering and it's parents
    QString state = name();
    ExState* parent = dynamic_cast<ExState*>( parentState() );
    while ( parent != 0 )
    {
        //state = parent->name() + "->" + state;
        parent = dynamic_cast<ExState*>( parent->parentState() );
    }
#ifdef _EX_FSM_DEBUG_
    qDebug() << prefix() << " >>> Entering state:" << state;
#endif

    QState::onEntry(e);
}

//-----------------------------------------------------------------------------
void ExState::onExit( QEvent* e )
{
    // Print out the state we are exiting and it's parents
    QString state = name();
    ExState* parent = dynamic_cast<ExState*>( parentState() );
    while ( parent != 0 )
    {
        //state = parent->name() + "->" + state;
        parent = dynamic_cast<ExState*>( parent->parentState() );
    }
#ifdef _EX_FSM_DEBUG_
    qDebug() << prefix() << " <<< Exiting state:" << state;
#endif

    QState::onExit(e);

    Q_FOREACH(QEvent const & savedEvent, static_cast<ExStatePrivate*>(m_pImpl)->m_savedEvents)
    {
#ifdef _EX_FSM_DEBUG_
        qDebug() << name() << " post: " << savedEvent.type();
#endif
        static_cast<ExStateMachine*>(machine())->postEvent(new QEvent(savedEvent));
    }
    static_cast<ExStatePrivate*>(m_pImpl)->m_savedEvents.clear();
}

//-----------------------------------------------------------------------------
void ExState::onUnexpectedEvent( QEvent * e )
{
    ExEvent * exEvent = ExEvent::fromQEvent(e);
    if(!exEvent)
        return;

#ifdef _EX_FSM_DEBUG_
    qDebug() << name() << " unexpected event : " << exEvent->type();
#endif

    if((static_cast<ExStatePrivate*>(m_pImpl)->m_savedEventTypes.contains(exEvent->type())))
    {
#ifdef _EX_FSM_DEBUG_
        qDebug() << name() << " Save unexpected event : " << exEvent->type();
#endif
        static_cast<ExStatePrivate*>(m_pImpl)->m_savedEvents.append(*exEvent);
    }
    else
    {
        Q_EMIT unexpectedEvent(exEvent);
    }
}

//-----------------------------------------------------------------------------
QString const & ExState::name() const
{
    return static_cast<ExStatePrivate*>(m_pImpl)->m_name;
}

//-----------------------------------------------------------------------------
QString const & ExState::prefix() const
{
    return static_cast<ExStatePrivate*>(m_pImpl)->m_prefix;
}

//-----------------------------------------------------------------------------
ExFlags const & ExState::flags() const
{
    return static_cast<ExStatePrivate*>(m_pImpl)->m_flags;
}

//-----------------------------------------------------------------------------
void ExState::addToSavedEventsList(QEvent::Type type)
{
    static_cast<ExStatePrivate*>(m_pImpl)->m_savedEventTypes.insert(type);
}

} // ExFSM
