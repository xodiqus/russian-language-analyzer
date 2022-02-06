#include "Adverb.h"
#include "Verb.h"

#include "Utils.h"

namespace RussianLanguageAnalyzer
{
  Adverb::Adverb(std::string_view word)
    : _word(word)
  {

  }

  bool Adverb::maybe(std::string_view word)
  {
    if (word.ends_with("î"))
    {
      return true;
    }

    return false;
  }
 
  std::optional<Relation> Adverb::relates(Verb const& w) const
  {
    return Relation::circumstance;
  }

  Adverb::operator std::string() const
  {
    return _word;
  }

  std::type_info const& Adverb::get_typeid() const
  {
    return typeid(Adverb);
  }
}
