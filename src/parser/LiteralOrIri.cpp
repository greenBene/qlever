// Copyright 2023, University of Freiburg,
//                 Chair of Algorithms and Data Structures.
// Author: Benedikt Maria Beckermann <benedikt.beckermann@dagstuhl.de>

#include "LiteralOrIri.h"

#include <algorithm>

// __________________________________________
LiteralOrIri::LiteralOrIri(Iri iri) : data_{std::move(iri)} {}

// __________________________________________
LiteralOrIri::LiteralOrIri(Literal literal) : data_{std::move(literal)} {}

// __________________________________________
bool LiteralOrIri::isIri() const { return std::holds_alternative<Iri>(data_); }

// __________________________________________
Iri& LiteralOrIri::getIri() {
  if (!isIri()) {
    AD_THROW(
        "LiteralOrIri object does not contain an Iri object and thus "
        "cannot return it");
  }
  return std::get<Iri>(data_);
}

// __________________________________________
NormalizedStringView LiteralOrIri::getIriContent() {
  return getIri().getContent();
}

// __________________________________________
bool LiteralOrIri::isLiteral() const {
  return std::holds_alternative<Literal>(data_);
}

// __________________________________________
Literal& LiteralOrIri::getLiteral() {
  if (!isLiteral()) {
    AD_THROW(
        "LiteralOrIri object does not contain an Literal object and "
        "thus cannot return it");
  }
  return std::get<Literal>(data_);
}

// __________________________________________
bool LiteralOrIri::hasLanguageTag() { return getLiteral().hasLanguageTag(); }

// __________________________________________
bool LiteralOrIri::hasDatatype() { return getLiteral().hasDatatype(); }

// __________________________________________
NormalizedStringView LiteralOrIri::getLiteralContent() {
  return getLiteral().getContent();
}

// __________________________________________
NormalizedStringView LiteralOrIri::getLanguageTag() {
  return getLiteral().getLanguageTag();
}

// __________________________________________
NormalizedStringView LiteralOrIri::getDatatype() {
  return getLiteral().getDatatype();
}

// __________________________________________
std::string LiteralOrIri::toRdf() {
  if (isIri()) {
    return getIri().toRdf();
  } else if (isLiteral()) {
    return getLiteral().toRdf();
  } else {
    AD_THROW("LiteralOrIri value is neither literal or iri");
  }
}

// __________________________________________
LiteralOrIri fromStringToLiteral(std::string_view input, std::string_view c) {
  auto pos = input.find(c, c.length());
  if (pos == 0) {
    AD_THROW("Cannot create LiteralOrIri from the input " + input +
             " because of missing or invalid closing quote character");
  }

  std::string_view content = input.substr(c.length(), pos - c.length());

  // No language tag or datatype
  if (pos == input.length() - c.length()) {
    return LiteralOrIri(Literal(fromStringUnsafe(content)));
  }

  std::string_view suffix =
      input.substr(pos + c.length(), input.length() - pos - c.length());

  if (suffix.starts_with("@")) {
    std::string_view languageTag = suffix.substr(1, suffix.length() - 1);
    auto literal =
        Literal(fromStringUnsafe(content), fromStringUnsafe(languageTag),
                LiteralDescriptor::LANGUAGE_TAG);
    return LiteralOrIri(literal);
  }
  if (suffix.starts_with("^^")) {
    std::string_view datatype = suffix.substr(2, suffix.length() - 2);
    auto literal =
        Literal(fromStringUnsafe(content), fromStringUnsafe(datatype),
                LiteralDescriptor::DATATYPE);
    return LiteralOrIri(literal);
  }
  AD_THROW("Cannot create LiteralOrIri from the input " + input +
           "because of invalid suffix.");
}

// __________________________________________
LiteralOrIri LiteralOrIri::parseRdf(std::string_view input) {
  if (input.starts_with("<") && input.ends_with(">")) {
    std::string_view content = input.substr(1, input.size() - 2);
    if (auto pos =
            content.find_first_of(R"(<>" {}|\^`)", 0) != std::string::npos) {
      AD_THROW("Iri " + input + " contains invalid character " +
               input.substr(pos, 1) + ".");
    }
    return LiteralOrIri(Iri(fromStringUnsafe(content)));
  }

  else if (input.starts_with(R"(""")"))
    return fromStringToLiteral(input, R"(""")");
  else if (input.starts_with("'''"))
    return fromStringToLiteral(input, "'''");
  else if (input.starts_with('"'))
    return fromStringToLiteral(input, "\"");
  else if (input.starts_with('\''))
    return fromStringToLiteral(input, "\'");

  AD_THROW("Cannot create LiteralOrIri from the input " + input);
}
