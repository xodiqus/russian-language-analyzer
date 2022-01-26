
#include "boost/test/unit_test.hpp"

#include "Noun.h"

using namespace RussianLanguageAnalyzer;
using namespace Morphology;

BOOST_AUTO_TEST_SUITE(NounTests);

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

BOOST_AUTO_TEST_CASE(setCase)
{
  auto word = Noun("слово", Case::nominative);

  word.set(Case::genitive);       BOOST_TEST((word == "слова"));
  word.set(Case::dative);         BOOST_TEST((word == "слову"));
  word.set(Case::accusative);     BOOST_TEST((word == "слово"));
  word.set(Case::instrumental);   BOOST_TEST((word == "словом"));
  word.set(Case::prepositional);  BOOST_TEST((word == "слове"));
  word.set(Case::nominative);     BOOST_TEST((word == "слово"));
}

BOOST_AUTO_TEST_SUITE_END();