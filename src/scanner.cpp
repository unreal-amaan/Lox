
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "lox.hpp"
#include "scanner.hpp"
#include "token.hpp"
#include "tokenType.hpp"

lox::Scanner::Scanner(const std::string &source, Lox &lox)
    : sourceCode(source), loxInstance(lox) {}

std::vector<lox::Token> lox::Scanner::scanTokens() {
  // std::cout << "************Source Code************" << std::endl;
  // std::cout << sourceCode << std::endl;
  while (!isAtEnd()) {
    start = current;
    char c = advance();
    if (std::isdigit(static_cast<unsigned char>(c))) {
      scanNumber();
      continue;
    } else if (c == '_' || std::isalpha(static_cast<unsigned char>(c))) {
      scanIdentifier();
      continue;
    }
    switch (c) {
    // ignore the white spaces
    case ' ':
    case '\r':
    case '\t':
      break;

    // Line end
    case '\n':
      lineNumber++;
      break;
    // Single character lexemes
    case '{':
      addToken(TokenType::LEFT_BRACE, nullptr);
      break;
    case '}':
      addToken(TokenType::RIGHT_BRACE, nullptr);
      break;
    case '(':
      addToken(TokenType::LEFT_PAREN, nullptr);
      break;
    case ')':
      addToken(TokenType::RIGHT_PAREN, nullptr);
      break;
    case ',':
      addToken(TokenType::COMMA, nullptr);
      break;
    case '.':
      addToken(TokenType::DOT, nullptr);
      break;
    case ';':
      addToken(TokenType::SEMICOLON, nullptr);
      break;
    // Arithmetic operators
    case '-':
      addToken(TokenType::MINUS, nullptr);
      break;
    case '*':
      addToken(TokenType::STAR, nullptr);
      break;
    case '+':
      addToken(TokenType::PLUS, nullptr);
      break;
    // Assignment and comparison operators
    case '!':
      addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG, nullptr);
      break;
    case '=':
      addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL, nullptr);
      break;
    case '<':
      addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS, nullptr);
      break;
    case '>':
      addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER,
               nullptr);
      break;
    case '/':
      // this is a line comment so skip the characters till the line end.
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd()) {
          advance();
        }
      } else { // it is a division operator.
        addToken(TokenType::SLASH, nullptr);
      }
      break;

      // String literals
    case '"':
      scanString();
      break;

    default:
      loxInstance.error(lineNumber, "Unexpected character.");
      break;
    }
  }
  tokens.emplace_back(TokenType::END_OF_FILE, "", nullptr, lineNumber);
  return tokens;
}

// helper functions for scanTokens.

char lox::Scanner::advance() { return sourceCode[current++]; }

bool lox::Scanner::isAtEnd() const { return current >= sourceCode.length(); }

char lox::Scanner::peek() {
  if (isAtEnd()) {
    return '\0';
  }
  return sourceCode[current];
}
char lox::Scanner::peekNext() {
  if (current + 1 >= sourceCode.length()) {
    return '\0';
  }
  return sourceCode[current + 1];
}

bool lox::Scanner::match(const char expected) {
  if (isAtEnd() || sourceCode[current] != expected)
    return false;
  current++;
  return true;
}

void lox::Scanner::addToken(TokenType type, LiteralValue literal) {
  std::string text = sourceCode.substr(start, current - start);
  tokens.emplace_back(Token(type, text, literal, lineNumber));
}

void lox::Scanner::scanString() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      lineNumber++;
    advance();
  }

  if (isAtEnd()) {
    loxInstance.error(lineNumber, "Unterminated string.");
    return;
  }
  advance(); // the closing ".
  std::string stringLexeme = sourceCode.substr(start + 1, current - start - 2);
  addToken(TokenType::STRING, stringLexeme);
}

void lox::Scanner::scanNumber() {
  while (std::isdigit(static_cast<unsigned char>(peek()))) {
    advance();
  }
  // check for fractional part '.'
  if (peek() == '.' && std::isdigit(static_cast<unsigned char>(peekNext()))) {
    advance(); // consume the '.'

    while (std::isdigit(static_cast<unsigned char>(peek()))) {
      advance();
    }
  }

  std::string num = sourceCode.substr(start, current - start);

  addToken(TokenType::NUMBER, std::stod(num));
}

void lox::Scanner::scanIdentifier() {
  while (peek() == '_' || std::isalnum(static_cast<unsigned char>(peek()))) {
    advance();
  }
  std::string text = sourceCode.substr(start, current - start);
  const auto it = keyWords.find(text);
  TokenType type = (it != keyWords.end()) ? it->second : TokenType::IDENTIFIER;
  addToken(type, nullptr);
}

void lox::Scanner::printTokens() {
  std::cout << "********Scanned Tokens********" << std::endl;
  for (const auto &token : tokens) {
    std::cout << token << std::endl;
  }
}
