// Copyright 2023, University of Freiburg,
// Chair of Algorithms and Data Structures.
//
// Authors: Björn Buchhold <buchhold@gmail.com>
//          Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//          Hannah Bast <bast@cs.uni-freiburg.de>

#pragma once

#include <limits>
#include <stdexcept>
#include <string>

#include "util/MemorySize/MemorySize.h"
#include "util/Parameters.h"
#include "util/ParseableDuration.h"

// For access to `memorySize` literals.
using namespace ad_utility::memory_literals;

static const ad_utility::MemorySize DEFAULT_MEMORY_LIMIT_INDEX_BUILDING = 5_GB;
static const ad_utility::MemorySize STXXL_DISK_SIZE_INDEX_BUILDER = 1_GB;

static constexpr ad_utility::MemorySize DEFAULT_MEM_FOR_QUERIES = 4_GB;

static const size_t MAX_NOF_ROWS_IN_RESULT = 1'000'000;
static const size_t MIN_WORD_PREFIX_SIZE = 4;
static const char PREFIX_CHAR = '*';
static const size_t MAX_NOF_NODES = 64;
static const size_t MAX_NOF_FILTERS = 64;

static const size_t BUFFER_SIZE_RELATION_SIZE = 1'000'000'000;
static const size_t BUFFER_SIZE_DOCSFILE_LINE = 100'000'000;
static const size_t DISTINCT_LHS_PER_BLOCK = 10'000;
static const size_t USE_BLOCKS_INDEX_SIZE_TRESHOLD = 20'000;

static const size_t TEXT_PREDICATE_CARDINALITY_ESTIMATE = 1'000'000'000;
static const size_t TEXT_LIMIT_DEFAULT = std::numeric_limits<size_t>::max();

static const size_t GALLOP_THRESHOLD = 1000;

static const char INTERNAL_PREDICATE_PREFIX_NAME[] = "ql";

static const std::string INTERNAL_PREDICATE_PREFIX =
    "http://qlever.cs.uni-freiburg.de/builtin-functions/";

// Return a IRI of the form
// `<http://qlever.cs.uni-freiburg.de/builtin-functions/concatenationOfSuffixes>`
constexpr auto makeInternalIri = [](auto&&... suffixes) {
  return absl::StrCat("<", INTERNAL_PREDICATE_PREFIX, suffixes..., ">");
};
static const std::string INTERNAL_ENTITIES_URI_PREFIX =
    absl::StrCat("<", INTERNAL_PREDICATE_PREFIX);
static const std::string INTERNAL_PREDICATE_PREFIX_IRI = makeInternalIri("");
static const std::string CONTAINS_ENTITY_PREDICATE =
    makeInternalIri("contains-entity");
static const std::string CONTAINS_WORD_PREDICATE =
    makeInternalIri("contains-word");

static const std::string INTERNAL_TEXT_MATCH_PREDICATE =
    makeInternalIri("text");
static const std::string HAS_PREDICATE_PREDICATE =
    makeInternalIri("has-predicate");
static const std::string HAS_PATTERN_PREDICATE = makeInternalIri("has-pattern");
static constexpr std::pair<std::string_view, std::string_view> GEOF_PREFIX = {
    "geof:", "<http://www.opengis.net/def/function/geosparql/"};
static constexpr std::pair<std::string_view, std::string_view> MATH_PREFIX = {
    "math:", "<http://www.w3.org/2005/xpath-functions/math#"};

static const std::string INTERNAL_VARIABLE_PREFIX =
    "?_QLever_internal_variable_";

static constexpr std::string_view TEXTSCORE_VARIABLE_PREFIX = "?ql_textscore_";
static constexpr std::string_view ENTITY_VARIABLE_PREFIX = "?ql_entity_";
static constexpr std::string_view SCORE_VARIABLE_PREFIX = "?ql_score_";
static constexpr std::string_view MATCHINGWORD_VARIABLE_PREFIX =
    "?ql_matchingword_";

// For anonymous nodes in Turtle.
static const std::string ANON_NODE_PREFIX = "QLever-Anon-Node";

static const std::string LANGUAGE_PREDICATE = makeInternalIri("langtag");

// TODO<joka921> Move them to their own file, make them strings, remove
// duplications, etc.
static const char XSD_DATETIME_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#dateTime";
static const char XSD_DATE_TYPE[] = "http://www.w3.org/2001/XMLSchema#date";
static const char XSD_GYEAR_TYPE[] = "http://www.w3.org/2001/XMLSchema#gYear";
static const char XSD_GYEARMONTH_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#gYearMonth";

