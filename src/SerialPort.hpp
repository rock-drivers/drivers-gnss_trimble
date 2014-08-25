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
 *    SerialPort.hpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */


#ifndef _BD970_SERIAL_PORT_HPP_
#define _BD970_SERIAL_PORT_HPP_


/** Std C++ libraries **/
#include <string>

/** Std C Libraries **/
#include <stdint.h>
#include <termios.h>

/** Rock Std types **/
#include <base/Time.hpp>
#include <iodrivers_base/Driver.hpp>

/** BD970 Driver Types **/
#include <gnss_trimble/Config.hpp>
#include <gnss_trimble/NMEATypes.hpp>



/**
 * 
 */
namespace gnss_trimble
{
    
    
    /**
     * 
     */
    class SerialPort: public iodrivers_base::Driver
    {
        private:
            
            float const SAMPLING_FREQUENCY; 
            
            
        protected:
            
            int m_baudrate;
            
            
        public:
            
            int const MAX_BUFFER_SIZE;
        
            uint8_t *m_buffer;
            
            base::Time m_timeout;
            
            
            SerialPort(int max_packet_size, float sampling_frequency);
            
            ~SerialPort(void);
            
            
            void Greeting(void);
            
            bool setBaudRate(int brate);
            
            bool openPort(std::string const& filename);
            
            int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
            
            int printBuffer (void);
            
            int closePort (void);
    };
    
    
} // end namespace bd970

#endif // _BD970_SERIAL_PORT_HPP_
