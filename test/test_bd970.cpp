#include <boost/test/unit_test.hpp>
#include <trimble_bd970/Bd970.hpp>

using namespace trimble_bd970;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    Bd970 mybd970(512, 1.0);
    
    mybd970.setupNMEA("/dev/ttyUSB0", 38400);
    
    for (register size_t i = 0; i < 10; i++)
    {
        mybd970.processNMEA();
        mybd970.printBufferNMEA();
        
        mybd970.printNMEA();
        
        
    }
    
    mybd970.closeNMEA();
}
