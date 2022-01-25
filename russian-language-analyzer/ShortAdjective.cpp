#include "ShortAdjective.h"
#include "Noun.h"
#include "Adjective.h"
#include "Pronoun.h"

#include "Utils.h"

namespace RussianLanguageAnalyzer
{
  bool ShortAdjective::maybe(std::string_view w)
  {
    if (w.ends_with("î") || w.ends_with("û") || w.ends_with("à"))
    {
      return true;
    }

    return false;
  }

  ShortAdjective::ShortAdjective(std::string_view w)
  {
    using namespace Morphology;

    if (w.ends_with("î"))
    {
      _gender = Gender::n;
      _count = Count::single;
      _root = w.substr(0, w.length() - 1);
    }
  }
  
  std::optional<Relation> ShortAdjective::relates(Word const& w) const
  {
    using namespace Morphology;
    using Utils::equal;

    if (auto n = dynamic_cast<Noun const*>(&w))
    {
      if (equal<Count, Gender>(this, n))
      {
        return Relation::predicate;
      }
    }

    if (auto a = dynamic_cast<Adjective const*>(&w))
    {
      if (a->case_() == Case::nominative && equal<Gender, Count>(this, a))
      {
        return Relation::predicate;
      }
    }

    if (auto p = dynamic_cast<Pronoun const*>(&w))
    {
      if (p->case_() == Case::nominative && equal<Gender, Count>(this, p))
      {
        return Relation::predicate;
      }
    }

    return std::nullopt;
  }

  ShortAdjective::operator std::string() const
  {
    using namespace Morphology;
    std::string r = _root;
    if (_count == Count::single && _gender == Gender::n)
    {
      r += "î";
    }

    return r;
  }
}
