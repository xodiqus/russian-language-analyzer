#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Word.h"

namespace RussianLanguageAnalyzer
{

  class Pronoun : public Word
  {
    std::string _word;

    Morphology::Gender _gender;
    Morphology::Count _count;
    Morphology::Case _case;
    Morphology::Person _person;

  public:

    Pronoun(std::string root, Morphology::Case case_, Morphology::Count count, Morphology::Gender gender)
      : _word(root), _case(case_), _count(count), _gender(gender)
    {
    }

    Pronoun(std::string_view p);

    static bool maybe(std::string_view s);

    static std::vector<std::unique_ptr<Pronoun>> createVariations(std::string_view s);

    std::optional<Relation> relates(Word const&) const override;

    Morphology::Count  count() const  { return _count; }
    Morphology::Gender gender() const { return _gender; }
    Morphology::Case   case_() const  { return _case; }
    Morphology::Person person() const { return _person; }

    operator std::string() const override;
  };

}

