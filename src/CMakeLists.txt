FIND_PACKAGE(Qt5Core REQUIRED)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)

ADD_DEFINITIONS(-DEXFSM_LIBRARY_EXPORT
                -D_EX_FSM_PRINT_INFO_
                -D_USE_CALLING_LOGGER
                )

SET(ExFSM_SRCS
        ExStateMachine.cpp
        ExEventFactory.cpp
        ExEventTransition.cpp
        ExMultiEventTransition.cpp
        ExConditionalTransition.cpp
        ExEvent.cpp
        ExFlags.cpp
        ExState.cpp
    )

ADD_LIBRARY(ExFSM STATIC ${ExFSM_SRCS} ${ExFSM_MOC_SRCS})
QT5_USE_MODULES(ExFSM Core)

TARGET_LINK_LIBRARIES(ExFSM calling_logger)

