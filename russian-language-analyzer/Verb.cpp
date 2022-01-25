
#include "Verb.h"
#include "Pronoun.h"
#include "Noun.h"

#include "Utils.h"

namespace RussianLanguageAnalyzer
{
  Verb::Verb(std::string_view s)
  {
    using namespace Morphology;

    if (s.ends_with("��"))
    {
      _infinitive = std::string(s.substr(0, s.length() - 1)) + "��";
      _person = Person::first;
      _count = Count::single;
      _tense = Tense::present;
    }

    if (s.starts_with("�"))
    {
      _kind = Kind::perfect;
      _tense = Tense::future;
    }
    else
    {
      _kind = Kind::imperfect;
    }
  }

  bool Verb::maybe(std::string_view s)
  {
    if (s.ends_with("��"))
    {
      return true;
    }

    return false;
  }

  std::optional<Relation> Verb::relates(Word const& w) const
  {
    using Utils::equal;
    using namespace Morphology;

    if (auto p = dynamic_cast<Pronoun const*>(&w))
    {
      if (equal<Count, Person>(this, p))
      {
        return Relation::predicate;
      }
    }

    if (auto n = dynamic_cast<Noun const*>(&w))
    {
      if (n->case_() == Case::accusative)
      {
        return Relation::predicate;
      }
    }

    return std::nullopt;
  }

  Verb::operator std::string() const
  {
    using namespace Morphology;
    std::string r = _infinitive.substr(0, _infinitive.length() - 2);

    if (_person == Person::first && _count == Count::single && _tense == Tense::present)
    {
      r += "�";
    }

    return r;
  }
}