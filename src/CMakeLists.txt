rock_library(bd970
    SOURCES Bd970.cpp
    HEADERS Bd970.hpp
    DEPS_PKGCONFIG iodrivers_base)


rock_executable(bd970_bin main.cpp
    DEPS bd970)

