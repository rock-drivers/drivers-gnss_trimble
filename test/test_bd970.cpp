#include <boost/test/unit_test.hpp>
#include <bd970/Bd970.hpp>

using namespace bd970;

static const unsigned int MAX_PACKET_SIZE = 2048;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    bd970::Bd970 mybd970(MAX_PACKET_SIZE);
    mybd970.welcome();
}
