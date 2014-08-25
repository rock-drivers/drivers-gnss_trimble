#include <boost/test/unit_test.hpp>
#include <gnss_trimble/Bd970.hpp>

using namespace gnss_trimble;

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
