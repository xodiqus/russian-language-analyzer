#include "Word.h"

namespace RussianLanguageAnalyzer
{ 
  bool operator==(Word const& w, std::string_view s)
  {
    return !(s != w);
  }

  bool operator ==(std::string_view s, Word const& w)
  {
    return !(s != w);
  }

  bool operator!=(std::string_view s, Word const& w)
  {
      return static_cast<std::string>(w) != s;
  }

  bool operator!=(Word const& w, std::string_view s)
  {
    return s != w;
  }
}
