#ifndef _BD970_HPP_
#define _BD970_HPP_

/** Std libraries **/
#include <iostream>

/** IO Drivers library **/
#include <iodrivers_base/Driver.hpp>

namespace bd970
{

    static const unsigned int DEFAULT_SAMPLING_FREQUENCY = 1; //Selected by default as frequency in the firmware

    class Bd970: public iodrivers_base::Driver
    {
    public:


        /** Constructors **/
        Bd970(int max_packet_size);
        ~Bd970();

        /**
        * Print a welcome to stdout
        * \return nothing
        */
        void welcome();

        /** Open the device, reset it and read device information.**/
        bool open(std::string const& filename);

        /** Find a packet into the currently accumulated data.
        */
        int extractPacket(uint8_t const* buffer, size_t buffer_size) const;

        /** \brief read the package and puts the data into the corresponding structures. *
        */
        int processPacket();



    protected:
        int	baudrate; /** Package baud rate **/
        int sampling_frequency; /** Sampling Frequency**/


    };

} // end namespace bd970

#endif // _BD970_HPP_
