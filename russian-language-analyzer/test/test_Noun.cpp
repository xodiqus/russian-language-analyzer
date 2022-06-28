
#include "boost/test/unit_test.hpp"

#include "Noun.h"
#include "Utils.h"

using namespace RussianLanguageAnalyzer;
using namespace Morphology;

BOOST_AUTO_TEST_SUITE(NounTests);

BOOST_AUTO_TEST_CASE(constructor)
{
  auto variations = Noun::createVariations("слово");

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
  auto word = Noun("слово", Case::nominative, Count::single, Gender::n);

  word.set(Case::genitive);       BOOST_TEST(word == "слова");
  word.set(Case::dative);         BOOST_TEST(word == "слову");
  word.set(Case::accusative);     BOOST_TEST(word == "слово");
  word.set(Case::instrumental);   BOOST_TEST(word == "словом");
  word.set(Case::prepositional);  BOOST_TEST(word == "слове");
  word.set(Case::nominative);     BOOST_TEST(word == "слово");

  word = Noun("стол", Case::nominative, Count::single, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "стола");
  word.set(Case::dative);         BOOST_TEST(word == "столу");
  word.set(Case::accusative);     BOOST_TEST(word == "стол");
  word.set(Case::instrumental);   BOOST_TEST(word == "столом");
  word.set(Case::prepositional);  BOOST_TEST(word == "столе");
  word.set(Case::nominative);     BOOST_TEST(word == "стол");

  word = Noun("человек", Case::nominative, Count::single, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "человека");//родительный
  word.set(Case::dative);         BOOST_TEST(word == "человеку");//дательный
  word.set(Case::accusative);     BOOST_TEST(word == "человека");//винительный
  word.set(Case::instrumental);   BOOST_TEST(word == "человеком");//творительный
  word.set(Case::prepositional);  BOOST_TEST(word == "человеке");//предложный
  word.set(Case::nominative);     BOOST_TEST(word == "человек");//именительный

  word = Noun("м€чи", Case::nominative, Count::plural, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "м€чей");
  word.set(Case::dative);         BOOST_TEST(word == "м€чам");
  word.set(Case::accusative);     BOOST_TEST(word == "м€чи");
  word.set(Case::instrumental);   BOOST_TEST(word == "м€чами");
  word.set(Case::prepositional);  BOOST_TEST(word == "м€чах");
  word.set(Case::nominative);     BOOST_TEST(word == "м€чи");

  word = Noun("мужчины", Case::nominative, Count::plural, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "мужчин");
  word.set(Case::dative);         BOOST_TEST(word == "мужчинам");
  word.set(Case::accusative);     BOOST_TEST(word == "мужчин");
  word.set(Case::instrumental);   BOOST_TEST(word == "мужчинами");
  word.set(Case::prepositional);  BOOST_TEST(word == "мужчинах");
  word.set(Case::nominative);     BOOST_TEST(word == "мужчины");

  word = Noun("лицо", Case::nominative, Count::single, Gender::n);

  word.set(Case::genitive);       BOOST_TEST(word == "лица");
  word.set(Case::dative);         BOOST_TEST(word == "лицу");
  word.set(Case::accusative);     BOOST_TEST(word == "лицо");
  word.set(Case::instrumental);   BOOST_TEST(word == "лицом");
  word.set(Case::prepositional);  BOOST_TEST(word == "лице");
  word.set(Case::nominative);     BOOST_TEST(word == "лицо");

  word = Noun("девочка", Case::nominative, Count::single, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "девочки");
  word.set(Case::dative);         BOOST_TEST(word == "девочке");
  word.set(Case::accusative);     BOOST_TEST(word == "девочку");
  word.set(Case::instrumental);   BOOST_TEST(word == "девочкой");
  word.set(Case::prepositional);  BOOST_TEST(word == "девочке");
  word.set(Case::nominative);     BOOST_TEST(word == "девочка");

  word = Noun("мальчик", Case::nominative, Count::single, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "мальчика");
  word.set(Case::dative);         BOOST_TEST(word == "мальчику");
  word.set(Case::accusative);     BOOST_TEST(word == "мальчика");
  word.set(Case::instrumental);   BOOST_TEST(word == "мальчиком");
  word.set(Case::prepositional);  BOOST_TEST(word == "мальчике");
  word.set(Case::nominative);     BOOST_TEST(word == "мальчик");

  word = Noun("муж", Case::nominative, Count::single, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "мужа");
  word.set(Case::dative);         BOOST_TEST(word == "мужу");
  word.set(Case::accusative);     BOOST_TEST(word == "мужа");
  word.set(Case::instrumental);   BOOST_TEST(word == "мужем");
  word.set(Case::prepositional);  BOOST_TEST(word == "муже");
  word.set(Case::nominative);     BOOST_TEST(word == "муж");

  word = Noun("жена", Case::nominative, Count::single, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "жены");
  word.set(Case::dative);         BOOST_TEST(word == "жене");
  word.set(Case::accusative);     BOOST_TEST(word == "жену");
  word.set(Case::instrumental);   BOOST_TEST(word == "женой");
  word.set(Case::prepositional);  BOOST_TEST(word == "жене");
  word.set(Case::nominative);     BOOST_TEST(word == "жена");

  word = Noun("космолет", Case::nominative, Count::single, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "космолета");
  word.set(Case::dative);         BOOST_TEST(word == "космолету");
  word.set(Case::accusative);     BOOST_TEST(word == "космолет");
  word.set(Case::instrumental);   BOOST_TEST(word == "космолетом");
  word.set(Case::prepositional);  BOOST_TEST(word == "космолете");
  word.set(Case::nominative);     BOOST_TEST(word == "космолет");

  word = Noun("€блоко", Case::nominative, Count::single, Gender::n);

  word.set(Case::genitive);       BOOST_TEST(word == "€блока");
  word.set(Case::dative);         BOOST_TEST(word == "€блоку");
  word.set(Case::accusative);     BOOST_TEST(word == "€блоко");
  word.set(Case::instrumental);   BOOST_TEST(word == "€блоком");
  word.set(Case::prepositional);  BOOST_TEST(word == "€блоке");
  word.set(Case::nominative);     BOOST_TEST(word == "€блоко");

  word = Noun("жижа", Case::nominative, Count::single, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "жижи");
  word.set(Case::dative);         BOOST_TEST(word == "жиже");
  word.set(Case::accusative);     BOOST_TEST(word == "жижу");
  word.set(Case::instrumental);   BOOST_TEST(word == "жижей");
  word.set(Case::prepositional);  BOOST_TEST(word == "жиже");
  word.set(Case::nominative);     BOOST_TEST(word == "жижа");

  word = Noun("тело", Case::nominative, Count::single, Gender::n);

  word.set(Case::genitive);       BOOST_TEST(word == "тела");
  word.set(Case::dative);         BOOST_TEST(word == "телу");
  word.set(Case::accusative);     BOOST_TEST(word == "тело");
  word.set(Case::instrumental);   BOOST_TEST(word == "телом");
  word.set(Case::prepositional);  BOOST_TEST(word == "теле");
  word.set(Case::nominative);     BOOST_TEST(word == "тело");

  word = Noun("куртка", Case::nominative, Count::single, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "куртки");
  word.set(Case::dative);         BOOST_TEST(word == "куртке");
  word.set(Case::accusative);     BOOST_TEST(word == "куртку");
  word.set(Case::instrumental);   BOOST_TEST(word == "курткой");
  word.set(Case::prepositional);  BOOST_TEST(word == "куртке");
  word.set(Case::nominative);     BOOST_TEST(word == "куртка");

  word = Noun("окна", Case::nominative, Count::plural, Gender::n);

  word.set(Case::genitive);       BOOST_TEST(word == "окон");
  word.set(Case::dative);         BOOST_TEST(word == "окнам");
  word.set(Case::accusative);     BOOST_TEST(word == "окна");
  word.set(Case::instrumental);   BOOST_TEST(word == "окнами");
  word.set(Case::prepositional);  BOOST_TEST(word == "окнах");
  word.set(Case::nominative);     BOOST_TEST(word == "окна");

  word = Noun("плать€", Case::nominative, Count::plural, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "платьев");
  word.set(Case::dative);         BOOST_TEST(word == "плать€м");
  word.set(Case::accusative);     BOOST_TEST(word == "плать€");
  word.set(Case::instrumental);   BOOST_TEST(word == "плать€ми");
  word.set(Case::prepositional);  BOOST_TEST(word == "плать€х");
  word.set(Case::nominative);     BOOST_TEST(word == "плать€");

  word = Noun("маска", Case::nominative, Count::single, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "маски");
  word.set(Case::dative);         BOOST_TEST(word == "маске");
  word.set(Case::accusative);     BOOST_TEST(word == "маску");
  word.set(Case::instrumental);   BOOST_TEST(word == "маской");
  word.set(Case::prepositional);  BOOST_TEST(word == "маске");
  word.set(Case::nominative);     BOOST_TEST(word == "маска");

  word = Noun("колЄса", Case::nominative, Count::plural, Gender::n);

  word.set(Case::genitive);       BOOST_TEST(word == "колЄс");
  word.set(Case::dative);         BOOST_TEST(word == "колЄсам");
  word.set(Case::accusative);     BOOST_TEST(word == "колЄса");
  word.set(Case::instrumental);   BOOST_TEST(word == "колЄсами");
  word.set(Case::prepositional);  BOOST_TEST(word == "колЄсах");
  word.set(Case::nominative);     BOOST_TEST(word == "колЄса");

  word = Noun("карандаши", Case::nominative, Count::plural, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "карандашей");
  word.set(Case::dative);         BOOST_TEST(word == "карандашам");
  word.set(Case::accusative);     BOOST_TEST(word == "карандаши");
  word.set(Case::instrumental);   BOOST_TEST(word == "карандашами");
  word.set(Case::prepositional);  BOOST_TEST(word == "карандашах");
  word.set(Case::nominative);     BOOST_TEST(word == "карандаши");

  word = Noun("руки", Case::nominative, Count::plural, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "рук");
  word.set(Case::dative);         BOOST_TEST(word == "рукам");
  word.set(Case::accusative);     BOOST_TEST(word == "руки");
  word.set(Case::instrumental);   BOOST_TEST(word == "руками");
  word.set(Case::prepositional);  BOOST_TEST(word == "руках");
  word.set(Case::nominative);     BOOST_TEST(word == "руки");

  word = Noun("платки", Case::nominative, Count::plural, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "платков");
  word.set(Case::dative);         BOOST_TEST(word == "платкам");
  word.set(Case::accusative);     BOOST_TEST(word == "платки");
  word.set(Case::instrumental);   BOOST_TEST(word == "платками");
  word.set(Case::prepositional);  BOOST_TEST(word == "платках");
  word.set(Case::nominative);     BOOST_TEST(word == "платки");

  word = Noun("бананы", Case::nominative, Count::plural, Gender::m);

  word.set(Case::genitive);       BOOST_TEST(word == "бананов");
  word.set(Case::dative);         BOOST_TEST(word == "бананам");
  word.set(Case::accusative);     BOOST_TEST(word == "бананы");
  word.set(Case::instrumental);   BOOST_TEST(word == "бананами");
  word.set(Case::prepositional);  BOOST_TEST(word == "бананах");
  word.set(Case::nominative);     BOOST_TEST(word == "бананы");

  word = Noun("ракета", Case::nominative, Count::single, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "ракеты");
  word.set(Case::dative);         BOOST_TEST(word == "ракете");
  word.set(Case::accusative);     BOOST_TEST(word == "ракету");
  word.set(Case::instrumental);   BOOST_TEST(word == "ракетой");
  word.set(Case::prepositional);  BOOST_TEST(word == "ракете");
  word.set(Case::nominative);     BOOST_TEST(word == "ракета");

  word = Noun("кружки", Case::nominative, Count::plural, Gender::f);

  word.set(Case::genitive);       BOOST_TEST(word == "кружек");
  word.set(Case::dative);         BOOST_TEST(word == "кружкам");
  word.set(Case::accusative);     BOOST_TEST(word == "кружки");
  word.set(Case::instrumental);   BOOST_TEST(word == "кружками");
  word.set(Case::prepositional);  BOOST_TEST(word == "кружках");
  word.set(Case::nominative);     BOOST_TEST(word == "кружки");
}

BOOST_AUTO_TEST_SUITE_END();
