
#include "Pronoun.h"
#include "Adjective.h"
#include "ShortAdjective.h"
#include "Verb.h"

#include "Utils.h"

namespace RussianLanguageAnalyzer
{
  Pronoun::Pronoun(std::string_view p) : _word(p)
  {
    using namespace Morphology;

    if (p == "ÿ")
    {
      _case = Case::nominative;
      _count = Count::single;
      _person = Person::first;
    }
  }

  bool Pronoun::maybe(std::string_view s)
  {
    if (s == "ÿ")
    {
      return true;
    }

    return false;
  }
  
  std::optional<Relation> Pronoun::relates(Verb const& v) const 
  {
    using namespace Morphology;
    using Utils::equal;

    if (equal<Count, Person>(this, &v))
    {
      if (this->person() == Person::third && equal<Gender>(this, &v)
        || this->person() != Person::third)
      {
        return Relation::subject;
      }
    }

    return std::nullopt;
  }

  std::optional<Relation> Pronoun::relates(Adjective const& a) const 
  {
    using namespace Morphology;
    using Utils::equal;

    if (equal<Count, Gender>(this, &a) && this->case_() == Case::nominative && a.case_() == Case::nominative)
    {
      return Relation::subject;
    }

    return std::nullopt;
  }

  std::optional<Relation> Pronoun::relates(ShortAdjective const& h) const 
  {
    using namespace Morphology;
    using Utils::equal;
  
    if (equal<Count, Gender>(this, &h))
    {
      return Relation::subject;
    }

    return std::nullopt;
  }

  Pronoun::operator std::string() const
  {
    return _word; 
  }

  std::type_info const& Pronoun::get_typeid() const
  {
    return typeid(Pronoun);
  }
}