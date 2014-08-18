#include <boost/test/unit_test.hpp>
#include <trimble_bd970/Dummy.hpp>

using namespace trimble_bd970;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    trimble_bd970::DummyClass dummy;
    dummy.welcome();
}
