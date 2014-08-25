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
#include <trimble_bd970/GNSSTypes.hpp>

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
    : NMEA_Base(-1, NMEA_GGA::NUMBER_OF_FIELD)
    , utc(base::NaN<double>())
    , latitude(base::NaN<double>())
    , lat_dir("~")
    , longitude(base::NaN<double>())
    , long_dir("~")
    , gps_quality(-1)
    , num_sat_vehicles(base::NaN<double>())
    , hdop(base::NaN<double>())
    , orthom_height(base::NaN<double>())
    , geoid_separation(base::NaN<double>())
    , dgps_age(base::NaN<double>())
    , ref_station_id(-1)
{
}

NMEA_GGA::~NMEA_GGA(void)
{
}

int NMEA_GGA::extractMessage(uint8_t *buffer, int message_len)
{
    /** prepare the std::string type for processing **/
    std::string input =  getMessageStr(buffer, message_len);

    /** split the message into fields **/
    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    /** checksum test **/
    int test = checksumTest (input, SplitVec[SplitVec.size()-1], "GGA");
    if (test != 0)
    {
        return 1;
    }

    /** message data extraction **/
   for(unsigned int i = 0; i < SplitVec.size(); ++i)
    {
        if(i == 0)
        {
            if(SplitVec[i].compare("$GPGGA") != 0)
            {
                std::runtime_error("NMEA_GGA: packet given is not GPGGA.");
                return -1;
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
            longitude = strtod(SplitVec[i].c_str(), 0);
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
    }

    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return 0;
}

int NMEA_GGA::printMessage(void)
{
    std::cout << "GGA Message values: " << std::endl;
    std::cout << std::endl;

    std::cout << "UTC: " << utc << std::endl;
    std::cout << "LATITUDE: " << latitude << std::endl;
    std::cout << "LATDIR: " << lat_dir << std::endl;
    std::cout << "LONGITUDE: " << longitude << std::endl;
    std::cout << "LONGDIR: " << long_dir << std::endl;
    std::cout << "GPS_QUAL: " << gps_quality << std::endl;
    std::cout << "SATs: " << num_sat_vehicles << std::endl;
    std::cout << "HDOP: " << hdop << std::endl;
    std::cout << "OH: " << orthom_height << std::endl;
    std::cout << "GS: " << geoid_separation << std::endl;
    std::cout << "DGPS AGE: " << dgps_age << std::endl;
    std::cout << "REFST: " << ref_station_id << std::endl;
    printf("CHKSM: %X\n", checksum);
    std::cout << std::endl;

    return 0;
}


/**
* 
*/
NMEA_AVR::NMEA_AVR(void)
    : NMEA_Base(-1,NMEA_AVR::NUMBER_OF_FIELD)
    , utc(base::NaN<double>())
    , yaw(base::NaN<double>())
    , tilt(base::NaN<double>())
    , range(base::NaN<double>())
    , gps_quality(-1)
    , pdop(base::NaN<double>())
    , num_sat_vehicles(-1)
{
}

NMEA_AVR::~NMEA_AVR(void)
{
}

int NMEA_AVR::extractMessage(uint8_t *buffer, int message_len)
{
    /** prepare the std::string type for processing **/
    std::string input =  getMessageStr(buffer, message_len);

    /** split the message into fields **/
    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    /** checksum test **/
    int test = checksumTest (input, SplitVec[SplitVec.size()-1], "AVR");
    if (test != 0)
    {
        return 1;
    }

    /** message data extraction **/
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

        if (i == 11)
        {
            pdop = strtod(SplitVec[i].c_str(), 0);
        }
        if (i == 12)
        {
            num_sat_vehicles = atoi(SplitVec[i].c_str());
        }

    }

    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return 0;
}

int NMEA_AVR::printMessage(void)
{
    std::cout << "AVR Message values: " << std::endl;
    std::cout << std::endl;

    std::cout << "UTC: " << utc << std::endl;
    std::cout << "YAW: " << yaw << std::endl;
    std::cout << "TILT: " << tilt << std::endl;
    std::cout << "RANGE: " << range << std::endl;
    std::cout << "GPS_QUAL: " << gps_quality << std::endl;
    std::cout << "PDOP: " << pdop << std::endl;
    std::cout << "SATs: " << num_sat_vehicles << std::endl;
    printf("CHKSM: %X\n", checksum);
    std::cout << std::endl;

    return 0;
}


/**
* 
*/
NMEA_HDT::NMEA_HDT(void)
    : NMEA_Base(-1, NMEA_HDT::NUMBER_OF_FIELD)
    , heading(base::NaN<double>())
    , heading_dir("~")
{
}

NMEA_HDT::~NMEA_HDT(void)
{
}

int NMEA_HDT::extractMessage(uint8_t *buffer, int message_len)
{
    /** prepare the std::string type for processing **/
    std::string input =  getMessageStr(buffer, message_len);

    /** split the message into fields **/
    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    std::cout<<"SplitVec.size(): "<<SplitVec.size()<<"\n";
    std::cout<<"SplitVec contains "<<SplitVec[SplitVec.size()-1]<<"\n";
    /** checksum test **/
    int test = checksumTest (input, SplitVec[SplitVec.size()-1], "HDT");
    if (test != 0)
    {
        return 1;
    }

    /** message data extraction **/
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
    }

    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    return 0;
}

