#pragma once

#include <string>

namespace lox {

class Lox {
public:
  // the runFile function's thin wrapper around the run function to  read the
  // code and call the run function.
  void runFile(const std::string &path);

private:
  bool hasError;
  bool hasRuntimeError;

  // run is the core function which handles the scanning of the tokens.
  void run(const std::string &source);

  // Error handling and Reporting

  // This error() function and its report() helper tells the user some syntax
  // error occurred on a given line
  void error(int lineNumber, std::string message);
  void report(int lineNumber, std::string where, std::string message);
};

} // namespace lox