
#include "boost/test/unit_test.hpp"

#include "Noun.h"

using namespace RussianLanguageAnalyzer;
using namespace Morphology;

BOOST_AUTO_TEST_CASE(constructor)
{
  auto variations = Noun::createVariations("слово");

  BOOST_TEST(variations.size() == 2);
  
  BOOST_TEST((variations[0]->gender() == Gender::n));
  BOOST_TEST((variations[1]->gender() == Gender::n));
            
  BOOST_TEST((variations[0]->count() == Count::single));
  BOOST_TEST((variations[1]->count() == Count::single));
            
  BOOST_TEST((variations[0]->case_() == Case::nominative));
  BOOST_TEST((variations[1]->case_() == Case::accusative));
}