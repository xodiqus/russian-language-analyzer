
#define BOOST_TEST_MODULE RussianLanguageAnalyzer.Tests

#define BOOST_TEST_NO_MAIN 
#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/included/unit_test.hpp>
#include <clocale>

int main(int argc, char** argv)
{
  using namespace boost::unit_test;

  std::setlocale(LC_ALL, "");

  return unit_test_main(&init_unit_test, argc, argv);
}

