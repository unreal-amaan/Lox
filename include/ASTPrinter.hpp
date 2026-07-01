#pragma once

#include "expr.hpp"
#include <any>
#include <initializer_list>
#include <string>

namespace lox {

class ASTPrinter : public ExprVisitor {
private:
  std::string parenthesize(const std::string &,
                           std::initializer_list<const Expr *>);
public:
  std::string print(const Expr &expr);

  std::any visitBinaryExpr(const Binary &) override;
  std::any visitUnaryExpr(const Unary &) override;
  std::any visitLiteralExpr(const Literal &) override;
  std::any visitGroupingExpr(const Grouping &) override;

};
} // namespace lox