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
#include <gnss_trimble/Bd970.hpp>

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

#ifndef D2R
#define D2R M_PI/180.00 /** Convert degree to radian **/
#endif
#ifndef R2D
#define R2D 180.00/M_PI /** Convert radian to degree **/
#endif


/**
 * 
 */
using namespace std;
using namespace boost;
using namespace gnss_trimble;


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
    //printf("@%s, LINE: %d\n", __FILE__, __LINE__);
    //std::cout<<"Num messages: "<< num_msg <<"\n";

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
            std::cerr << "GNSS: TimeoutError buffer size: " << packet_size << "\n";
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

gnss_trimble::Time Bd970::getTime(void)
{
    gnss_trimble::Time current_time;

    /** Parse the NMEA UTC time into base Time **/
    double fractpart, intpart;
    fractpart = modf(m_current_nmea.data_zda.utc, &intpart);

    //std::cout<<"intpart: " << intpart <<" fractpart: "<< fractpart <<"\n";

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

    /*std::cout<<"TIME FROM VALUES: YEAR "<<m_current_nmea.data_zda.year<<" MONTH "<< m_current_nmea.data_zda.month <<
                " DAY " << m_current_nmea.data_zda.day << " HOUR " <<utc_int_parts[0] << " MINUTES "<< utc_int_parts[1] <<
                " SECONDS " << utc_int_parts[2] << " MILLIS "<< int_millis << "\n";*/

    base::Time utc_time = base::Time::fromTimeValues(m_current_nmea.data_zda.year, m_current_nmea.data_zda.month,
                            m_current_nmea.data_zda.day, utc_int_parts[0], utc_int_parts[1],
                            utc_int_parts[2], int_millis, 0);

    /** Store the times **/
    current_time.gnss_time = utc_time;
    current_time.cpu_time = base::Time::now();
    current_time.processing_latency = m_current_nmea.process_time;

    return current_time;
}


gnss_trimble::Solution Bd970::getSolution(void)
{
    gnss_trimble::Solution gnss_solution;


    gnss_solution.time = base::Time::now();
    gnss_solution.latitude = interpretAngle(m_current_nmea.data_gga.latitude, m_current_nmea.data_gga.lat_dir == "N");
    gnss_solution.longitude = interpretAngle(m_current_nmea.data_gga.longitude, m_current_nmea.data_gga.long_dir == "E");
    switch (m_current_nmea.data_gga.gps_quality)
    {
        case 0: gnss_solution.positionType = NO_SOLUTION; break;
        case 1: gnss_solution.positionType = AUTONOMOUS; break;
        case 2: gnss_solution.positionType = DIFFERENTIAL; break;
        case 4: gnss_solution.positionType = RTK_FIXED; break;
        case 5: gnss_solution.positionType = RTK_FLOAT; break;
        default: gnss_solution.positionType = INVALID; break;
    }
    gnss_solution.noOfSatellites = m_current_nmea.data_gga.num_sat_vehicles;
    gnss_solution.altitude =  m_current_nmea.data_gga.orthom_height;
    gnss_solution.geoidalSeparation = m_current_nmea.data_gga.geoid_separation;
    gnss_solution.ageOfDifferentialCorrections = m_current_nmea.data_gga.dgps_age;

    gnss_solution.deviationLatitude = m_current_nmea.data_gst.latitude_sigma_error;
    gnss_solution.deviationLongitude = m_current_nmea.data_gst.longitude_sigma_error;
    gnss_solution.deviationAltitude = m_current_nmea.data_gst.height_sigma_error;

    return gnss_solution;
}


Eigen::Matrix3d Bd970::getPositionUncertainty(void)
{
    Eigen::Matrix3d position_uncertainty;

    Eigen::Vector3d eigenvalues; // eigen values are the square of the std deviation
    eigenvalues << m_current_nmea.data_gst.semi_major_axis_sigma_error *
                m_current_nmea.data_gst.semi_major_axis_sigma_error,
                m_current_nmea.data_gst.semi_minor_axis_sigma_error *
                m_current_nmea.data_gst.semi_minor_axis_sigma_error,
                m_current_nmea.data_gst.height_sigma_error *
                m_current_nmea.data_gst.height_sigma_error;

    Eigen::Matrix3d U = this->getOrientation().matrix();
    position_uncertainty = U * eigenvalues.array().matrix().asDiagonal() * U.transpose();

    return position_uncertainty;
}

Eigen::Quaternion<double> Bd970::getOrientation(void)
{
    Eigen::Quaternion<double> orientation;

    /** Get the yaw with respect to the north **/
    orientation = Eigen::Quaternion <double>(
        Eigen::AngleAxisd(m_current_nmea.data_hdt.heading * D2R, Eigen::Vector3d::UnitZ())*
        Eigen::AngleAxisd(0.00, Eigen::Vector3d::UnitY()) *
        Eigen::AngleAxisd(0.00, Eigen::Vector3d::UnitX()));

    return orientation;
}

Eigen::Matrix3d Bd970::getOrientationUncertainty(void)
{
    Eigen::Matrix3d orientation_uncertainty;

    /** Get the yaw with respect to the north **/
    Eigen::Vector3d variance;
    variance << 0.00, 0.00, (m_current_nmea.data_gst.heading_sigma_error*m_current_nmea.data_gst.heading_sigma_error);
    orientation_uncertainty = variance.array().matrix().asDiagonal();

    return orientation_uncertainty;
}


double Bd970::interpretAngle(double const &value, const bool positive)
{
    double angle = value;
    double minutes = fmod(angle, 100);
    angle = static_cast<int>(angle / 100) + minutes / 60.0;
    if (!positive)
        angle = -angle;
    return angle;
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


