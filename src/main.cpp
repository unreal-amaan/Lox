#include <iostream>
#include "ASTPrinter.hpp"
#include "lox.hpp"
int main(int argc, char *argv[]) {
  auto expression = std::make_unique<lox::Binary>(
      std::make_unique<lox::Unary>(
          lox::Token(lox::TokenType::MINUS, "-", nullptr, 1),
          std::make_unique<lox::Literal>(123.0)),
      lox::Token(lox::TokenType::STAR, "*", nullptr, 1),
      std::make_unique<lox::Grouping>(std::make_unique<lox::Literal>(45.67)));
  lox::Lox loxInterpreter;
  lox::ASTPrinter ast;
      if (argc > 2) {
        std::cout << "Usage: lox [script]" << std::endl;
      } else if(argc == 2){
        loxInterpreter.runFile(argv[1]);
        std::cout << ast.print(*expression) << '\n';
      } else {
        std::cout << "Please provide a script file." << std::endl;
      }
      return 0;
}