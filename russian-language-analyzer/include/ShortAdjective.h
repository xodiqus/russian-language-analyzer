#pragma once
#include <string>

#include "Word.h"

namespace RussianLanguageAnalyzer
{

  class ShortAdjective : public Word
  {
    Morphology::Gender _gender;
    Morphology::Count _count;
    
  public:
    static bool maybe(std::string_view word);

    ShortAdjective(std::string_view word);

    std::optional<Relation> relates(Noun const& w) const override;
    std::optional<Relation> relates(Adjective const& w) const override;
    std::optional<Relation> relates(Pronoun  const& w) const override;

    Morphology::Count count() const { return _count; }
    Morphology::Gender gender() const { return _gender; }

    operator std::string() const override;

    std::type_info const& get_typeid() const override;
  };

}
