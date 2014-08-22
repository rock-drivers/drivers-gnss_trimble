rock_library(trimble_bd970
    SOURCES NMEABaseTypes.cpp NMEATypes.cpp SerialPort.cpp Bd970.cpp 
    HEADERS NMEABaseTypes.hpp NMEATypes.hpp Config.hpp SerialPort.hpp Bd970.hpp GNSSTypes.hpp Bd970Types.hpp
    DEPS_PKGCONFIG base-types iodrivers_base)

rock_executable(trimble_bd970_bin Main.cpp
DEPS trimble_bd970)

