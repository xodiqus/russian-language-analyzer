
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
    : Word(n.baseForm()), _case(n._case), _count(n._count), _gender(_gender)
  {
  }

  Noun::Noun(Noun &&n)
    : Word(std::move(n.baseForm())), _case(n._case), _count(n._count), _gender(_gender)
  {
  }

  Noun& Noun::operator=(Noun const& n)
  {
    baseForm() = n.baseForm();
    _case = n._case;
    _count = n._count;
    _gender = n._gender;

    return *this;
  }

  Noun& Noun::operator=(Noun &&n)
  {
    baseForm() = std::move(n.baseForm());
    _case = n._case;
    _count = n._count;
    _gender = n._gender;

    return *this;
  }

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
    using namespace Morphology;

    std::vector<std::unique_ptr<Noun>> r;

    if (s.ends_with("ие"))
    {
      r.emplace_back(new Noun(std::string(s), Case::nominative, Count::single, Gender::n));

      r.emplace_back(new Noun(std::string(s), Case::accusative, Count::single, Gender::n));
    }

    if (s.ends_with("о"))
    {
      r.emplace_back(new Noun(std::string(s), Case::nominative, Count::single, Gender::n));

      r.emplace_back(new Noun(std::string(s), Case::accusative, Count::single, Gender::n));
    }

    return r;
  }

  std::optional<Relation> Noun::relates(ShortAdjective const& h) const
  {
    using namespace Utils;
    using namespace Morphology;

    if (equal<Count, Gender>(this, &h))
    {
      return Relation::subject;
    }

    return std::nullopt;
  }

  std::optional<Relation> Noun::relates(Verb const& v) const
  {
    using namespace Utils;
    using namespace Morphology;

    if (equal<Count>(&v, this) && this->case_() == Case::nominative && v.person() == Person::third)
    {
      return Relation::subject;
    }

    if (this->case_() == Case::accusative)
    {
      return Relation::object;
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
          if (bool o_end = baseForm().ends_with("о"))
          {
            if (o_end)
              r = baseForm().substr(0, baseForm().length() - 1);
            else
              r = baseForm();

            static const std::map<Case, const char*> e{
              { Case::nominative,     "о" },
              { Case::genitive,       "а" },
              { Case::dative,         "у" },
              { Case::accusative,     "о" },
              { Case::instrumental,   "ом" },
              { Case::prepositional,  "е" },
            };

            ends = &e;
          }
          else if (baseForm().ends_with("ие"))
          {
            r = baseForm().substr(0, baseForm().length() - 2);

            static const std::map<Case, const char*> e{
              { Case::nominative,      "ие" },
              { Case::genitive,        "ия" },
              { Case::dative,          "ию" },
              { Case::accusative,      "ие" },
              { Case::instrumental,    "ием" },
              { Case::prepositional,   "ии" },
            };

            ends = &e;
          }
          break;

        case Gender::m:
        {
          r = baseForm();

          static const std::map<Case, const char*> e{
              { Case::nominative,     "" },
              { Case::genitive,       "а" },
              { Case::dative,         "у" },
              { Case::accusative,     "" },
              { Case::instrumental,   "ом" },
              { Case::prepositional,  "е" },
          };

          ends = &e;
        }

        case Gender::f:
        {
          if (bool o_end = baseForm().ends_with("а"))
          {
             r = baseForm().substr(0, baseForm().length() - 1);

             static const std::map<Case, const char*> e{
              { Case::nominative,      "а" },
              { Case::genitive,        "и" },
              { Case::dative,          "е" },
              { Case::accusative,      "у" },
              { Case::instrumental,    "ой" },
              { Case::prepositional,   "е" },
             };

             ends = &e;
          }
        }
      }
    }
    
    case Count::plural:
    {
        switch (gender())
        {
        case Gender::m:
        {
            if (bool o_end = baseForm().ends_with("и"))
            {
                r = baseForm().substr(0, baseForm().length() - 1);

                static const std::map<Case, const char*> e{
               { Case::nominative,     "и" },
               { Case::genitive,       "ей" },
               { Case::dative,         "ам" },
               { Case::accusative,     "и" },
               { Case::instrumental,   "ами" },
               { Case::prepositional,  "ах" },
                };

                ends = &e;
                
                break;
            }
            else if (baseForm().ends_with("ы"))
            {
                r = baseForm().substr(0, baseForm().length() - 1);

                static const std::map<Case, const char*> e{
              { Case::nominative,     "ы" },
              { Case::genitive,       "" },
              { Case::dative,         "ам" },
              { Case::accusative,     "" },
              { Case::instrumental,   "ами" },
              { Case::prepositional,  "ах" },
                };

                ends = &e;
            }
        }
        case Gender::n:
        {
            if (bool o_end = baseForm().ends_with("а"))
            {
                r = baseForm().substr(0, baseForm().length() - 1);

                static const std::map<Case, const char*> e{
               { Case::nominative,     "а" },
               { Case::genitive,       "" },
               { Case::dative,         "ам" },
               { Case::accusative,     "а" },
               { Case::instrumental,   "ами" },
               { Case::prepositional,  "ах" },
                };

                ends = &e;
            }
        }
        case Gender::f:
        {
            if (bool o_end = baseForm().ends_with("я"))
            {
                r = baseForm().substr(0, baseForm().length() - 1);

                static const std::map<Case, const char*> e{
               { Case::nominative,     "я" },
               { Case::genitive,       "ев" },
               { Case::dative,         "ям" },
               { Case::accusative,     "я" },
               { Case::instrumental,   "ями" },
               { Case::prepositional,  "ях" },
                };

                ends = &e;
            }
            else if (bool o_end = baseForm().ends_with("и"))
            {
                r = baseForm().substr(0, baseForm().length() - 1);

                static const std::map<Case, const char*> e{
               { Case::nominative,     "и" },
               { Case::genitive,       "" },
               { Case::dative,         "ам" },
               { Case::accusative,     "и" },
               { Case::instrumental,   "ами" },
               { Case::prepositional,  "ах" },
                };

                ends = &e;
            }
        }
        }
    }
    }

    return r + (ends != nullptr ? ends->find(case_())->second : "");
  }

  void Noun::set(Morphology::Case c)
  {
    _case = c;
  }

  std::type_info const& Noun::get_typeid() const 
  { 
    return typeid(Noun);
  }
}