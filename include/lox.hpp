#pragma once

#include <cstddef>
#include <string>

namespace lox {

class Lox {
public:
  // the runFile function's thin wrapper around the run function to  read the
  // code and call the run function.
  void runFile(const std::string &path);
  // the error function is a thin wrapper around the report function which
  // describes the errors when they are occured
  void error(size_t lineNumber, std::string message);

private:
  bool hasError;
  bool hasRuntimeError;

  // run is the core function which handles the scanning of the tokens.
  void run(const std::string &source);

  // Error handling and Reporting
  // report() helper tells the user some syntax error occurred on a given line
  void report(size_t lineNumber, std::string where, std::string message);
};

} // namespace lox