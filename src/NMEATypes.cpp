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
 *    NMEATypes.cpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */

/** NMEA Types Header **/
#include <trimble_bd970/NMEATypes.hpp>

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



using namespace std;
using namespace boost;
using namespace trimble_bd970;



/**
* 
*/
typedef vector< string > split_vector_type;



/**
* 
*/
NMEA_GGA::NMEA_GGA(void)
    : NMEA_Base(-1, 15)
    , utc(-1)
    , latitude(0)
    , lat_dir("~")
    , longtitude(0)
    , long_dir("~")
    , gps_quality(-1)
    , num_sat_vehicles(0)
    , hdop(0)
    , orthom_height(0)
    , geoid_separation(0)
    , dgps_age(-1)
    , ref_station_id(-1)
{
}

NMEA_GGA::~NMEA_GGA(void)
{
}

int NMEA_GGA::extractMessage(uint8_t *buffer, int message_len)
{
    uint8_t *temp = new uint8_t[message_len - 1];
    memcpy(temp, buffer, (message_len - 1));
    temp[message_len - 2] = '\0';
    std::string input((char *)temp);
    delete temp;

    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    for(unsigned int i = 0; i < SplitVec.size(); ++i)
    {
        if(i == 0)
        {
            if(SplitVec[i].compare("$GPGGA") != 0)
            {
                std::runtime_error("NMEA_GGA: packet given is not GPGGA.");
            }
        }

        if(i == 1)
        {
            utc = strtod(SplitVec[i].c_str(), 0);
        }

        if(i == 2)
        {
            latitude = strtod(SplitVec[i].c_str(), 0);
        }

        if(i == 3)
        {
            lat_dir = SplitVec[i];
        }

        if(i == 4)
        {
            longtitude = strtod(SplitVec[i].c_str(), 0);
        }

        if(i == 5)
        {
            long_dir = SplitVec[i];
        }

        if(i == 6)
        {
            gps_quality = atoi(SplitVec[i].c_str());
        }

        if(i == 7)
        {
            num_sat_vehicles = atoi(SplitVec[i].c_str());
        }

        if(i == 8)
        {
            hdop = strtod(SplitVec[i].c_str(), 0);
        }

        if(i == 9)
        {
            orthom_height = strtod(SplitVec[i].c_str(), 0);
        }

        if(i == 11)
        {
            geoid_separation = strtod(SplitVec[i].c_str(), 0);
        }

        if(i == 13)
        {
            dgps_age = strtod(SplitVec[i].c_str(), 0);
        }

        if(i == 14)
        {
            ref_station_id = atoi(SplitVec[i].c_str());
        }

        if(i == 15)
        {
            std::stringstream str;
            str << SplitVec[i];
            str >> std::hex >> checksum;
        }
    }

    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return 0;
}

int NMEA_GGA::printMessage(void)
{
    std::cout << "These are the found values: " << std::endl;
    std::cout << std::endl;
    
    std::cout << "UTC: " << utc << std::endl;
    std::cout << "LAT: " << latitude << std::endl;
    std::cout << "LATDIR: " << lat_dir << std::endl;
    std::cout << "LONG: " << longtitude << std::endl;
    std::cout << "LONGDIR: " << long_dir << std::endl;
    std::cout << "GPS_QUAL: " << gps_quality << std::endl;
    std::cout << "SATs: " << num_sat_vehicles << std::endl;
    std::cout << "HDOP: " << hdop << std::endl;
    std::cout << "OH: " << orthom_height << std::endl;
    std::cout << "GS: " << geoid_separation << std::endl;
    std::cout << "DGPS AGE: " << dgps_age << std::endl;
    std::cout << "REFST: " << ref_station_id << std::endl;
    std::cout << "CHKSM: " << checksum << std::endl;
    std::cout << std::endl;
    
    return 0;
}


/**
* 
*/
NMEA_AVR::NMEA_AVR(void)
    : NMEA_Base(-1, 12)
    , utc(0)
    , yaw(0)
    , tilt(0)
    , range(0)
    , gps_quality(0)
    , pdop(0)
    , num_sat_vehicles(0)
{
}

NMEA_AVR::~NMEA_AVR(void)
{
}

