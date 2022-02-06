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
 
  std::optional<Relation> ShortAdjective::relates(Noun const& n) const 
  {
    using namespace Morphology;
    using Utils::equal;

    if (equal<Count, Gender>(this, &n))
    {
      return Relation::predicate;
    }

    return std::nullopt;
  }
  std::optional<Relation> ShortAdjective::relates(Adjective const& a) const 
  {
    using namespace Morphology;
    using Utils::equal;

    if (a.case_() == Case::nominative && equal<Gender, Count>(this, &a))
    {
      return Relation::predicate;
    }

    return std::nullopt;
  }
  std::optional<Relation> ShortAdjective::relates(Pronoun  const& p) const 
  {
    using namespace Morphology;
    using Utils::equal;

    if (p.case_() == Case::nominative && equal<Gender, Count>(this, &p))
    {
      return Relation::predicate;
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

  std::type_info const& ShortAdjective::get_typeid() const
  {
    return typeid(ShortAdjective);
  }
}