constexpr inline char XSD_INT_TYPE[] = "http://www.w3.org/2001/XMLSchema#int";
static const char XSD_INTEGER_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#integer";
static const char XSD_FLOAT_TYPE[] = "http://www.w3.org/2001/XMLSchema#float";
static const char XSD_DOUBLE_TYPE[] = "http://www.w3.org/2001/XMLSchema#double";
constexpr inline char XSD_DECIMAL_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#decimal";

static const char XSD_NON_POSITIVE_INTEGER_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#nonPositiveInteger";
static const char XSD_NEGATIVE_INTEGER_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#negativeInteger";
static const char XSD_LONG_TYPE[] = "http://www.w3.org/2001/XMLSchema#long";
static const char XSD_SHORT_TYPE[] = "http://www.w3.org/2001/XMLSchema#short";
static const char XSD_BYTE_TYPE[] = "http://www.w3.org/2001/XMLSchema#byte";
static const char XSD_NON_NEGATIVE_INTEGER_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#nonNegativeInteger";
static const char XSD_UNSIGNED_LONG_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#unsignedLong";
static const char XSD_UNSIGNED_INT_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#unsignedInt";
static const char XSD_UNSIGNED_SHORT_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#unsignedShort";
static const char XSD_UNSIGNED_BYTE_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#unsignedByte";
static const char XSD_POSITIVE_INTEGER_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#positiveInteger";
constexpr inline char XSD_BOOLEAN_TYPE[] =
    "http://www.w3.org/2001/XMLSchema#boolean";
static const char RDF_PREFIX[] = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
static const char VALUE_DATE_TIME_SEPARATOR[] = "T";
static const int DEFAULT_NOF_VALUE_INTEGER_DIGITS = 50;
static const int DEFAULT_NOF_VALUE_EXPONENT_DIGITS = 20;
static const int DEFAULT_NOF_VALUE_MANTISSA_DIGITS = 30;
static const int DEFAULT_NOF_DATE_YEAR_DIGITS = 19;

static const std::string INTERNAL_VOCAB_SUFFIX = ".vocabulary.internal";
static const std::string EXTERNAL_VOCAB_SUFFIX = ".vocabulary.external";
static const std::string MMAP_FILE_SUFFIX = ".meta";
static const std::string CONFIGURATION_FILE = ".meta-data.json";
static const std::string PREFIX_FILE = ".prefixes";

static const std::string ERROR_IGNORE_CASE_UNSUPPORTED =
    "Key \"ignore-case\" is no longer supported. Please remove this key from "
    "your settings.json and rebuild your index. You can optionally specify the "
    "\"locale\" key, otherwise \"en.US\" will be used as default";
static const std::string WARNING_ASCII_ONLY_PREFIXES =
    "You specified \"ascii-prefixes-only = true\", which enables faster "
    "parsing for well-behaved TTL files";
// " but only works correctly if there are no escape sequences in "
// "prefixed names (e.g., rdfs:label\\,el is not allowed), no multiline "
// "literals, and the regex \". *\\n\" only matches at the end of a triple. "
// "Most Turtle files fulfill these properties (e.g. that from Wikidata), "
// "but not all";

static const std::string WARNING_PARALLEL_PARSING =
    "You specified \"parallel-parsing = true\", which enables faster parsing "
    "for TTL files that don't include multiline literals with unescaped "
    "newline characters and that have newline characters after the end of "
    "triples.";
static const std::string LOCALE_DEFAULT_LANG = "en";
static const std::string LOCALE_DEFAULT_COUNTRY = "US";
static constexpr bool LOCALE_DEFAULT_IGNORE_PUNCTUATION = false;

// Constants for the range of valid compression prefixes
// all ASCII- printable characters are left out.
// when adding more special characters to the vocabulary make sure to leave out
// \n since the vocabulary is stored in a text file line by line.
// All prefix codes have a most significant bit of 1. This means the prefix
// codes are never valid UTF-8 and thus it is always able to determine, whether
// this vocabulary was compressed or not.
static constexpr uint8_t MIN_COMPRESSION_PREFIX = 129;
static constexpr uint8_t NUM_COMPRESSION_PREFIXES = 126;
// if this is the first character of a compressed string, this means that no
// compression has been applied to  a word
static const uint8_t NO_PREFIX_CHAR =
    MIN_COMPRESSION_PREFIX + NUM_COMPRESSION_PREFIXES;