int NMEA_AVR::extractMessage(uint8_t *buffer, int message_len)
{
    uint8_t *temp = new uint8_t[message_len - 1];
    memcpy(temp, buffer, (message_len - 1));
    temp[message_len - 2] = '\0';
    std::string input((char *)temp);
    delete temp;

    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    for(unsigned int i = 0; i < SplitVec.size(); ++i)
    {
        if(i == 1)
        {
            if(SplitVec[i].compare("AVR") != 0)
            {
                std::runtime_error("NMEA_AVR: packet given is not AVR.");
            }
        }

        if (i == 2)
        {
            utc = strtod(SplitVec[i].c_str(), 0);
        }

        if (i == 3)
        {
            yaw = strtod(SplitVec[i].c_str(), 0);
        }

        if (i == 5)
        {
            tilt = strtod(SplitVec[i].c_str(), 0);
        }

        if (i == 9)
        {
            range = strtod(SplitVec[i].c_str(), 0);
        }

        if (i == 10)
        {
            gps_quality = atoi(SplitVec[i].c_str());
        }

        if (i == 12)
        {
            pdop = strtod(SplitVec[i].c_str(), 0);
        }

        if(i == 13)
        {
            std::stringstream str;
            str << SplitVec[i];
            str >> std::hex >> checksum;
        }
    }

    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return 0;
}

int NMEA_AVR::printMessage(void)
{
    std::cout << "These are the AVR values: " << std::endl;
    std::cout << std::endl;

    std::cout << "UTC: " << utc << std::endl;
    std::cout << "YAW: " << yaw << std::endl;
    std::cout << "TILT: " << tilt << std::endl;
    std::cout << "RANGE: " << range << std::endl;
    std::cout << "GPS_QUAL: " << gps_quality << std::endl;
    std::cout << "PDOP: " << pdop << std::endl;
    std::cout << "SATs: " << num_sat_vehicles << std::endl;
    std::cout << "CHKSM: " << checksum << std::endl;
    std::cout << std::endl;

    return 0;
}


/**
* 
*/
NMEA_HDT::NMEA_HDT(void)
    : NMEA_Base(-1, 3)
    , heading(0)
    , heading_dir("~")
{
}

NMEA_HDT::~NMEA_HDT(void)
{
}

int NMEA_HDT::extractMessage(uint8_t *buffer, int message_len)
{
    uint8_t *temp = new uint8_t[message_len - 1];
    memcpy(temp, buffer, (message_len - 1));
    temp[message_len - 2] = '\0';
    std::string input((char *)temp);
    delete temp;

    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    for(unsigned int i = 0; i < SplitVec.size(); ++i)
    {
        if(i == 0)
        {
            if(SplitVec[i].compare("$GPHDT") != 0)
            {
                std::runtime_error("NMEA_HDT: packet given is not GPHDT.");
            }
        }

        if (i == 1)
        {
            heading = strtod(SplitVec[i].c_str(), 0);
        }

        if (i == 2)
        {
             heading_dir = SplitVec[i];
        }

        if(i == 3)
        {
            std::stringstream str;
            str << SplitVec[i];
            str >> std::hex >> checksum;
        }
    }

    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return 0;
}

int NMEA_HDT::printMessage(void)
{
    std::cout << "These are the HDT values: " << std::endl;
    std::cout << std::endl;

    std::cout << "HEADING: " << heading << std::endl;
    std::cout << "HDIR: " << heading_dir << std::endl;
    std::cout << "CHKSM: " << checksum << std::endl;
    std::cout << std::endl;

    return 0;
}


/**
* NMEA_GST
*/
NMEA_GST::NMEA_GST(void)
    : NMEA_Base(-1, 3)
    , utc(0)
    , rms(0)
    , semi_major_axis_sigma_error(0)
    , semi_minor_axis_sigma_error(0)
    , heading_sigma_error(0)
    , latitude_sigma_error(0)
    , longitude_sigma_error(0)
    , height_sigma_error(0)
{
}

NMEA_GST::~NMEA_GST(void)
{
}

int NMEA_GST::extractMessage(uint8_t *buffer, int message_len)
{
    uint8_t *temp = new uint8_t[message_len - 1];
    memcpy(temp, buffer, (message_len - 1));
    temp[message_len - 2] = '\0';
    std::string input((char *)temp);
    delete temp;

    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    for(unsigned int i = 0; i < SplitVec.size(); ++i)
    {
        if(i == 0)
        {
            if(SplitVec[i].compare("$GPGST") != 0)
            {
                std::runtime_error("NMEA_GST: packet given is not GPGST.");
            }
        }

        else if (i == 1)
        {
            utc = strtod(SplitVec[i].c_str(), 0);
        }

        else if (i == 2)
        {
            rms = strtod(SplitVec[i].c_str(), 0);
        }

        else if (i == 3)
        {
            semi_major_axis_sigma_error = strtod(SplitVec[i].c_str(), 0);
        }

        else if (i == 4)
        {
            semi_minor_axis_sigma_error = strtod(SplitVec[i].c_str(), 0);
        }

        else if (i == 5)
        {
            heading_sigma_error = strtod(SplitVec[i].c_str(), 0);
        }

        else if (i == 6)
        {
            latitude_sigma_error = strtod(SplitVec[i].c_str(), 0);
        }

        else if (i == 7)
        {
            longitude_sigma_error = strtod(SplitVec[i].c_str(), 0);
        }

        else if (i == 8)
        {
            height_sigma_error = strtod(SplitVec[i].c_str(), 0);
        }

        else if(i == 9)
        {
            std::stringstream str;
            str << SplitVec[i];
            str >> std::hex >> checksum;
        }
    }

    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return 0;
}


