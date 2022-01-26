#pragma once

#include <optional>
#include <memory>
#include <string>

namespace RussianLanguageAnalyzer
{
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

    virtual std::optional<Relation> relates(Word const&) const = 0;

    virtual operator std::string() const = 0;

    std::unique_ptr<Word> _child;
  };
}