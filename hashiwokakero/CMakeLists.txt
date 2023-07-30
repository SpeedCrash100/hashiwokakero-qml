
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 COMPONENTS Quick Gui REQUIRED)

# Set qml prefix to :/qt/qml
qt_policy(SET QTP0001 NEW)


set(APP_SRCS
    src/main.cpp
    src/boardlogic.cpp
)

qt_add_executable(hashiwokakero ${APP_SRCS})

target_link_libraries(hashiwokakero PRIVATE hashiwokakero-lib)
target_link_libraries(hashiwokakero PRIVATE Qt6::Gui Qt6::Quick)
target_include_directories(hashiwokakero PRIVATE src)
target_compile_features(hashiwokakero PRIVATE cxx_std_20)

qt_add_qml_module(hashiwokakero
    URI .
    VERSION 1.0
    QML_FILES
        ui/main.qml
        ui/Board.qml
        ui/Island.qml
)


