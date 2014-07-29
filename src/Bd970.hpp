#ifndef _BD970_HPP_
#define _BD970_HPP_

/** Std libraries **/
#include <stdio.h>
#include <iostream>

/** Rock Std types **/
#include <base/Time.hpp>

/** IO Drivers library **/
#include <iodrivers_base/Driver.hpp>



namespace bd970
{


    static const uint8_t BEGIN_WORD = 0x24;

    class Bd970: public iodrivers_base::Driver
    {
    private:
        int const MAX_BUFFER_SIZE;
        float const SAMPLING_FREQUENCY; //Selected by default as frequency in the firmware
        uint8_t *buffer; /** Buffer with the current package **/

    protected:

        int	baudrate; /** Package baud rate **/
        base::Time pckgTimeout; /** Estimate time to have a whole package **/

    public:


        /** Constructors **/
        Bd970(int max_packet_size, float sampling_frequency);
        ~Bd970();

        /**
        * Print a welcome to stdout
        * \return nothing
        */
        void welcome();

        /** Sets the device baudrate (only possible for serial devices). +brate+ is
        * the baud rate in bps, can be one of 38400,
        *
        * If the device is not open yet, this baud rate will be set on startup (i.e.
        * in open())
        */
        bool setBaudrate(int brate);


        /** Open the device, reset it and read device information.**/
        bool open(std::string const& filename);

        /** Find a packet into the currently accumulated data.
        */
        int extractPacket(uint8_t const* buffer, size_t buffer_size) const;

        /** \brief read the package and puts the data into the corresponding structures. *
        */
        int processPacket();

        void printBuffer ();

    };

} // end namespace bd970

#endif // _BD970_HPP_
