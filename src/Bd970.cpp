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
 *    Bd970.cpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */



/** DB970 Library header **/
#include <trimble_bd970/Bd970.hpp>

/** Std C Libraries **/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/** Std C++ Libraries **/
#include <iostream>
#include <string>
#include <iostream>
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


/**
 * 
 */
using namespace std;
using namespace boost;
using namespace trimble_bd970;


/**
 * 
 */
Bd970::Bd970 (int max_packet_size, float sampling_frequency)
    : bd970Config()
    , m_current_nmea()
    , NmeaRxPort(max_packet_size, sampling_frequency)
    //, m_current_rtk()
    //, RtkTxPort(max_packet_size, sampling_frequency)
{
    std::cout << "Creating and initializing driver object" << std::endl;

    if(max_packet_size <= 0)
    {
        std::runtime_error("BD970 Driver: max_packet_size cannot be smaller or equal to 0!");
    }
}

Bd970::~Bd970 ()
{
    std::cout << "Destructing object" << std::endl;
}


/**
 * 
 */

void Bd970::Greeting (void)
{
        std::cout << "Trimble BD970 GNSS Receiver is online." << std::endl;
}



/**
 * 
 */

/**
 * 
 */
int Bd970::setupNMEA (std::string const& filename, int baudrate)
{
    Greeting();
    NmeaRxPort.Greeting();
    
    NmeaRxPort.setBaudRate(baudrate);
    
    if (!NmeaRxPort.openPort(filename))
    {
        cerr << "setupNMEA: Cannot open device: " << filename << endl;
        perror("errno is: ");
        return -1;
    }
    
    return 0;
}

int Bd970::processNMEA (void)
{

    int i = 0;
    int packet_size = 0;

    uint8_t data_tag[16] = {0};
    int start_tag_found = 0;

    int num_msg = m_current_nmea.m_number_messages;
    int *nmea_len = m_current_nmea.m_message_lengths;

    uint8_t *p_buffer;
    p_buffer = NmeaRxPort.m_buffer;


    /** Find the correct packet bundle and place it in the ports outer buffer.
     * 
     */
    printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    std::cout<<"Num messages: "<< num_msg <<"\n";

    for (i = 0; i < num_msg; ++i)
    {
        //printf("@%s, LINE: %d\n", __FILE__, __LINE__);

        try 
        {
            if (start_tag_found == 0)
            {
                //printf("@%s, LINE: %d\n", __FILE__, __LINE__);

                while (strcmp((const char *)data_tag, "$GPGGA") != 0)
                {
                    packet_size = NmeaRxPort.readPacket (p_buffer, NmeaRxPort.MAX_BUFFER_SIZE, NmeaRxPort.m_timeout);
                    memcpy(data_tag, p_buffer, 6);

                    //printf("@%s, packet_size = %d\n", __FILE__, packet_size);
                }

                nmea_len[0] = packet_size;

                start_tag_found = 1;
            }
            else
            {
                //printf("@%s, LINE: %d\n", __FILE__, __LINE__);

                packet_size = NmeaRxPort.readPacket (p_buffer, NmeaRxPort.MAX_BUFFER_SIZE, NmeaRxPort.m_timeout);

                nmea_len[i] = packet_size;
                //printf("@%s, packet_size = %d\n", __FILE__, packet_size);
            }
        }
        catch (iodrivers_base::TimeoutError& e )
        {
            std::cerr << "TimeoutError buffer size: " << packet_size << "\n";
            return -1;
        }

        p_buffer += packet_size;
    }

    /** Reset the pointer to the beginning of the buffer **/
    p_buffer = NmeaRxPort.m_buffer;


    /** Extract the packet bundle into the corresponding NMEA types wrappers */
    m_current_nmea.extractNMEA(p_buffer);

    return 0;
}

int Bd970::printNMEA (void)
{
    std::cout << "The current NMEA messages are: " << std::endl;
    m_current_nmea.printMessages();

    return 0;
}

trimble_bd970::Time Bd970::getTime(void)
{
    trimble_bd970::Time current_time;

    /** Parse the NMEA UTC time into base Time **/
    double fractpart, intpart;
    fractpart = modf(m_current_nmea.data_zda.utc, &intpart);

    /** Integer forms **/
    std::vector<int> utc_int_parts;
    int int_hh_mm_ss = static_cast<int>(intpart);
    int int_millis = static_cast<int>(fractpart * 1000.00);

    /** Split digits (hours, minutes, and seconds) **/
    utc_int_parts.insert(utc_int_parts.begin(), int_hh_mm_ss % 100); //seconds
    int_hh_mm_ss = int_hh_mm_ss / 100;

    utc_int_parts.insert(utc_int_parts.begin(), int_hh_mm_ss % 100); //minutes
    int_hh_mm_ss = int_hh_mm_ss / 100;

    utc_int_parts.insert(utc_int_parts.begin(), int_hh_mm_ss % 100); //hours
    int_hh_mm_ss = int_hh_mm_ss / 100;

    base::Time utc_time;
    utc_time.fromTimeValues(m_current_nmea.data_zda.year, m_current_nmea.data_zda.month,
                            m_current_nmea.data_zda.day, utc_int_parts[0], utc_int_parts[1],
                            utc_int_parts[2], int_millis, 0);

    /** Store the times **/
    current_time.gnss_time = utc_time;
    current_time.cpu_time = base::Time::now();
    current_time.processing_latency = m_current_nmea.process_time;

    return current_time;
}

int Bd970::printBufferNMEA (void)
{
    NmeaRxPort.printBuffer();

    return 0;
}

int Bd970::closeNMEA (void)
{
    NmeaRxPort.close();

    return 0;
}


