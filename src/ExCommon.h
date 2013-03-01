#ifndef __EX_FSM_COMMON_H__
#define __EX_FSM_COMMON_H__

#include <QtCore/QtGlobal>

#ifdef EX_FSM_LIB
    #define EX_FSM_EXPORT Q_DECL_EXPORT
#else
    #define EX_FSM_EXPORT Q_DECL_IMPORT
#endif

#endif // !__EX_FSM_COMMON_H__

