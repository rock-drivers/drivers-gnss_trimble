#include "Bd970.hpp"

using namespace bd970;


Bd970::Bd970(int max_packet_size)
:Driver(max_packet_size)
,baudrate(iodrivers_base::Driver::SERIAL_921600)
,sampling_frequency(bd970::DEFAULT_SAMPLING_FREQUENCY)
{
}


void Bd970::welcome()
{
        std::cout << "You successfully compiled and executed BD970 Driver. Welcome!" << std::endl;
}

bool Bd970::open(const std::string& filename)
{
    if (! Driver::openSerial(filename, this->baudrate))
        return false;
    return true;
}

Bd970::~Bd970()
{
    if (isValid())
    close();
}


int Bd970::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{

}

int Bd970::processPacket()
{
}
