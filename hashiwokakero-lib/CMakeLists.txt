

set(LIB_SOURCES
    src/hashiwokakero.cpp
    src/island.cpp
    src/bridge.cpp
    src/board.cpp
    src/boardbuilder.cpp
    src/vectorboard.cpp
)

add_library(hashiwokakero-lib STATIC ${LIB_SOURCES})
target_include_directories(hashiwokakero-lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/>)
