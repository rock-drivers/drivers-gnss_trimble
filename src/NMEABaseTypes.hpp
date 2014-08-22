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
 *    NMEABaseTypes.hpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */


#ifndef _BD970_NMEA_BASE_TYPES_HPP_
#define _BD970_NMEA_BASE_TYPES_HPP_


/** Std C++ libraries **/
#include <string>

/** Std C Libraries **/
#include <stdint.h>

/** Rock Std types **/
#include <base/Time.hpp>

/** BD970 Driver Types **/
#include <trimble_bd970/Config.hpp>



/**
 * 
 * 
 */
namespace trimble_bd970
{
    /** NMEA messages sent over the serial port are prefixed with '$', which
     * in ASCII is 0x24.
     */
    static const uint8_t NMEA_MESSAGE_PREFIX = 0x24;
    
    
    /**
     * 
     * 
     */
    class NMEA_Base
    {
        public:
            
            int m_message_len;
            int m_field_num;
            
            int checksum;
            
            NMEA_Base(int message_len, int filed_num);
            virtual ~NMEA_Base(void);
            
            virtual int checksumTest (std::string message, int checksum);
            virtual int extractMessage (uint8_t *buffer, int message_len) = 0;
            virtual int printMessage (void) = 0;
            
    };
    
    
    /**
     * 
     * 
     */
    
    /*class NMEA_Messages
    {
        public:
            
            base::Time  m_rx_time;
            base::Time  m_tx_time;
            
            int m_number_messages;
            int *m_message_lengths;
            
            
            // TODO: Dynaimc Messages
            //std::vector<NMEA_Base::mp_message> mp_messages;
            //NMEA_Base *mp_messages;
            
            // Messages (Static)
            NMEA_GGA data_gga;
            //NMEA_GST data_gst;
            NMEA_AVR data_avr;
            NMEA_HDT data_hdt;
            //NMEA_ZDA data_zda;
            
            
            NMEA_Messages(void);
            
            virtual ~NMEA_Messages(void);
            
            
            int checkTag(uint8_t *buffer);
            
            int extractNMEA(uint8_t *buffer);
            
            int printMessages(void);
        
    };*/
}

#endif // _BD970_NMEA_BASE_TYPES_HPP_
