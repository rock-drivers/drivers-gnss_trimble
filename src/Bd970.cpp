#include "Bd970.hpp"

using namespace bd970;


Bd970::Bd970(int max_packet_size, float sampling_frequency)
:Driver(max_packet_size)
,MAX_BUFFER_SIZE(max_packet_size)
,SAMPLING_FREQUENCY(sampling_frequency)
,buffer(new uint8_t[max_packet_size])
,baudrate(iodrivers_base::Driver::SERIAL_921600)
{
    pckgTimeout = base::Time::fromSeconds(1.0/SAMPLING_FREQUENCY);

    if(MAX_BUFFER_SIZE <= 0)
        std::runtime_error("Driver: max_packet_size cannot be smaller or equal to 0!");

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

bool Bd970::setBaudrate(int brate)
{
    this->baudrate = brate;

    return true;
}

int Bd970::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{

    int packet_state = 0; //0-> no synchronized, 1->Semi synchonized, 2-> package found
    unsigned short start_position = 0;

//    std::cout<<"**** extractPacket ****\n";
//    std::cout<<"buffer_size: "<< buffer_size <<"\n";
//    for ( int i=0; i < (int)buffer_size; i++)
//        printf("%X \n", buffer[i]);

    /** Found start of the packet **/
    for (register unsigned int i=0; i < (unsigned int)buffer_size; i++)
    {
        if (buffer[i] == BEGIN_WORD)
        {
            start_position = i;
            packet_state = 1;
            break;
        }
    }

    if (packet_state == 0)
        return -buffer_size;
    else if (packet_state == 1)
    {
        return -start_position;
    }
    else
    {
        if (start_position > 0)
            return -start_position;
        else
            return MAX_BUFFER_SIZE;
    }

    return 0;
}

int Bd970::processPacket()
{

    int buf_size = 0;
    //std::cout<<"processPacket\n";

    try {
        buf_size = Driver::readPacket (this->buffer, MAX_PACKET_SIZE, this->pckgTimeout);
    } catch (iodrivers_base::TimeoutError& e ) { 
	std::cerr<<"TimeoutError buffer size: "<<buf_size<<"\n";
	return false;
    }

    return true;
}

void Bd970::printBuffer ()
{

    std::cout<<"BEGIN BUFFER:\n";

    for (register unsigned int i=0; i < (unsigned int)MAX_BUFFER_SIZE; i++)
    {
        std::cout<< buffer[i]<<" ";
    }
    std::cout<<"\nEND BUFFER.";

}
