#pragma once

#include <optional>
#include <memory>
#include <string>

namespace RussianLanguageAnalyzer
{
  class Noun;
  class Adjective;
  class ShortAdjective;
  class Verb;
  class Adverb;
  class Pronoun;

  namespace Morphology
  {
    enum class Case { nominative, dative, accusative, instrumental, prepositional, genitive };
    enum class Count { single, plural };
    enum class Gender { m, n, f };
    enum class Tense { past, present, future };
    enum class Person { first, second, third };
    enum class Kind { perfect, imperfect };
  }

  enum class Relation { subject, predicate, object, definition, circumstance };

  class Word
  {
  public:
    Word(Word* w = nullptr) : _child(w) {  }

    virtual ~Word() {}

            std::optional<Relation> relates(Word            const&) const;

    virtual std::optional<Relation> relates(Noun            const&) const;
    virtual std::optional<Relation> relates(Verb            const&) const;
    virtual std::optional<Relation> relates(Adjective       const&) const;
    virtual std::optional<Relation> relates(Adverb          const&) const;
    virtual std::optional<Relation> relates(ShortAdjective  const&) const;
    virtual std::optional<Relation> relates(Pronoun         const&) const;

    virtual operator std::string() const = 0;

    virtual std::type_info const& get_typeid() const = 0;

    std::unique_ptr<Word> _child;
  };

  bool operator ==(Word const&, std::string_view);
  bool operator ==(std::string_view, Word const&);
  bool operator !=(std::string_view, Word const&); 
  bool operator !=(Word const&, std::string_view);
}