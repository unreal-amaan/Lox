#pragma once

#include "token.hpp"
#include <any>
#include <memory>
#include <string>
#include <variant>

namespace lox {

// forward declarations of the classes.
struct Binary;
struct Grouping;
struct Literal;
struct Unary;

using Value = std::variant<std::nullptr_t, double, bool, std::string>;

/*
ExprVisitor defines the visitor interface for traversing expression nodes.
 Each concrete visitor implements handlers for the different Expr subclasses
 so operations can be performed without embedding behavior in the AST nodes.
*/
struct ExprVisitor {
public:
  virtual ~ExprVisitor() = default;
  virtual std::any visitBinaryExpr(const Binary &) = 0;
  virtual std::any visitUnaryExpr(const Unary &) = 0;
  virtual std::any visitLiteralExpr(const Literal &) = 0;
  virtual std::any visitGroupingExpr(const Grouping &) = 0;
};


// Expr is the abstract base class for all expression nodes in the AST.
// Each expression type derives from Expr and represents a different
// syntactic construct in the Lox language.
struct Expr {
public:
  virtual ~Expr() = default;

  /*
    Accepts a visitor and dispatches the current node to the visitor's
   corresponding visit method. This enables external operations like
   evaluation or printing without coupling them to the AST node classes.
  */
  virtual std::any accept(ExprVisitor &visitor) const = 0;
};

// Binary represents a binary operation expression with a left operand,
// an operator, and a right operand (e.g., a + b, x * y).
struct Binary :  Expr {
public:
  const std::unique_ptr<Expr> left;
  const Token op;
  const std::unique_ptr<Expr> right;

  Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
      : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

  std::any accept(ExprVisitor &visitor) const override {
    return visitor.visitBinaryExpr(*this);
  }
};

// Grouping represents an expression enclosed in parentheses (e.g., (a + b)).
// It wraps another expression to enforce precedence and grouping.
struct Grouping :  Expr {
public:
  const std::unique_ptr<Expr> expression;

  Grouping(std::unique_ptr<Expr> expression)
      : expression(std::move(expression)) {}

  std::any accept(ExprVisitor &visitor) const override {
    return visitor.visitGroupingExpr(*this);
  }
};

// Unary represents a unary operation expression with an operator and
// a right operand (e.g., -x, !value).
struct Unary :  Expr {
public:
  const Token op;
  const std::unique_ptr<Expr> right;

  Unary(Token op, std::unique_ptr<Expr> right)
      : op(std::move(op)), right(std::move(right)) {}

  std::any accept(ExprVisitor &visitor) const override {
    return visitor.visitUnaryExpr(*this);
  }
};

// Literal represents a literal value expression (e.g., 42, "hello", true, nil).
// It holds a Value variant that can be a number, string, boolean, or null.
struct Literal : Expr {
public:
  const Value value;

  Literal(Value value) : value(std::move(value)) {}

  std::any accept(ExprVisitor &visitor) const override {
    return visitor.visitLiteralExpr(*this);
  }
};

} // namespace lox