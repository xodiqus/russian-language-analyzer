#pragma once

#include <string_view>
#include <memory>
#include <vector>

#include "Word.h"

namespace RussianLanguageAnalyzer
{
  class Sentence
  {
    std::unique_ptr<Word> _subject, _predicate, _object;

  public:
    Sentence(std::string_view s);

    const Word*   subject() const { return    _subject.get(); }
    const Word*    object() const { return     _object.get(); }
    const Word* predicate() const { return  _predicate.get(); }

  private:
    static std::vector<std::unique_ptr<Word>> determineVariations(std::string_view s);
  };
}