int NMEA_GST::printMessage(void)
{
    std::cout << "These are the found values: " << std::endl;
    std::cout << std::endl;

    std::cout << "UTC: " << utc << std::endl;
    std::cout << "RMS: " << rms << std::endl;
    std::cout << "ELLIPSOID MAJOR AXIS (1-SIGMA): " << semi_major_axis_sigma_error << std::endl;
    std::cout << "ELLIPSOID MINOR AXIS (1-SIGMA): " << semi_minor_axis_sigma_error << std::endl;
    std::cout << "HEADING ERROR FROM TRUE NORTH (1-SIGMA): " << heading_sigma_error << std::endl;
    std::cout << "LATITUDE ERROR (1-SIGMA): " << latitude_sigma_error << std::endl;
    std::cout << "LONGITUDE ERROR (1-SIGMA): " << longitude_sigma_error << std::endl;
    std::cout << "HEIGHT ERROR (1-SIGMA): " << height_sigma_error << std::endl;
    std::cout << "CHKSM: " << checksum << std::endl;
    std::cout << std::endl;

    return 0;
}


/**
* NMEA_ZDA
*/
NMEA_ZDA::NMEA_ZDA(void)
    : NMEA_Base(-1, 3)
    , utc(0)
    , day(0)
    , month(0)
    , year(0)
    , gmt_hours_offset(0)
    , gmt_minutes_offset(0)
{
}

NMEA_ZDA::~NMEA_ZDA(void)
{
}

int NMEA_ZDA::extractMessage(uint8_t *buffer, int message_len)
{
    uint8_t *temp = new uint8_t[message_len - 1];
    memcpy(temp, buffer, (message_len - 1));
    temp[message_len - 2] = '\0';
    std::string input((char *)temp);
    delete temp;

    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    for(unsigned int i = 0; i < SplitVec.size(); ++i)
    {
        if(i == 0)
        {
            if(SplitVec[i].compare("$GPGST") != 0)
            {
                std::runtime_error("NMEA_ZDA: packet given is not GPZDA.");
            }
        }
        else if (i == 1)
        {
            utc = strtod(SplitVec[i].c_str(), 0);
        }
        else if (i == 2)
        {
            day = atoi(SplitVec[i].c_str());
        }
        else if (i == 3)
        {
            month = atoi(SplitVec[i].c_str());
        }
        else if (i == 4)
        {
            year = atoi(SplitVec[i].c_str());
        }
        else if (i == 5)
        {
            gmt_hours_offset = atoi(SplitVec[i].c_str());
        }
        else if (i == 6)
        {
            gmt_minutes_offset = atoi(SplitVec[i].c_str());
        }
        else if (i == 7)
        {
            std::stringstream str;
            str << SplitVec[i];
            str >> std::hex >> checksum;

        }
    }

    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return 0;
}


int NMEA_ZDA::printMessage(void)
{
    std::cout << "These are the found values: " << std::endl;
    std::cout << std::endl;

    std::cout << "UTC: " << utc << std::endl;
    std::cout << "DAY " << day <<" MONTH "<< month <<" YEAR "<< year << std::endl;
    std::cout << "GTM HOURS: " << gmt_hours_offset <<" MINUTES "<<gmt_minutes_offset  << std::endl;
    std::cout << "CHKSM: " << checksum << std::endl;
    std::cout << std::endl;

    return 0;
}


/* TODO: Put these in NMEABaseTypes.hpp when message generalization
 *       for dynamic message generation will be implemented.
 * 
 */
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
    //for (int i = 0; i < m_number_messages);

    data_gga.printMessage();
    data_gst.printMessage();
    data_avr.printMessage();
    data_zda.printMessage();
    data_hdt.printMessage();

    int64_t process_time = m_tx_time.toMicroseconds() - m_rx_time.toMicroseconds();

    std::cout << "NMEA processing time (usec) is: " << process_time << std::endl;

    return 0;
}
