#include "Utils.h"

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

  std::ostream& operator <<(std::ostream& out, RussianLanguageAnalyzer::Morphology::Case c)
  {
    using namespace RussianLanguageAnalyzer::Morphology;

    switch (c)
    {
    case Case::nominative: out << "именительный"; break;
    case Case::accusative: out << "винительный"; break;
    }

    return out;
  }

  std::ostream& operator <<(std::ostream& out, RussianLanguageAnalyzer::Morphology::Person p)
  {
    using namespace RussianLanguageAnalyzer::Morphology;

    switch (p)
    {
    case Person::first: out << "1-ое"; break;

    }

    return out;
  }

  std::ostream& operator <<(std::ostream& out, RussianLanguageAnalyzer::Morphology::Count c)
  {
    using namespace RussianLanguageAnalyzer::Morphology;

    switch (c)
    {
    case Count::single: out << "единственное"; break;
    case Count::plural: out << "множественное"; break;
    }

    return out;
  }

  std::ostream& operator <<(std::ostream& out, RussianLanguageAnalyzer::Morphology::Gender g)
  {
    using namespace RussianLanguageAnalyzer::Morphology;

    switch (g)
    {
    case Gender::n: out << "средний"; break;
    }

    return out;
  }

  std::ostream& operator <<(std::ostream& out, RussianLanguageAnalyzer::Morphology::Tense t)
  {
    using namespace RussianLanguageAnalyzer::Morphology;

    switch (t)
    {
    case Tense::present: out << "настоящие"; break;
    }

    return out;
  }
}