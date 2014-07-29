#include <boost/test/unit_test.hpp>
#include <bd970/Bd970.hpp>

using namespace bd970;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    bd970::Bd970 mybd970(1024, 1.0);
    mybd970.welcome();
    mybd970.open("/dev/ttyXR0", iodrivers_base::Driver::SERIAL_921600);

    while (100)
    {
        mybd970.processPacket();
        mybd970.printBuffer();
    }

}
