
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


set(TEST_SOURCES
    test/generate.cpp
)

add_executable(
    hashiwokakero-lib-tests
    ${TEST_SOURCES}
)
target_link_libraries(hashiwokakero-lib-tests PRIVATE GTest::gtest_main hashiwokakero-lib)
target_include_directories(hashiwokakero-lib-tests PRIVATE src)

include(GoogleTest)
gtest_discover_tests(hashiwokakero-lib-tests)

