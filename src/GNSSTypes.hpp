#ifndef GNSS_TYPES_HPP
#define GNSS_TYPES_HPP


#ifndef __orogen
    #include <vector>
#endif

/**
 * 
 */
//#include <vector>
#include <base/time.h>

/**
 * 
 */
namespace trimble_bd970 
{

    enum GNSS_SOLUTION_TYPES
    {
        INVALID      = 0,
        AUTONOMOUS   = 1,
        RTK_FLOAT    = 2,
        RTK_FIXED    = 3,
        DIFFERENTIAL = 4
    };

    struct Time
    {
      base::Time cpu_time;
      base::Time gnss_time;
      double processing_latency;
    };

    struct Solution
    {
        base::Time time;
        double latitude;
        double longitude;
        GNSS_SOLUTION_TYPES positionType;
        int noOfSatellites;
        double altitude;
        double geoidalSeparation;
        double ageOfDifferentialCorrections;

        double deviationLatitude;
        double deviationLongitude;
        double deviationAltitude;
#ifndef __orogen

        Solution()
            : positionType(INVALID)
        {
        }

#endif
    };

    struct Position 
    {
        base::Time time;
        double latitude;
        double longitude;
        GNSS_SOLUTION_TYPES positionType;
        int noOfSatellites;
        double altitude;
        double geoidalSeparation;
        double ageOfDifferentialCorrections;

#ifndef __orogen

        Position()
            : positionType(INVALID)
        {
        }

#endif

    };

    struct Errors 
    {
        base::Time time;
        double deviationLatitude;
        double deviationLongitude;
        double deviationAltitude;
    };

    struct SolutionQuality 
    {
        base::Time time;
        std::vector<int> usedSatellites;
        double pdop;
        double hdop;
        double vdop;
    };

    enum CONSTELLATIONS 
    {
        CONSTELLATION_GPS,
        CONSTELLATION_GALILEO,
        CONSTELLATION_SBAS,
        CONSTELLATION_GLONASS
    };

    struct Satellite 
    {
        int PRN;
        int elevation;
        int azimuth;
        double SNR;

#ifndef __orogen

        static CONSTELLATIONS getConstellationFromPRN(int prn)
        {
            if (prn < 33)
                return CONSTELLATION_GPS;
            else if (prn < 65)
                return CONSTELLATION_SBAS;
            else
                return CONSTELLATION_GLONASS;
        }

        CONSTELLATIONS getConstellation() const
        {
            return getConstellationFromPRN(PRN);
        }

#endif

    };

    struct SatelliteInfo 
    {
        base::Time time;
        std::vector < trimble_bd970::Satellite> knownSatellites;
    };

    struct UserDynamics 
    {
        int hSpeed;
        int hAccel;
        int vSpeed;
        int vAccel;
#ifndef __orogen

        UserDynamics()
            : hSpeed(0)
            , hAccel(0)
            , vSpeed(0)
            , vAccel(0)
            {
            }
#endif
    };

    struct ConstellationInfo 
    {
        trimble_bd970::SolutionQuality quality;
        trimble_bd970::SatelliteInfo  satellites;
    };

}

#endif //GNSS_TYPES_HPP

