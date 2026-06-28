#include "token.hpp"
#include <ostream>
#include <variant>
#include <type_traits>

lox::Token::Token(TokenType type, std::string lexeme, Literal literal,
                  std::size_t line)
    : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)),
      line(line) {}

std::ostream &lox::operator<<(std::ostream &os, const lox::Token &token) {
  os << token.type << " " << token.lexeme << " ";

  std::visit(
      [&os](const auto &val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, std::nullptr_t>) {
          os << "nil";
        } else if constexpr (std::is_same_v<T, bool>) {
          os << (val ? "true" : "false");
        } else {
          os << val;
        }
      },
      token.literal);

  return os;
}