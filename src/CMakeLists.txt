rock_library(trimble_bd970
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(trimble_bd970_bin Main.cpp
    DEPS trimble_bd970)

