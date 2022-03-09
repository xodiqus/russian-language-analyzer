#include <assert.h>

#include "Sentence.h"
#include "Utils.h"

#include "Word.h"
#include "Noun.h"
#include "Adjective.h"
#include "Pronoun.h"
#include "Verb.h"
#include "Adverb.h"
#include "ShortAdjective.h"

namespace RussianLanguageAnalyzer
{
  Sentence::Sentence(std::string_view s)
  {
    auto words = Utils::split(s, " ");
    std::vector<std::vector<std::unique_ptr<Word>>> variations(words.size());

    for (std::size_t i = 0; i < words.size(); ++i)
    {
      variations[i] = determineVariations(words[i]);
    }

    for (auto&& v : variations)
    {
      if (auto _ = dynamic_cast<Verb const*>(v[0].get()))
      {
        _predicate = std::move(v[0]);
        break;
      }
    }

    for (auto&& v : variations)
    {
      for (auto&& w : v)
      {
        if (w == nullptr) continue;

        if (_predicate->relates(*w) == Relation::predicate
          && w->relates(*_predicate) == Relation::subject)
        {
          _subject = std::move(w);
        }
        else if (_predicate->relates(*w) == Relation::predicate
              && w->relates(*_predicate) == Relation::object)
        {
          _object = std::move(w);
        } 
        else if (w->relates(*_predicate) == Relation::circumstance)
        {
          _predicate->child(w.release());
        }
      }
    }

    for (auto&& v : variations)
    {
      for (auto&& w : v)
      {
        if (w == nullptr) continue;

        if (w->relates(*_object) == Relation::definition)
        {
          _object->child(w.release());
        }
      }
    }
  }

  std::vector<std::unique_ptr<Word>> Sentence::determineVariations(std::string_view s)
  {
    std::vector<std::unique_ptr<Word>> r;

    constexpr auto emplace_back = [](auto& r, auto && words) 
    {
      for (auto && w : words)
      {
        r.emplace_back(std::move(w));
      }
    };

    if (Noun::maybe(s))
    {
      emplace_back(r, Noun::createVariations(s));
    }

    if (Adjective::maybe(s))
    {
      emplace_back(r, Adjective::createVariations(s));
    }

    if (ShortAdjective::maybe(s))
    {
      r.emplace_back(new ShortAdjective(s));
    }

    if (Pronoun::maybe(s))
    {
      r.emplace_back(new Pronoun(s));
    }

    if (Verb::maybe(s))
    {
      r.emplace_back(new Verb(s));
    }

    if (Adverb::maybe(s))
    {
      r.emplace_back(new Adverb(s));
    }

    return r;
  }
}
