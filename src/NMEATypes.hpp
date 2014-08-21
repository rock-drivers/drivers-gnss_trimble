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
 *    NMEATypes.hpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */

#ifndef _BD970_NMEA_TYPES_HPP_
#define _BD970_NMEA_TYPES_HPP_


/** Std C++ libraries **/
#include <string>

/** Std C Libraries **/
#include <stdint.h>

/** Rock Std types **/
#include <base/Time.hpp>

/** BD970 Driver Types **/
#include <trimble_bd970/NMEABaseTypes.hpp>
#include <trimble_bd970/Config.hpp>



/** CONFIGURATIONS 
 *  
 *  This must be modified to the number of desired NMEA messages from receiver.
 *  
 */
#define NMEA_MESSAGE_NUM    3

/**
 * 
 * 
 */
namespace trimble_bd970
{
    
    /**
     * 
     * 
     */
    enum NMEA_TAG
    {
        NULL      = 0,
        GGA       = 1,
        PTNL_AVR  = 2,
        HDT       = 3
    }
    
    
    /**
     * 
     * 
     */
    
    class NMEA_GGA : public NMEA_Base
    {
        public:
        
            /** Message Data **/
            double      utc;
            
            double      latitude;
            std::string lat_dir;
            
            double      longtitude;
            std::string long_dir;
            
            int         gps_quality;
            int         num_sat_vehicles;
            double      hdop;
            
            double      orthom_height;
            double      geoid_separation;
            double      dgps_age;
            int         ref_station_id;
            
            
            NMEA_GGA(void);
            
            ~NMEA_GGA(void);
            
            
            int extractMessage(uint8_t *buffer, int message_len);
            
            int printMessage(void);
        
    };
    
    class NMEA_AVR : public NMEA_Base
    {
        public:
            
            /** Message Data **/
            double      utc;
            
            double      yaw;
            double      tilt;
            
            double      range;
            int         gps_quality;
            double      pdop;
            int         num_sat_vehicles;
            
            
            NMEA_AVR(void);
            
            ~NMEA_AVR(void);
            
            
            int extractMessage(uint8_t *buffer, int message_len);
            
            int printMessage(void);
        
    };
    
    class NMEA_HDT : public NMEA_Base
    {
        public:
            
            /** Message Data **/
            double      heading;
            std::string heading_dir;
            
            
            NMEA_HDT(void);
            
            ~NMEA_HDT(void);
            
            
            int extractMessage(uint8_t *buffer, int message_len);
            
            int printMessage(void);
        
    };
    
    
    /**
     * 
     * 
     */
    /*
    class NMEA_Messages
    {
        public:
            
            int m_number_messages;
            
            int *m_message_lengths;
            
            base::Time  m_rx_time;
            base::Time  m_tx_time;
            
            NMEA_GGA data_gga;
            NMEA_GST data_gst;
            NMEA_AVR data_avr;
            NMEA_HDT data_hdt;
            NMEA_GSA data_gsa;
            
            
            NMEA_Messages(void);
            
            ~NMEA_Messages(void);
            
            
            int extractNMEA(uint8_t *buffer);
            
            int printMessages(void);
        
    };
    */
}

#endif // _BD970_NMEA_TYPES_HPP_
