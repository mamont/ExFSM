#include "ExEventFactory.h"

#include <QtCore/QStateMachine>
#include <QtCore/QDebug>

namespace ExFSM {

ExEventFactory::ExEventFactory(QStateMachine * fsm)
    : QObject(fsm)
    , m_fsm(fsm)
{
    ;
}

//--------------------------------------------------------------------------------------------------
ExEventFactory::~ExEventFactory()
{
    ;
}

//--------------------------------------------------------------------------------------------------
ExEvent * ExEventFactory::constructEvent(QVariant const& data)
{
    Q_UNUSED(data);


    return NULL;
}

//--------------------------------------------------------------------------------------------------
bool ExEventFactory::postEvent(QVariant const& data)
{
    QEvent * event = parseEvent(data);
    if(!event)
        return false;

    m_fsm->postEvent(event);

    return true;
}

//--------------------------------------------------------------------------------------------------
QEvent * ExEventFactory::parseEvent(QVariant const& json) const
{
    return 0;
}

} // ExFSM

