#include "Adjective.h"

#include "Noun.h"
#include "Pronoun.h"
#include "ShortAdjective.h"

#include "Utils.h"

namespace RussianLanguageAnalyzer
{
    bool Adjective::maybe(std::string_view s)
    {
      if (s.ends_with("ее"))
      {
        return true;
      }

      return false;
    }

    std::vector<std::unique_ptr<Adjective>> Adjective::createVariations(std::string_view s)
    {
      std::vector<std::unique_ptr<Adjective>> r;

      if (s.ends_with("ее"))
      {
        using namespace Morphology;
        auto root = s.substr(0, s.length() - 2);
        r.emplace_back(new Adjective(std::string(root), Case::accusative, Count::single, Gender::n));

        r.emplace_back(new Adjective(std::string(root), Case::nominative, Count::single, Gender::n));
      }

      return r;
    }

    std::optional<Relation> Adjective::relates(Word const& w) const
    {
      using namespace Morphology;
      using Utils::equal;

      if (auto n = dynamic_cast<Noun const*>(&w))
      {
        if (equal<Case, Gender, Count>(this, n))
        {
          return Relation::definition;
        }
      }

      if (auto p = dynamic_cast<Pronoun const*>(&w))
      {
        if (equal<Gender, Count>(this, p) && this->case_() == Case::nominative && p->case_() == Case::nominative)
        {
          return Relation::predicate;
        }
      }

      if (auto h = dynamic_cast<ShortAdjective const*>(&w))
      {
        if (this->case_() == Case::nominative && equal<Gender, Count>(this, h))
        {
          return Relation::predicate;
        }
      }

      return std::nullopt;
    }

    Adjective::operator std::string() const
    {
      using namespace Morphology;
      std::string r = _root;
      if ((_case == Case::nominative || _case == Case::accusative) && _count == Count::single && _gender == Gender::n)
      {
        r += "ее";
      }

      return r;
    }
}