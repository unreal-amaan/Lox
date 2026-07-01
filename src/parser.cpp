
#include "parser.hpp"
#include "expr.hpp"
#include "token.hpp"
#include "tokenType.hpp"
#include <memory>
#include <utility>
#include <vector>
lox::Parser::Parser(std::vector<lox::Token>& scannedTokens)
    : scannedTokens(scannedTokens) {}

std::unique_ptr<lox::Expr> lox::Parser::expression() {
  return lox::Parser::equality();
}

std::unique_ptr<lox::Expr> lox::Parser::equality() {
  std::unique_ptr<Expr> expr = comparison();

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
    Token op = previous();
    std::unique_ptr<Expr> right = comparison();
    expr = std::make_unique<Binary>(std::move(expr), op, std::move(expr));
  }
  return expr;
}

std::unique_ptr<lox::Expr> lox::Parser::comparison() {
  std::unique_ptr<Expr> expr = term();

  while(match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
    Token op = previous();
    std::unique_ptr<Expr> right = term();
    expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
  }
  return expr;
}

std::unique_ptr<lox::Expr> lox::Parser::term() {
  std::unique_ptr<Expr> expr = factor();

  while(match({TokenType::MINUS, TokenType::PLUS})) {
    Token op = previous();
    std::unique_ptr<Expr> right = factor();
    expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
  }
  return expr;
}

std::unique_ptr<lox::Expr> lox::Parser::factor() {
  std::unique_ptr<Expr> expr = unary();

  while(match({TokenType::SLASH, TokenType::STAR})) {
    Token op = previous();
    std::unique_ptr<Expr> right = unary();
    expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
  }
  return expr;
}

std::unique_ptr<lox::Expr> lox::Parser::unary() {
  if (match({TokenType::BANG, TokenType::MINUS})) {
    Token op = previous();
    std::unique_ptr<Expr> right = unary();
    return std::make_unique<Unary>(op, std::move(right));
  }
  return primary();
}

std::unique_ptr<lox::Expr> lox::Parser::primary() {
  if(match({TokenType::FALSE})) return std::make_unique<Literal>(false);
  if(match({TokenType::TRUE})) return std::make_unique<Literal>(true);
  if(match({TokenType::NIL})) return std::make_unique<Literal>(nullptr);
  if (match({TokenType::NUMBER, TokenType::STRING}))
    return std::make_unique<Literal>(previous().literal);

  if (match({TokenType::LEFT_PAREN})) {
    std::unique_ptr<Expr> expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
    return std::make_unique<Grouping>(std::move(expr));
  }
}



// helper functions

bool lox::Parser::match(std::initializer_list<lox::TokenType> types) {
    for (const auto &type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool lox::Parser::check(lox::TokenType type) {
    if (isAtEnd())
    return false;
return peek().type == type;
}

bool lox::Parser::isAtEnd() { return peek().type == TokenType::END_OF_FILE; }

lox::Token lox::Parser::advance() {
  if (!isAtEnd())
    current++;
  return previous();
}

lox::Token lox::Parser::peek() { return scannedTokens[current]; }

lox::Token lox::Parser::previous() { return scannedTokens[current - 1]; }


