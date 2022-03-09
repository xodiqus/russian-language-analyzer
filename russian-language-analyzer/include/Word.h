#pragma once

#include <optional>
#include <memory>
#include <string_view>

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
    friend class Sentence;

  private:
    std::string _baseForm;
    std::unique_ptr<Word> _child;

  public:
    Word() = default;
    Word(std::string_view baseForm) noexcept;

    Word(Word&&)            noexcept = default;
    Word& operator=(Word&&) noexcept = default;

    virtual ~Word() noexcept = default;

            std::optional<Relation> relates(Word            const&) const;

    virtual std::optional<Relation> relates(Noun            const&) const;
    virtual std::optional<Relation> relates(Verb            const&) const;
    virtual std::optional<Relation> relates(Adjective       const&) const;
    virtual std::optional<Relation> relates(Adverb          const&) const;
    virtual std::optional<Relation> relates(ShortAdjective  const&) const;
    virtual std::optional<Relation> relates(Pronoun         const&) const;

  protected:
    std::string&       baseForm() noexcept;

  public:
    std::string const& baseForm() const noexcept;
    
    Word const* child() const;
    Word      * child();
  private:
    void        child(Word* w);

  public:
    virtual operator std::string() const = 0;

    virtual std::type_info const& get_typeid() const = 0;
  };

  bool operator ==(Word const&, std::string_view);
  bool operator ==(std::string_view, Word const&);
  bool operator !=(std::string_view, Word const&); 
  bool operator !=(Word const&, std::string_view);
}