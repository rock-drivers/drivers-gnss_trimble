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
 *    SerialPort.cpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */


/** DB970 Library header **/
#include <trimble_bd970/SerialPort.hpp>

/** Std C Libraries **/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/** Std C++ Libraries **/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

/** Boost C++ Libraries **/
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

/** POSIX & GNU/Linux Libraries **/
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <termio.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/** Rock library **/
#include <iodrivers_base/Driver.hpp>



/**
 * 
 */
using namespace std;
using namespace boost;
using namespace trimble_bd970;



/**
 * 
 */
 
SerialPort::SerialPort(int max_packet_size, float sampling_frequency)
    : Driver(max_packet_size)
    , SAMPLING_FREQUENCY(sampling_frequency)
    , MAX_BUFFER_SIZE(max_packet_size)
    , m_buffer(new uint8_t[max_packet_size])
    , m_timeout(base::Time::fromSeconds(1.0/sampling_frequency))
{
    m_baudrate = iodrivers_base::Driver::SERIAL_38400;
    
    //m_timeout = base::Time::fromSeconds(1.0/SAMPLING_FREQUENCY);

    if(MAX_BUFFER_SIZE <= 0)
    {
        std::runtime_error("SerialPort: max_packet_size cannot be smaller or equal to 0!");
    }

}


SerialPort::~SerialPort()
{
    delete m_buffer;
}



/**
 * 
 */

void SerialPort::Greeting(void)
{
        std::cout << "Serial device driver is online." << std::endl;
}


bool SerialPort::setBaudRate(int brate)
{
    this->m_baudrate = brate;

    return true;
}


bool SerialPort::openPort(const std::string& filename)
{
    return Driver::openSerial(filename, this->m_baudrate);
}


int SerialPort::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    
    size_t i = 0;
    
    if (buffer[0] == '$')
    {
        //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
        
        for (i = 1; i < buffer_size; ++i)
        {
            if ( buffer[i] == '\n')
            {
                //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
                
                // Minimal message is $*FF\r\n
                if (i < 5)
                {
                    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
                    return -(i + 1);
                }
                else if (buffer[i - 4] != '*')
                {
                    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
                    return -(i + 1);
                }
 
                //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
                return i + 1;
            }
            else if (buffer[i] == '$')
            {
                //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
                return -i;
            }
        }
        
        //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
        return 0;
    }
 
    for (i = 1; i < buffer_size; ++i)
    {
        if ( buffer[i] == '$') return -i;
    }
    
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return -buffer_size;
    
}


int SerialPort::printBuffer (void)
{
    unsigned int i;
    
    std::cout<<"BEGIN BUFFER:\n\n";
    
    for (i=0; i < (unsigned int)MAX_BUFFER_SIZE; i++)
    {
        if (m_buffer[i] == '\0')
        {
            break;
        }
        else
        {
            fprintf (stdout, "%c", m_buffer[i]);
        }
    }
    
    std::cout<<"\nEND BUFFER.\n\n\n";
    
    return 0;
}


int SerialPort::closePort (void)
{
    if (isValid())
    close();
    
    return 0;
}


/**
 *
 */
