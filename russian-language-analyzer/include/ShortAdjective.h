#pragma once
#include <string>

#include "Word.h"

namespace RussianLanguageAnalyzer
{

  class ShortAdjective : public Word
  {
    std::string _root;
    Morphology::Gender _gender;
    Morphology::Count _count;
    
  public:
    static bool maybe(std::string_view word);

    ShortAdjective(std::string_view word);

    std::optional<Relation> relates(Word const&) const override;

    Morphology::Count count() const { return _count; }
    Morphology::Gender gender() const { return _gender; }

    operator std::string() const override;
  };

}
