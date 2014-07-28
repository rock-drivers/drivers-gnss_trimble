#include <boost/test/unit_test.hpp>
#include <bd970/Bd970.hpp>

using namespace bd970;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    bd970::Bd970 mybd970;
    mybd970.welcome();
}
