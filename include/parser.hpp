#include "expr.hpp"
#include "token.hpp"
#include "tokenType.hpp"
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <vector>

namespace lox {

/*
This is the Grammar that we will be parse for lox
expression     → equality ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;


Grammar notation  |  Code Representation
Terminal          |  Code to match and consume a token
non terminal      |  Call to that rule’s function
|                 |  if or switch statement
* or +            |  Loop(while or for)
?                 |  if statement

*/

class Parser {
private:
  const std::vector<lox::Token> &scannedTokens;
  size_t current = 0;

  std::unique_ptr<Expr>
  expression(); // Parses the highest-level expression rule.

  std::unique_ptr<Expr> equality(); // Parses equality operators: "!=" and "==".

  std::unique_ptr<Expr>
  comparison(); // Parses comparison operators: ">", ">=", "<", "<=".

  std::unique_ptr<Expr> term();    // Parses term operators: "+" and "-".
  std::unique_ptr<Expr> factor();  // Parses factor operators: "*" and "/".
  std::unique_ptr<Expr> unary();   // Parses unary operators: "!" and "-".
  std::unique_ptr<Expr> primary(); // Parses primary expressions: literals,
                                   // identifiers, and grouped expressions.

  bool match(std::initializer_list<
             lox::TokenType>); // Checks if the current token matches any of the
                               // given types and advances if match found.

  bool check(lox::TokenType); // returns true if the current token is of the
                              // given type.
  bool isAtEnd(); // check the end of the tokens list i.e., END_OF_FILE.
  lox::Token
  advance();         // returns true if the current token is of the given type.
  lox::Token peek(); // returns the current token we are yet to consume.
  lox::Token previous(); // returns the most recently consumed token

public:
  Parser(std::vector<lox::Token> &);
};
} // namespace lox