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
#include <base/Float.hpp>
#include <base/Time.hpp>

/** BD970 Driver Types **/
#include <trimble_bd970/NMEABaseTypes.hpp>

/**
 * 
 * 
 */
namespace trimble_bd970
{

    static const int NMEA_MESSAGE_NUM = 5;
    /**
     * 
     * 
     */
    enum NMEA_TAG
    {
        MSG_NULL  = 0,
        GGA       = 1,
        GST       = 2,
        PTNL_AVR  = 3,
        ZDA       = 4,
        HDT       = 5
    };


    /**
     * 
     * 
     */

    class NMEA_GGA : public NMEA_Base
    {
        private:
            static const int NUMBER_OF_FIELD = 15;

        public:

            //boost::shared_ptr<NMEA_GGA> mp_message;

            /** Message Data **/
            double      utc;

            double      latitude;
            std::string lat_dir;

            double      longitude;
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
        private:
            static const int NUMBER_OF_FIELD = 12;

        public:

            //boost::shared_ptr<NMEA_AVR> mp_message;

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
        private:
            static const int NUMBER_OF_FIELD = 3;

        public:

            //boost::shared_ptr<NMEA_HDT> mp_message;

            /** Message Data **/
            double      heading;
            std::string heading_dir;


            NMEA_HDT(void);

            ~NMEA_HDT(void);


            int extractMessage(uint8_t *buffer, int message_len);

            int printMessage(void);

    };


    class NMEA_GST : public NMEA_Base
    {
        private:
            static const int NUMBER_OF_FIELD = 9;

        public:

            /** Message Data **/
            double utc;
            double rms;

            double semi_major_axis_sigma_error; // 1-sigma in meters
            double semi_minor_axis_sigma_error; // 1-sigma in meters

            double heading_sigma_error; //1-sigma in degrees

            double latitude_sigma_error; //1-sigma in meters
            double longitude_sigma_error; //1-sigma in meters
            double height_sigma_error; //1-sigma in meters

            NMEA_GST(void);

            ~NMEA_GST(void);


            int extractMessage(uint8_t *buffer, int message_len);

            int printMessage(void);

    };

    class NMEA_ZDA : public NMEA_Base
    {
        private:
            static const int NUMBER_OF_FIELD = 7;

        public:

            /** Message Data **/
            double utc;
            int  day;
            int  month;
            int  year;

            int  gmt_hours_offset;
            int  gmt_minutes_offset;


            NMEA_ZDA(void);

            ~NMEA_ZDA(void);


            int extractMessage(uint8_t *buffer, int message_len);

            int printMessage(void);

    };


    /**
     *
     *
     *
     */
    class NMEA_Messages
    {
        public:

            base::Time  m_rx_time;
            base::Time  m_tx_time;

            int m_number_messages;

            int *m_message_lengths;

            int64_t process_time;


            // TODO: Dynaimc Messages
            //std::vector<NMEA_Base::mp_message> mp_messages;
            //NMEA_Base *mp_messages;

            /** Message Data in the order given by the receiver **/
            NMEA_GGA data_gga;
            NMEA_GST data_gst;
            NMEA_AVR data_avr;
            NMEA_ZDA data_zda;
            NMEA_HDT data_hdt;


            NMEA_Messages(void);

            virtual ~NMEA_Messages(void);


            int checkTag(uint8_t *buffer);

            int extractNMEA(uint8_t *buffer);

            int printMessages(void);

    };
}

#endif // _BD970_NMEA_TYPES_HPP_
