#ifndef __EX_FSM_LOGGER_H__
#define __EX_FSM_LOGGER_H__

#ifdef _USE_CALLING_LOGGER

#include <Logger>

#else

#include <QtCore/QDebug>

#define LOG(COMPONENT_ID) qDebug() << COMPONENT_ID << ": "
#define LOG_D(COMPONENT_ID) qDebug() << COMPONENT_ID << ": "
#define LOG_W(COMPONENT_ID) qWarning() << COMPONENT_ID << ": "
#define LOG_C(COMPONENT_ID) qCritical() << COMPONENT_ID << ": "

#endif

#endif // !__EX_FSM_LOGGER_H__

