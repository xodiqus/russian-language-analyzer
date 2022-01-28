#include <assert.h>

#include "Utils.h"

#include "Noun.h"


namespace RussianLanguageAnalyzer
{

namespace Utils
{
  std::vector<std::string_view> split(std::string_view s, std::string_view d)
  {
    std::vector<std::string_view> r;
    std::size_t offset = 0;
    do
    {
      offset = s.find(d);
      r.emplace_back(s.substr(0, offset));
      s = s.substr(offset + d.length());
    } while (s.find(d) != std::numeric_limits<std::size_t>::max());

    r.emplace_back(s);

    return r;
  }
}

namespace Morphology
{
  std::string_view to_string(Case c)
  {
    switch (c)
    {
    case Case::nominative: return "именительный"; 
    case Case::accusative: return "винительный"; 
    }

    assert(false);
    return "";
  }

  std::string_view to_string(Person p)
  {
    switch (p)
    {
    case Person::first: return "1-ое";
    }

    assert(false);
    return "";
  }

  std::string_view to_string(Count c)
  {
    switch (c)
    {
    case Count::single: return "единственное"; 
    case Count::plural: return "множественное"; 
    }

    assert(false);
    return "";
  }

  std::string_view to_string(Gender g)
  {
    switch (g)
    {
    case Gender::n: return "средний"; 
    }

    assert(false);
    return "";
  }

  std::string_view to_string(Tense t)
  {
    switch (t)
    {
    case Tense::present: return "настоящие"; 
    }

    assert(false);
    return "";
  }

  std::ostream& operator <<(std::ostream& out, Case c)
  {
    return out << to_string(c);
  }

  std::ostream& operator <<(std::ostream& out, Person p)
  {
    return out << to_string(p);
  }

  std::ostream& operator <<(std::ostream& out, Count c)
  {
    return out << to_string(c);
  }

  std::ostream& operator <<(std::ostream& out, Gender g)
  {
    return out << to_string(g);
  }

  std::ostream& operator <<(std::ostream& out, Tense t)
  {
    return out << to_string(t);
  }
}

  std::ostream& operator<<(std::ostream& out, Word const& w)
  {
    return out << static_cast<std::string>(w);
  }
}