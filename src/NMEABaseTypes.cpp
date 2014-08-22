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
 *    NMEABaseTypes.cpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */


/** NMEA Base Types Header **/
#include <trimble_bd970/NMEABaseTypes.hpp>

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
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace trimble_bd970;
using namespace std;

/**
* 
*/
NMEA_Base::NMEA_Base(int message_len, int field_num)
    : m_message_len(message_len)
    , m_field_num(field_num)
    , checksum(0)
{
}


NMEA_Base::~NMEA_Base(void)
{
}


std::string NMEA_Base::getMessageStr(uint8_t *buffer, int message_len) const
{
    uint8_t *temp = new uint8_t[message_len - 1];
    memcpy(temp, buffer, (message_len - 1));
    temp[message_len - 2] = '\0';
    std::string message((char *)temp);
    delete temp;
    
    return message;
}


int NMEA_Base::checksumTest (std::string& message, 
                             std::string& cur_checksum, 
                             std::string const message_type)
{
    /** get the cheksum as an integer **/
    int hex_checksum;
    std::stringstream str;
    str << cur_checksum;
    str >> std::hex >> hex_checksum;
    
    /** modify string to remove characters not included in sum **/
    int astr_pos = message.find_last_of('*');
    std::string temp = message.substr(1, (astr_pos - 1));
    int substr_size = temp.size();
    
    /** compute the sum as an XOR between all characters **/
    int i, sum = 0;
    for (i = 0; i < substr_size; ++i)
    {
        sum ^= (int)temp[i];
    }
    
    /** DEBUG helper prints **/
    //std::cout << "Checksum is: " << hex_checksum << std::endl;
    //std::cout << "sum: " << sum << std::endl;
    //std::cout << "temp is: " << temp << std::endl;
    
    /** test to see if the values are correct **/
    if (sum != hex_checksum)
    {
        /* data is incorrect */
        std::cout << "NMEA_" << message_type  << ": checksum error" << std::endl;
        return -1;
    }
    else
    {
        checksum = hex_checksum;
    }
    
    
    /* data is correct */
    return 0;
}



/**
*  
*  
*/
/*
NMEA_Messages::NMEA_Messages(void)
    : m_rx_time(base::Time::now())
    , m_tx_time(base::Time::now())
    , m_number_messages(NMEA_MESSAGE_NUM)
    , m_message_lengths(0)
    //, mp_messages(0)
    , data_gga()
    , data_avr()
    , data_hdt()
{
    this->m_message_lengths = new int[NMEA_MESSAGE_NUM];
    
    //shared_ptr<T> static_pointer_cast(shared_ptr<U> const & r);
    
    //this->mp_messages = new ? 
    
}


NMEA_Messages::~NMEA_Messages(void)
{
    // TODO: ADD MESSAGES HERE
    
    delete this->m_message_lengths;
}



int NMEA_Messages::checkTag(uint8_t *buffer)
{
    // TODO
    
    
    return 0;
}


int NMEA_Messages::extractNMEA(uint8_t *buffer)
{
    m_rx_time = base::Time::now();
    
    
    // TODO: setup ZDA + GST
    
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    uint8_t *p_buffer = buffer;
    data_gga.extractMessage(p_buffer, m_message_lengths[0]);
    
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    p_buffer += m_message_lengths[0];
    data_avr.extractMessage(p_buffer, m_message_lengths[1]);
    
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    p_buffer += m_message_lengths[1];
    data_hdt.extractMessage(p_buffer, m_message_lengths[2]);
    
    m_tx_time = base::Time::now();
    
    return 0;
}


int NMEA_Messages::printMessages(void)
{
    for (int i = 0; i < m_number_messages;
    
    // TODO: setup ZDA + GST
    data_gga.printMessage();
    data_avr.printMessage();
    data_hdt.printMessage();
    
    int64_t process_time = m_tx_time.toMicroseconds() - m_rx_time.toMicroseconds();
    
    std::cout << "NMEA processing time (usec) is: " << process_time << std::endl;
    
    return 0;
}
*/


