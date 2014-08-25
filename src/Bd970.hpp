/*    Robotic Construction Kit (ROCK) Driver  for the BD970 GNSS receiver 
 *    from Trimble.
 *    Copyright (C) 2014  Vassilios Tsounis
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *    
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *    
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    Bd970.hpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */



#ifndef _BD970_HPP_
#define _BD970_HPP_


/** Std C++ libraries **/
#include <string>

/** Std C Libraries **/
#include <stdint.h>

/** Rock Std types **/
#include <base/Time.hpp>

/** BD970 Driver Types **/
#include <trimble_bd970/Config.hpp>
#include <trimble_bd970/NMEATypes.hpp>
#include <trimble_bd970/SerialPort.hpp>
#include <trimble_bd970/GNSSTypes.hpp>
#include <trimble_bd970/Bd970Types.hpp>

//#include <ogr_spatialref.h>

/**
 * 
 */


/**
 * 
 */
namespace trimble_bd970
{
    static const int OK = 0;
    static const int ERROR = -1;
    static const std::string  NMEA_PORT_EMU =  "/home/vassilis/ttyV0";
    static const std::string NMEA_PORT = "/dev/ttyXR0";
    static const std::string RTK_PORT = "/dev/ttyXR1";


    /**
     * 
     */
    class Bd970
    {
        private:

            Config bd970Config;


        protected:

            NMEA_Messages       m_current_nmea;

            SerialPort          NmeaRxPort;

            //RTK_Messages      m_current_rtk;
            //
            //SerialPort        RtkTxPort;


        public:


            Bd970(int max_packet_size, float sampling_frequency);

            Bd970(const Config& config = Config());

            ~Bd970(void);

            void Greeting (void);

            int setupNMEA (std::string const& filename, int baudrate);

            int processNMEA (void);

            int printNMEA (void);

            trimble_bd970::Time getTime(void);

            trimble_bd970::Solution getSolution(void);

            int printBufferNMEA (void);

            int closeNMEA (void);

            //int setupRTK (std::string const& filename, int baudrate);
            //
            //int getRTK (void);
            //
            //int sendRTK (void);
            //
            //int printRTK (void);
            //
            //
        private:

            double interpretAngle(double const &value, const bool positive);

    };

} // end namespace bd970

#endif // _BD970_HPP_