// When initializing a sort performance estimator, at most this percentage of
// the number of triples in the index is being sorted at once.
static constexpr size_t PERCENTAGE_OF_TRIPLES_FOR_SORT_ESTIMATE = 5;

// When asked to make room for X ids in the cache, actually make room for X
// times this factor.
static constexpr size_t MAKE_ROOM_SLACK_FACTOR = 2;

// The version of the binary format of the pattern files. Has to be increased,
// when this format is changed.
static constexpr uint32_t PATTERNS_FILE_VERSION = 1;

// The maximal number of columns an `IdTable` (an intermediate result of
// query evaluation) may have to be able to use the more efficient `static`
// implementation (For details see `IdTable.h`, `CallFixedSize.h` and the
// usage of `CALL_FIXED_SIZE` in the various subclasses of `Operation`.
// Increasing this number improves the runtime for operations on tables with
// more columns, but also increases compile times because more templates
// have to be instantiated. It might also be necessary to increase some internal
// compiler limits for the evaluation of constexpr functions and templates.
static constexpr int DEFAULT_MAX_NUM_COLUMNS_STATIC_ID_TABLE = 5;

// Interval in which an enabled watchdog would check if
// `CancellationHandle::throwIfCancelled` is called regularly.
constexpr std::chrono::milliseconds DESIRED_CANCELLATION_CHECK_INTERVAL{50};

inline auto& RuntimeParameters() {
  using ad_utility::detail::parameterShortNames::Bool;
  using ad_utility::detail::parameterShortNames::Double;
  using ad_utility::detail::parameterShortNames::DurationParameter;
  using ad_utility::detail::parameterShortNames::MemorySizeParameter;
  using ad_utility::detail::parameterShortNames::SizeT;
  // NOTE: It is important that the value of the static variable is created by
  // an immediately invoked lambda, otherwise we get really strange segfaults on
  // Clang 16 and 17.
  // TODO<joka921> Figure out whether this is a bug in Clang or whether we
  // clearly misunderstand something about static initialization.
  static ad_utility::Parameters params = []() {
    using namespace std::chrono_literals;
    auto ensureStrictPositivity = [](auto&& parameter) {
      parameter.setParameterConstraint(
          [](std::chrono::seconds value, std::string_view parameterName) {
            if (value <= 0s) {
              throw std::runtime_error{absl::StrCat(
                  "Parameter ", parameterName,
                  " must be strictly positive, was ", value.count(), "s")};
            }
          });
      return AD_FWD(parameter);
    };
    return ad_utility::Parameters{
        // If the time estimate for a sort operation is larger by more than this
        // factor than the remaining time, then the sort is canceled with a
        // timeout exception.
        Double<"sort-estimate-cancellation-factor">{3.0},
        SizeT<"cache-max-num-entries">{1000},
        MemorySizeParameter<"cache-max-size">{30_GB},
        MemorySizeParameter<"cache-max-size-single-entry">{5_GB},
        SizeT<"lazy-index-scan-queue-size">{20},
        SizeT<"lazy-index-scan-num-threads">{10},
        ensureStrictPositivity(
            DurationParameter<std::chrono::seconds, "default-query-timeout">{
                30s}),
        SizeT<"lazy-index-scan-max-size-materialization">{1'000'000},
        Bool<"use-group-by-hash-map-optimization">{false}};
  }();
  return params;
}

#ifdef _PARALLEL_SORT
static constexpr bool USE_PARALLEL_SORT = true;
#include <parallel/algorithm>
namespace ad_utility {
template <typename... Args>
auto parallel_sort(Args&&... args) {
  return __gnu_parallel::sort(std::forward<Args>(args)...);
}
using parallel_tag = __gnu_parallel::parallel_tag;

}  // namespace ad_utility

#else
static constexpr bool USE_PARALLEL_SORT = false;
namespace ad_utility {
template <typename... Args>
auto parallel_sort([[maybe_unused]] Args&&... args) {
  throw std::runtime_error(
      "Triggered the parallel sort although it was disabled. Please report to "
      "the developers!");
}
using parallel_tag = int;
}  // namespace ad_utility
#endif
static constexpr size_t NUM_SORT_THREADS = 4;
