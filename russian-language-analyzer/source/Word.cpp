#include "Word.h"

namespace RussianLanguageAnalyzer
{ 
  bool Word::operator==(std::string_view s) const
  {
    return this->operator std::string() == s;
  }

  bool operator ==(std::string_view s, Word const& w)
  {
    return w == s;
  }
}
