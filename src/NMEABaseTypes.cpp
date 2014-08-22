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


/** NMEA Types Header **/
#include <trimble_bd970/NMEABaseTypes.hpp>

using namespace trimble_bd970;

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


