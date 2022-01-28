#pragma once

#include <vector>
#include <string_view>
#include <ostream>

#include "Word.h"

namespace RussianLanguageAnalyzer
{

namespace Utils
{
  std::vector<std::string_view> split(std::string_view s, std::string_view d);

  template <class T, class ...Args>
  struct equal
  {
    operator bool() const { return _result; }

    template<class W1, class W2> equal(W1&& w1, W2&& w2)
      : _result(equal<T      >(std::forward<W1>(w1), std::forward<W2>(w2))
        && equal<Args...>(std::forward<W1>(w1), std::forward<W2>(w2))) {    }

  protected:
    equal(bool r) : _result(r) {}
    bool _result;
  };

  template <>
  struct equal<RussianLanguageAnalyzer::Morphology::Gender> : equal<void>
  {
    template<class W1, class W2> equal(W1&& w1, W2&& w2) : equal<void>(w1->gender() == w2->gender()) {    }
  };

  template <>
  struct equal<RussianLanguageAnalyzer::Morphology::Count> : equal<void>
  {
    template<class W1, class W2> equal(W1&& w1, W2&& w2) : equal<void>(w1->count() == w2->count()) {    }
  };

  template <>
  struct equal<RussianLanguageAnalyzer::Morphology::Case> : equal<void>
  {
    template<class W1, class W2> equal(W1&& w1, W2&& w2) : equal<void>(w1->case_() == w2->case_()) {    }
  };

  template <>
  struct equal<RussianLanguageAnalyzer::Morphology::Person> : equal<void>
  {
    template<class W1, class W2> equal(W1&& w1, W2&& w2) : equal<void>(w1->person() == w2->person()) {    }
  };
}

namespace Morphology 
{
  std::string_view to_string(Case);
  std::string_view to_string(Person);
  std::string_view to_string(Count);
  std::string_view to_string(Gender);
  std::string_view to_string(Tense);

  std::ostream& operator <<(std::ostream& out, Case);
  std::ostream& operator <<(std::ostream& out, Person);
  std::ostream& operator <<(std::ostream& out, Count);
  std::ostream& operator <<(std::ostream& out, Gender);
  std::ostream& operator <<(std::ostream& out, Tense);
}

  std::ostream& operator <<(std::ostream&, Word const&);
};

