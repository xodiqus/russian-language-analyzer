
#include <memory>
#include <map>
#include <assert.h>

#include "Noun.h"
#include "Verb.h"
#include "Adjective.h"
#include "ShortAdjective.h"

#include "Utils.h"


namespace RussianLanguageAnalyzer
{
  Noun::Noun()
  {
  }

  Noun::Noun(Noun const& n)
    :_word(n._word), _case(n._case), _count(n._count), _gender(_gender)
  {
  }

  Noun::Noun(Noun &&n)
    : _word(std::move(n._word)), _case(n._case), _count(n._count), _gender(_gender)
  {
  }

  Noun& Noun::operator=(Noun const& n)
  {
    _word = n._word;
    _case = n._case;
    _count = n._count;
    _gender = n._gender;

    return *this;
  }

  Noun& Noun::operator=(Noun &&n)
  {
    _word = std::move(n._word);
    _case = n._case;
    _count = n._count;
    _gender = n._gender;

    return *this;
  }

  bool Noun::maybe(std::string_view s)
  {
    if (s.ends_with("��"))
    {
      return true;
    }

    return false;
  }

  std::vector<std::unique_ptr<Noun>> Noun::createVariations(std::string_view s)
  {
    using namespace Morphology;

    std::vector<std::unique_ptr<Noun>> r;

    if (s.ends_with("��"))
    {
      r.emplace_back(new Noun(std::string(s), Case::nominative, Count::single, Gender::n));

      r.emplace_back(new Noun(std::string(s), Case::accusative, Count::single, Gender::n));
    }

    if (s.ends_with("�"))
    {
      r.emplace_back(new Noun(std::string(s), Case::nominative, Count::single, Gender::n));

      r.emplace_back(new Noun(std::string(s), Case::accusative, Count::single, Gender::n));
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

    std::string r;
    std::map<Case, const char*> const* ends = nullptr;

    switch (count())
    {
    case Count::single:
    {
      switch (gender())
      {
        case Gender::n:
          if (bool o_end = _word.ends_with("�"))
          {
            if (o_end)
              r = _word.substr(0, _word.length() - 1);
            else
              r = _word;

            static const std::map<Case, const char*> e{
              { Case::nominative,     "�" },
              { Case::genitive,       "�" },
              { Case::dative,         "�" },
              { Case::accusative,     "�" },
              { Case::instrumental,   "��" },
              { Case::prepositional,  "�" },
            };

            ends = &e;
          }
          else if (_word.ends_with("��"))
          {
            r = _word.substr(0, _word.length() - 2);

            static const std::map<Case, const char*> e{
              { Case::nominative,      "��" },
              { Case::genitive,        "��" },
              { Case::dative,          "��" },
              { Case::accusative,      "��" },
              { Case::instrumental,    "���" },
              { Case::prepositional,   "��" },
            };

            ends = &e;
          }
          break;

        case Gender::m:
        {
          r = _word;

          static const std::map<Case, const char*> e{
              { Case::nominative,     "" },
              { Case::genitive,       "�" },
              { Case::dative,         "�" },
              { Case::accusative,     "" },
              { Case::instrumental,   "��" },
              { Case::prepositional,  "�" },
          };

          ends = &e;
        }
      }
    }
    case Count::plural:
      break;
    }

    assert(ends != nullptr);

    return r + ends->find(case_())->second;
  }

  void Noun::set(Morphology::Case c)
  {
    _case = c;
  }
}