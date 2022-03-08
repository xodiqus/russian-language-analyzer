#pragma once

#include <string> 
#include <vector>
#include <memory>

#include "Word.h"

namespace RussianLanguageAnalyzer
{
  class Adjective : public Word
  {
    Morphology::Case _case;
    Morphology::Gender _gender;
    Morphology::Count _count;

  public:
    Adjective(std::string baseForm, Morphology::Case case_, Morphology::Count count, Morphology::Gender gender)
      : Word(baseForm), _case(case_), _count(count), _gender(gender)
    {
    }

    Morphology::Gender gender() const { return _gender; }
    Morphology::Count   count() const { return _count; }
    Morphology::Case    case_() const { return _case; }

    static bool maybe(std::string_view s);

    static std::vector<std::unique_ptr<Adjective>> createVariations(std::string_view s);

    std::optional<Relation> relates(Pronoun const&) const override;
    std::optional<Relation> relates(Noun const& n) const override;
    std::optional<Relation> relates(ShortAdjective const& n) const override;

    operator std::string() const override;

    std::type_info const& get_typeid() const override;
  };
}

