#ifndef BD970_TYPES_HPP
#define BD970_TYPES_HPP



namespace trimble_bd970
{
    enum BD970_FIRMWARE_OPTIONS
    {
        BD970_UPDATE_RATE        = 1,
        BD970_RTK_ROVER          = 2,
        BD970_RTK_BASE           = 4,
        BD970_PPS_OUTPUT         = 8,
        BD970_EVENT_MARKER       = 16,
        BD970_SBAS_TRACKING      = 32,
        BD970_GLONASS_TRACKING   = 64,
        BD970_RTK_MOVING_BASE    = 128,
        BD970_HEADING            = 256,
        BD970_ADVANCED_MULTIPATH = 512
    };

    enum BD970_DYNAMICS_MODEL
    {
        BD970_STATIC       = 1,
        BD970_QUASI_STATIC = 2,
        BD970_WALKING      = 3,
        BD970_SHIP         = 4,
        BD970_AUTOMOBILE   = 5,
        BD970_AIRCRAFT     = 6,
        BD970_UNLIMITED    = 7,
        BD970_ADAPTIVE     = 8,
        BD970_USER_DEFINED = 9
    };

    enum BD970_AMBIGUITY_THRESHOLD
    {
        BD970_NO_FIX     = 0,
        BD970_FIX_95_0 = 1,
        BD970_FIX_99_0 = 2,
        BD970_FIX_99_9 = 3
    };

    enum BD970_GNSS_MODE
    {
        BD970_GP_L1   = 0,
        BD970_GPGL_L1 = 1,
        BD970_GP_L2   = 2,
        BD970_GP_L2CS = 3,
        BD970_GPGL_L1L2 = 4,
        BD970_GPGL_L1L2CS = 5
    };
}

#endif //BD970_TYPES_HPP
