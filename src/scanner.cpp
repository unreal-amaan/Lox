#include "scanner.hpp"
#include "token.hpp"
#include <iterator>
#include <vector>

lox::Scanner::Scanner(const std::string &source) { this->sourceCode = source; }

std::vector<lox::Token> lox::Scanner::scanTokens() {
  // std::cout << "************Source Code************" << std::endl;
  // std::cout << sourceCode << std::endl;

  while (current < sourceCode.length()) {
    char c = advance();
    switch (c) {}
  }

  return tokens;
}

char lox::Scanner::advance() { return sourceCode[current++]; }

char lox::Scanner::peek() {
  if (current >= sourceCode.length()) {
    return '\0';
  }
  return sourceCode[current];
}

bool lox::Scanner::match(const char expected) {
  if (current >= sourceCode.length() || sourceCode[current] != expected)
    return false;
  current++;
  return true;
}

void lox::Scanner::addToken(TokenType type, Literal literal) {
  
}