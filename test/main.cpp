#define BOOST_TEST_BUILD_INFO true

#define BOOST_TEST_MODULE QoUtils_tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

int main(int argc, char* argv[], char* envp[])
{
  using namespace boost::unit_test;

  return unit_test_main( &init_unit_test, argc, argv );
}