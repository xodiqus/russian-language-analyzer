#pragma once
#include <string>
#include "Word.h"

namespace RussianLanguageAnalyzer
{

  class Adverb : public Word
  {
    std::string _word;

  public:
    Adverb(std::string_view word);

    static bool maybe(std::string_view word);

    std::optional<Relation> relates(Word const&) const override;

    operator std::string() const override;
  };
}

