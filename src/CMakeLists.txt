FIND_PACKAGE(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(ExFSM_SRCS
        ExStateMachine.cpp
        ExEventFactory.cpp
        ExEventTransition.cpp
        ExEvent.cpp
        ExFlags.cpp
        ExState.cpp

    )

set(ExFSM_HDRS
        ExStateMachine.h
        ExEventFactory.h
        ExEventTransition.h
        #ExEvent.h
        #ExFlags.h
        #ExState.h

    )


QT4_WRAP_CPP(ExFSM_MOC_SRCS ${ExFSM_HDRS})

ADD_LIBRARY(ExFSM SHARED ${ExFSM_SRCS} ${ExFSM_MOC_SRCS})

#INSTALL( TARGETS ExFSM ARCHIVE )

