

set(LIB_SOURCES
    src/hashiwokakero.cpp
)

add_library(hashiwokakero-lib STATIC ${LIB_SOURCES})
target_include_directories(hashiwokakero-lib PUBLIC ./include)
