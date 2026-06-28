#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

#include "token.hpp"
#include "tokenType.hpp"

namespace lox {

// Forward declaration of Lox class to reduce coupling and avoid circular
// dependencies. This allows Scanner to hold a reference to Lox without
// including the full Lox header, preventing unnecessary compilation
// dependencies and potential circular include issues.
class Lox;

class Scanner {
private:
  size_t start = 0;
  size_t current = 0;
  size_t lineNumber = 1;

  std::string
      sourceCode; // string that stores the sourceCode from the source file
  std::vector<Token> tokens; // container to store the scanned tokens

  Lox &loxInstance;

  const std::unordered_map<std::string, TokenType> keyWords = {
      {"and", TokenType::AND},       {"class", TokenType::CLASS},
      {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
      {"fun", TokenType::FUN},       {"for", TokenType::FOR},
      {"if", TokenType::IF},         {"nil", TokenType::NIL},
      {"or", TokenType::OR},         {"print", TokenType::PRINT},
      {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
      {"this", TokenType::THIS},     {"true", TokenType::TRUE},
      {"var", TokenType::VAR},       {"while", TokenType::WHILE},
  };

  char advance(); // this function returns the character to be scanned and moves
                  // the current pointer to next character
  char peek(); // the peek(i.e., lookahead) function only returns the character
               // present next to the character that is being currently scanned.
  char peekNext(); // +2 lookahead

  bool isAtEnd() const;  //  check for end of the sourcecode

  void
  addToken(TokenType type,
           Literal literal); // addToken function is responsible for filling the
                             // tokens vectors with the Token information.
  bool match(const char expected); // the match looks at the next character to
                                   // determine if it is a two character token
                                   // like(>=, ==, <=, +=......)

  void scanString();     // function to consume string literals.
  void scanNumber();     // function to consume number literals.
  void scanIdentifier(); // function to consume identifiers.

  
  public:
  explicit Scanner(const std::string &source, Lox &lox);
  // the scanTokens function scans all the lexemes and map them to their
  // corresponding tokentype as defined in the enum class TokenType
  std::vector<Token> scanTokens();
  void printTokens();   // function to print the scanned tokens
};

} // namespace lox