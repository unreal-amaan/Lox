#pragma once

#include <string>
#include <vector>

#include "token.hpp"
#include "tokenType.hpp"

namespace lox {

class Scanner {
private:
  size_t start = 0;
  size_t current = 0;
  int lineNumber = 1;

  std::string sourceCode;
  std::vector<Token> tokens;

  char advance(); // this function returns the character to be scanned and moves
                  // the current pointer to next character
  char peek(); // the peek function only returns the character present
                    // next to the character that is being currently scanned.
  void
  addToken(TokenType type,
           Literal literal); // addToken function is responsible for filling the
                             // tokens vectors with the Token information.
  bool match(const char expected); // the match looks at the next character to determine if it is a two character token like(>=, ==, <=, +=......)
  
public:
  explicit Scanner(const std::string &source);
  // the scanTokens function scans all the lexemes and map them to their
  // corresponding tokentype as defined in the enum class TokenType
  std::vector<Token> scanTokens();
};

} // namespace lox