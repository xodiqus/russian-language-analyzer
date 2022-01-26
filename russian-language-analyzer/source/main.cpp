
#include <iostream>

#include <clocale>

#include "Sentence.h"
#include "Word.h"
#include "Noun.h"
#include "Pronoun.h"
#include "Verb.h"
#include "Adjective.h"

#include "Utils.h"
#include "Adverb.h"

int main()
{
  using namespace RussianLanguageAnalyzer;
  using Utils::operator<<;

  std::setlocale(LC_ALL, "");

  std::cout << "Делаем разбор предложения: \"домашнее задание делаю быстро я\"." << std::endl << std::endl;

  auto s = Sentence("домашнее задание делаю быстро я");

  {
    auto w = dynamic_cast<Pronoun const*>(s.subject());
    std::cout << "Подлежащие: " << (std::string)*w
              << " (лицо: " << w->person() << ", число: " << w->count() << ", падеж: " << w->case_() << ")" << std::endl;
  }
  {
    auto w = dynamic_cast<Verb const*>(s.predicate());
    std::cout << "Сказуемое: " << (std::string)*w
              << " (время: " << w->tense() << ", лицо: " << w->person() << ", число: " << w->count() << ")" << std::endl;
  }
  {
    auto w = dynamic_cast<Noun const*>(s.object());
    std::cout << "Дополнение: " << (std::string)*w
      << " (род: " << w->gender() << ", число: " << w->count() << ", падеж: " << w->case_() << ")" << std::endl;
  }
  {
    auto w = dynamic_cast<Adjective const*>(s.object()->_child.get());
    std::cout << "Определение: " << (std::string)*w
      << " (род: " << w->gender() << ", число: " << w->count() << ", падеж: " << w->case_() << ")" << std::endl;
  }
  {
    auto w = dynamic_cast<Adverb const*>(s.predicate()->_child.get());
    std::cout << "Обстоятельство: " << (std::string)*w << std::endl;
  }

  return 0;
}

