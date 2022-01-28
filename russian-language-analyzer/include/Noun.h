#pragma once
#include <string>
#include <vector>
#include <memory>
#include <ostream>

#include "Word.h"

namespace RussianLanguageAnalyzer
{
  class Noun : public Word
  {
    std::string _word;

    Morphology::Case _case;
    Morphology::Count _count;
    Morphology::Gender _gender;

  public:
    Noun();

    Noun(Noun     &&);
    Noun(Noun const& n);

    Noun& operator=(Noun     &&);
    Noun& operator=(Noun const&);

    Noun(std::string word, Morphology::Case case_, Morphology::Count count, Morphology::Gender gender)
      : _word(word), _case(case_), _count(count), _gender(gender)
    {
    }

    Morphology::Gender gender() const { return _gender; }
    Morphology::Count  count () const { return _count; }
    Morphology::Case    case_() const { return _case; }

    static bool maybe(std::string_view s);

    static std::vector<std::unique_ptr<Noun>> createVariations(std::string_view s);

    std::optional<Relation> relates(Word const&) const override;

    operator std::string() const override;

    void set(Morphology::Gender) = delete;
    void set(Morphology::Case);
  };

}
