#pragma once

#include "tokenType.hpp"
#include <cstddef>
#include <string>
#include <variant>

namespace lox {

using LiteralValue = std::variant<std::nullptr_t, double, bool, std::string>;

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const LiteralValue literal;
  const std::size_t line;

  Token(TokenType type, std::string lexeme, LiteralValue literal, std::size_t line);
};

std::ostream &operator<<(std::ostream &os, const Token &token);

} // namespace lox