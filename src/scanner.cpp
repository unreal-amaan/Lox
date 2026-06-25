#include "scanner.hpp"
#include "token.hpp"
#include <iostream>
#include <vector>

lox::Scanner::Scanner(const std::string &source) { this->sourceCode = source; }

std::vector<lox::Token> lox::Scanner::scanTokens() {
  std::cout << "************Source Code************" << std::endl;
  std::cout << sourceCode << std::endl;
  return tokens;
}