
#include <fstream>
#include <iostream>
#include <iterator>

#include "lox.hpp"
#include "scanner.hpp"

void lox::Lox::runFile(const std::string &path) {
  std::ifstream file(path);

  if (!file) {
    std::cerr << "Could not open file: " << path << '\n';
    return;
  }

  std::string source((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
  
  run(source);

  if (hasError) {
    return;
  }
}

void lox::Lox::run(const std::string &source) {
  Scanner scanner(source);
  scanner.scanTokens();
}

// Error handling and Reporting

// This error() function and its report() helper tells the user some syntax
// error occurred on a given line
void lox::Lox::error(int lineNumber, std::string message) {
  report(lineNumber, "", message);
}

void lox::Lox::report(int lineNumber, std::string where, std::string message) {
  std::cerr << "[line " << lineNumber << " ] Error" << where << ": " << message
            << std::endl;
  hasError = true;
}