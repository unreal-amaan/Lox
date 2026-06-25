#pragma once

#include "token.hpp"
#include <string>
#include <vector>

namespace lox {

class Scanner {
  std::string sourceCode;
  std::vector<Token> tokens;
    public:
      explicit Scanner(const std::string &source);
      std::vector<Token> scanTokens();
  };
}