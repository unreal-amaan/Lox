#include "token.hpp"
#include <memory>
#include <string>
#include <variant>


namespace lox {

using Value = std::variant<std::nullptr_t, double, bool, std::string>;

template <typename R> class ExprVisitor {
  
};


// Expr is the abstract base class for all expression nodes in the AST.
// Each expression type derives from Expr and represents a different
// syntactic construct in the Lox language.
class Expr {
public:
  virtual ~Expr() = default;
};

// Binary represents a binary operation expression with a left operand,
// an operator, and a right operand (e.g., a + b, x * y).
class Binary : public Expr {
private:
  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;

public:
  Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
      : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}
};

// Grouping represents an expression enclosed in parentheses (e.g., (a + b)).
// It wraps another expression to enforce precedence and grouping.
class Grouping : public Expr {
private:
  std::unique_ptr<Expr> expression;

public:
  Grouping(std::unique_ptr<Expr> expression)
      : expression(std::move(expression)) {}
};

// Unary represents a unary operation expression with an operator and
// a right operand (e.g., -x, !value).
class Unary : public Expr {
private:
  Token op;
  std::unique_ptr<Expr> right;

public:
  Unary(Token op, std::unique_ptr<Expr> right)
      : op(std::move(op)), right(std::move(right)) {}
};

// Literal represents a literal value expression (e.g., 42, "hello", true, nil).
// It holds a Value variant that can be a number, string, boolean, or null.
class Literal : public Expr {
private:
  Value value;

public:
  Literal(Value value) : value(std::move(value)) {}
};

} // namespace lox