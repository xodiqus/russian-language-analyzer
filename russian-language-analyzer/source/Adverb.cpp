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
 
  std::optional<Relation> Adverb::relates(Word const& w) const
  {
    using namespace Morphology;
    using Utils::equal;

    if (auto v = dynamic_cast<Verb const*>(&w))
    {
      return Relation::circumstance;
    }

    return std::nullopt;
  }

  Adverb::operator std::string() const
  {
    return _word;
  }
}
