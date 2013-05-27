PROJECT (ExFSM)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.10)

IF(UNIX)
    ADD_DEFINITIONS(-std=c++11)
ENDIF(UNIX)

add_subdirectory(src)

INCLUDE_DIRECTORIES(include)
add_subdirectory(tests)

