
#include "boost/test/unit_test.hpp"

#include "Noun.h"
#include "Utils.h"

#include <iostream>

using namespace RussianLanguageAnalyzer;
using namespace Morphology;

BOOST_AUTO_TEST_SUITE(NounTests);

BOOST_AUTO_TEST_CASE(constructor)
{
  auto variations = Noun::createVariations("סכמגמ");

  BOOST_TEST(variations.size() == 2);
  
  BOOST_TEST(variations[0]->gender() == Gender::n);
  BOOST_TEST(variations[1]->gender() == Gender::n);
            
  BOOST_TEST(variations[0]->count() == Count::single);
  BOOST_TEST(variations[1]->count() == Count::single);
            
  BOOST_TEST(variations[0]->case_() == Case::nominative);
  BOOST_TEST(variations[1]->case_() == Case::accusative);
}

BOOST_AUTO_TEST_CASE(setCase)
{
  auto word = Noun("סכמגמ", Case::nominative, Count::single, Gender::n);

  word.set(Case::genitive);       BOOST_TEST(word == "סכמגא");
  word.set(Case::dative);         BOOST_TEST(word == "סכמגף");
  word.set(Case::accusative);     BOOST_TEST(word == "סכמגמ");
  word.set(Case::instrumental);   BOOST_TEST(word == "סכמגמל");
  word.set(Case::prepositional);  BOOST_TEST(word == "סכמגו");
  word.set(Case::nominative);     BOOST_TEST(word == "סכמגמ");

  word = Noun("סעמכ", Case::nominative, Count::single, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "סעמכא");
  word.set(Case::dative);         BOOST_TEST(word == "סעמכף");
  word.set(Case::accusative);     BOOST_TEST(word == "סעמכ");
  word.set(Case::instrumental);   BOOST_TEST(word == "סעמכמל");
  word.set(Case::prepositional);  BOOST_TEST(word == "סעמכו");
  word.set(Case::nominative);     BOOST_TEST(word == "סעמכ");
}

BOOST_AUTO_TEST_SUITE_END();