#include <memory>

#include "Noun.h"
#include "Verb.h"
#include "Adjective.h"
#include "ShortAdjective.h"

#include "Utils.h"

namespace RussianLanguageAnalyzer
{
  bool Noun::maybe(std::string_view s)
  {
    if (s.ends_with("ие"))
    {
      return true;
    }

    return false;
  }

  std::vector<std::unique_ptr<Noun>> Noun::createVariations(std::string_view s)
  {
    std::vector<std::unique_ptr<Noun>> r;

    if (s.ends_with("ие"))
    {
      using namespace Morphology;
      auto root = s.substr(0, s.length() - 2);
      r.emplace_back(new Noun(std::string(root), Case::accusative, Count::single, Gender::n));

      r.emplace_back(new Noun(std::string(root), Case::nominative, Count::single, Gender::n));
    }

    return r;
  }

  std::optional<Relation> Noun::relates(Word const& w) const
  {
    using namespace Morphology;
    using Utils::equal;

    if (auto v = dynamic_cast<Verb const*>(&w))
    {
      if (equal<Count>(this, v) && this->case_() == Case::nominative && v->person() == Person::third)
      {
        return Relation::subject;
      }

      if (this->case_() == Case::accusative)
      {
        return Relation::object;
      }
    }

    if (auto h = dynamic_cast<ShortAdjective const*>(&w))
    {
      if (equal<Count, Gender>(this, h))
      {
        return Relation::subject;
      }
    }

    return std::nullopt;
  }

  Noun::operator std::string() const
  {
    using namespace Morphology;
    std::string r = _root;
    if ((_case == Case::nominative || _case == Case::accusative) && _count == Count::single && _gender == Gender::n)
    {
      r += "ие";
    }

    return r;
  }
}