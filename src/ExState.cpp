#include "ExState.h"
#include "ExEvent.h"
#include "ExStateMachine.h"
#include "ExLogger.h"

namespace ExFSM {

struct ExStatePrivate 
{
    QString m_name;
    QString m_prefix;
    ExFlags m_flags;

    QSet<QEvent::Type> m_savedEventTypes;
    QList<ExEvent*> m_savedEvents;

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
    // Print out the state we are entering and it's parents
#ifdef _EX_FSM_PRINT_INFO_
    QString state = name();
    ExState* parent = qobject_cast<ExState*>( parentState() );
    while ( parent != 0 )
    {
        state = parent->name() + "->" + state;
        parent = qobject_cast<ExState*>( parent->parentState() );
    }

    LOG_D("ExState") << prefix() << " >>> Entering state: '" << state << "'";
#endif

    QState::onEntry(e);
}

//-----------------------------------------------------------------------------
void ExState::onExit( QEvent* e )
{
    // Print out the state we are exiting and it's parents
#ifdef _EX_FSM_PRINT_INFO_
    QString state = name();
    ExState* parent = qobject_cast<ExState*>( parentState() );
    while ( parent != 0 )
    {
        state = parent->name() + "->" + state;
        parent = qobject_cast<ExState*>( parent->parentState() );
    }
    LOG_D("ExState") << prefix() << " <<< Exiting state: '" << state << "'";
#endif

    QState::onExit(e);

    Q_FOREACH(ExEvent* const & savedEvent, static_cast<ExStatePrivate*>(m_pImpl)->m_savedEvents)
    {
#ifdef _EX_FSM_PRINT_INFO_
        LOG_D("ExState") << prefix() << " - " << name() << ": Post saved event: '" << savedEvent->name() << "'";
#endif
        static_cast<ExStateMachine*>(machine())->putEvent(savedEvent);
    }
    static_cast<ExStatePrivate*>(m_pImpl)->m_savedEvents.clear();
}

//-----------------------------------------------------------------------------
void ExState::onUnexpectedEvent( QEvent * e )
{
    ExEvent* exEvent = ExEvent::fromQEvent(e);

    if(!exEvent)
        return;

#ifdef _EX_FSM_PRINT_INFO_
    LOG_D("ExState") << prefix() << " - " << name() << ": Unexpected event: '" << exEvent->name() << "'";
#endif

    if((static_cast<ExStatePrivate*>(m_pImpl)->m_savedEventTypes.contains(exEvent->type())))
    {
#ifdef _EX_FSM_PRINT_INFO_
        LOG_D("ExState") << prefix() << " - " << name() << ": Save unexpected event: '" << exEvent->name() << "'";
#endif
        static_cast<ExStatePrivate*>(m_pImpl)->m_savedEvents.append(exEvent->clone());
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
