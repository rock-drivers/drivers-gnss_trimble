rock_library(gnss_trimble
    SOURCES NMEABaseTypes.cpp NMEATypes.cpp SerialPort.cpp Bd970.cpp 
    HEADERS NMEABaseTypes.hpp NMEATypes.hpp Config.hpp SerialPort.hpp Bd970.hpp GNSSTypes.hpp Bd970Types.hpp
    DEPS_PKGCONFIG base-types iodrivers_base)

rock_executable(gnss_trimble_bin Main.cpp
DEPS gnss_trimble)

