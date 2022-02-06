
#include "boost/test/unit_test.hpp"

#include "Sentence.h"
#include "Utils.h"

using namespace RussianLanguageAnalyzer;
using namespace Morphology;

BOOST_AUTO_TEST_SUITE(SentenceTests);

BOOST_AUTO_TEST_CASE(constructor)
{
  using namespace RussianLanguageAnalyzer;

  Sentence s("домашнее задание делаю быстро я");

  BOOST_TEST(*s.object()    == "задание");
  BOOST_TEST(*s.subject()   == "я");
  BOOST_TEST(*s.predicate() == "делаю");
}

BOOST_AUTO_TEST_SUITE_END();