#include "ASTPrinter.hpp"
#include "expr.hpp"
#include <any>
#include <initializer_list>
#include <string>



std::string lox::ASTPrinter::print(const Expr &expr) {
  return std::any_cast<std::string>(expr.accept(*this));
}

std::any lox::ASTPrinter::visitBinaryExpr(const Binary &binExpr) {
  return parenthesize(binExpr.op.lexeme,
                      {binExpr.left.get(), binExpr.right.get()});
}
std::any lox::ASTPrinter::visitUnaryExpr(const Unary &unExpr) {
  return parenthesize(unExpr.op.lexeme, {unExpr.right.get()});
}
std::any lox::ASTPrinter::visitLiteralExpr(const Literal &litExpr) {
  // litExpr.value is a std::variant<nullptr_t, double, bool, std::string>
  if (std::holds_alternative<std::nullptr_t>(litExpr.value)) {
    return std::string("nil");
  }
  if (std::holds_alternative<double>(litExpr.value)) {
    return std::to_string(std::get<double>(litExpr.value));
  }
  if (std::holds_alternative<bool>(litExpr.value)) {
    return std::string(std::get<bool>(litExpr.value) ? "true" : "false");
  }
  return std::get<std::string>(litExpr.value);
}
std::any lox::ASTPrinter::visitGroupingExpr(const Grouping &grpExpr) {
  return parenthesize("group", {grpExpr.expression.get()});
}

std::string
lox::ASTPrinter::parenthesize(const std::string &name,
                              std::initializer_list<const Expr *> exprs) {

  std::string result = "(" + name;
  for (const Expr *expr : exprs) {
    result += " ";
    result += std::any_cast<std::string>(expr->accept(*this));
  }
  result += ")";


  return result;
}