int NMEA_HDT::printMessage(void)
{
    std::cout << "HDT Message values: " << std::endl;
    std::cout << std::endl;

    std::cout << "HEADING: " << heading << std::endl;
    std::cout << "HDIR: " << heading_dir << std::endl;
    printf("CHKSM: %X\n", checksum);
    std::cout << std::endl;

    return 0;
}


/**
* NMEA_GST
*/
NMEA_GST::NMEA_GST(void)
    : NMEA_Base(-1, NMEA_GST::NUMBER_OF_FIELD)
    , utc(base::NaN<double>())
    , rms(base::NaN<double>())
    , semi_major_axis_sigma_error(base::NaN<double>())
    , semi_minor_axis_sigma_error(base::NaN<double>())
    , heading_sigma_error(base::NaN<double>())
    , latitude_sigma_error(base::NaN<double>())
    , longitude_sigma_error(base::NaN<double>())
    , height_sigma_error(base::NaN<double>())
{
}

NMEA_GST::~NMEA_GST(void)
{
}

int NMEA_GST::extractMessage(uint8_t *buffer, int message_len)
{

    /** prepare the std::string type for processing **/
    std::string input =  getMessageStr(buffer, message_len);

    /** split the message into fields **/
    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    /** checksum test **/
    int test = checksumTest (input, SplitVec[SplitVec.size()-1], "GST");
    if (test != 0)
    {
        return 1;
    }

    /** message data extraction **/
    for(unsigned int i = 0; i < SplitVec.size(); ++i)
    {
        if(i == 0)
        {
            if(SplitVec[i].compare("$GNGST") != 0)
            {
                std::runtime_error("NMEA_GST: packet given is not GNGST.");
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
    std::cout << "GST Message values: " << std::endl;
    std::cout << std::endl;

    std::cout << "UTC: " << utc << std::endl;
    std::cout << "RMS: " << rms << std::endl;
    std::cout << "ELLIPSOID MAJOR AXIS (1-SIGMA): " << semi_major_axis_sigma_error << std::endl;
    std::cout << "ELLIPSOID MINOR AXIS (1-SIGMA): " << semi_minor_axis_sigma_error << std::endl;
    std::cout << "HEADING ERROR FROM TRUE NORTH (1-SIGMA): " << heading_sigma_error << std::endl;
    std::cout << "LATITUDE ERROR (1-SIGMA): " << latitude_sigma_error << std::endl;
    std::cout << "LONGITUDE ERROR (1-SIGMA): " << longitude_sigma_error << std::endl;
    std::cout << "HEIGHT ERROR (1-SIGMA): " << height_sigma_error << std::endl;
    printf("CHKSM: %X\n", checksum);
    std::cout << std::endl;

    return 0;
}


/**
* NMEA_ZDA
*/
NMEA_ZDA::NMEA_ZDA(void)
    : NMEA_Base(-1, NMEA_ZDA::NUMBER_OF_FIELD)
    , utc(base::NaN<double>())
    , day(-1)
    , month(-1)
    , year(-1)
    , gmt_hours_offset(-1)
    , gmt_minutes_offset(-1)
{
}

NMEA_ZDA::~NMEA_ZDA(void)
{
}

int NMEA_ZDA::extractMessage(uint8_t *buffer, int message_len)
{

    /** prepare the std::string type for processing **/
    std::string input =  getMessageStr(buffer, message_len);

    /** split the message into fields **/
    split_vector_type SplitVec;
    split( SplitVec, input, is_any_of(",*") );

    /** checksum test **/
    int test = checksumTest (input, SplitVec[SplitVec.size()-1], "ZDA");
    if (test != 0)
    {
        return 1;
    }

    /** message data extraction **/
    for(unsigned int i = 0; i < SplitVec.size(); ++i)
    {
        if(i == 0)
        {
            if(SplitVec[i].compare("$GPZDA") != 0)
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
    std::cout << "ZDA Message values: " << std::endl;
    std::cout << std::endl;

    std::cout << "UTC: " << utc << std::endl;
    std::cout << "DAY " << day <<" MONTH "<< month <<" YEAR "<< year << std::endl;
    std::cout << "GTM HOURS: " << gmt_hours_offset <<" MINUTES "<<gmt_minutes_offset  << std::endl;
    printf("CHKSM: %X\n", checksum);
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

    /** GGA **/
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    uint8_t *p_buffer = buffer;
    int ret = data_gga.extractMessage(p_buffer, m_message_lengths[0]);

    /** GST **/
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    p_buffer += m_message_lengths[0];
    ret = data_gst.extractMessage(p_buffer, m_message_lengths[1]);

    /** AVR **/
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    p_buffer += m_message_lengths[1];
    ret = data_avr.extractMessage(p_buffer, m_message_lengths[2]);

    /** ZDA **/
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    p_buffer += m_message_lengths[2];
    ret = data_zda.extractMessage(p_buffer, m_message_lengths[3]);

    /** HDT **/
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    p_buffer += m_message_lengths[3];
    ret = data_hdt.extractMessage(p_buffer, m_message_lengths[4]);

    m_tx_time = base::Time::now();

    return ret;
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
