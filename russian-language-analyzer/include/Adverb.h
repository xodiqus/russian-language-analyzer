#pragma once
#include <string>
#include "Word.h"

namespace RussianLanguageAnalyzer
{
  class Adverb : public Word
  {
  public:
    Adverb(std::string_view word);

    static bool maybe(std::string_view word);

    std::optional<Relation> relates(Verb const&) const override;

    operator std::string() const override;

    std::type_info const& get_typeid() const override;
  };
}

