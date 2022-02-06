
#include <typeindex>
#include <map>
#include <functional>
#include <assert.h>

#include "Word.h"

#include "Noun.h"
#include "Verb.h"

#include "Adjective.h"
#include "ShortAdjective.h"
#include "Adverb.h"

#include "Pronoun.h"

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

  std::optional<Relation> Word::relates(Word const& w) const
  {
    using f = std::function <std::optional<Relation> (Word const*, Word const*)>;

    static const std::map<std::type_index, f> typeids 
    { 
      { typeid(Noun),             [](auto t, auto w) { auto d = dynamic_cast<Noun           const*>(w); assert(d != nullptr); return t->relates(*d); }},
      { typeid(Pronoun),          [](auto t, auto w) { auto d = dynamic_cast<Pronoun        const*>(w); assert(d != nullptr); return t->relates(*d); }},
      { typeid(Verb),             [](auto t, auto w) { auto d = dynamic_cast<Verb           const*>(w); assert(d != nullptr); return t->relates(*d); }},
      { typeid(Adverb),           [](auto t, auto w) { auto d = dynamic_cast<Adverb         const*>(w); assert(d != nullptr); return t->relates(*d); }},
      { typeid(Adjective),        [](auto t, auto w) { auto d = dynamic_cast<Adjective      const*>(w); assert(d != nullptr); return t->relates(*d); }},
      { typeid(ShortAdjective),   [](auto t, auto w) { auto d = dynamic_cast<ShortAdjective const*>(w); assert(d != nullptr); return t->relates(*d); }},
      // ...
    };

    auto const& type = w.get_typeid();

    auto const it = typeids.find(type);

    if (it != typeids.cend())
    {
      return it->second(this, &w);
    }

    assert(it != typeids.cend());
    return std::nullopt;
  }

  std::optional<Relation> Word::relates(Noun            const&) const { return std::nullopt; }
  std::optional<Relation> Word::relates(Verb            const&) const { return std::nullopt; }
  std::optional<Relation> Word::relates(Adjective       const&) const { return std::nullopt; }
  std::optional<Relation> Word::relates(Adverb          const&) const { return std::nullopt; }
  std::optional<Relation> Word::relates(ShortAdjective  const&) const { return std::nullopt; }
  std::optional<Relation> Word::relates(Pronoun         const&) const { return std::nullopt; }
}
