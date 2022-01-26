
#include <boost/test/unit_test.hpp>

#include "Verb.h"

using namespace RussianLanguageAnalyzer;
using namespace Morphology;

BOOST_AUTO_TEST_CASE(constructor)
{
  auto verb = Verb("делаю");

  BOOST_TEST((verb.count() == Count::single));
  BOOST_TEST((verb.person() == Person::first));
  BOOST_TEST((verb.tense() == Tense::present));
}