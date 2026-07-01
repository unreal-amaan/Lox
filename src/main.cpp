#include <iostream>
#include "ASTPrinter.hpp"
#include "lox.hpp"
int main(int argc, char *argv[]) {
  lox::Lox loxInterpreter;
  lox::ASTPrinter ast;
      if (argc > 2) {
        std::cout << "Usage: lox [script]" << std::endl;
      } else if(argc == 2){
        loxInterpreter.runFile(argv[1]);
      } else {
        std::cout << "Please provide a script file." << std::endl;
      }
      return 0;
}