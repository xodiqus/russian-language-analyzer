#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Word.h"

#include "Utils.h"

namespace RussianLanguageAnalyzer
{
  class Verb : public Word
  {
    Morphology::Count _count;
    Morphology::Tense _tense;
    // For Past, Future:
    Morphology::Kind _kind;
    // For Past:
    Morphology::Gender _gender;
    // For Present, Future:
    Morphology::Person _person;
    

  public:
    Verb(std::string_view word);

    static bool maybe(std::string_view s);

    static std::vector<std::unique_ptr<Verb>> createVariations(std::string_view s);

    std::optional<Relation> relates(Noun const&) const override;
    std::optional<Relation> relates(Pronoun const& p) const override;

    Morphology::Count count() const { return _count; }
    Morphology::Gender gender() const { return _gender; }
    Morphology::Person person() const { return _person; }
    Morphology::Tense tense() const { return _tense; }

    operator std::string() const override;

    std::type_info const& get_typeid() const override;
  };
}

