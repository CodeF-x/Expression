#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include <complex>
#include <map>
#include <iostream>
#include <memory>

using rational = double;
using complex = std::complex<double>;


template<typename Num = rational>
inline std::string make_string(Num val);

template<>
inline std::string make_string<complex>(complex val);

template<typename Num>
class Expression;

template<typename Num = rational>
class ExpressionTempl {
public:
    ExpressionTempl() = default;

    virtual ~ExpressionTempl() = default;

    virtual Num eval(std::map<std::string, Num> substitution) const = 0;

    virtual std::string to_string() const = 0;

    virtual Expression<Num> sub(std::map<std::string, Num> substitution) const = 0;

    virtual Expression<Num> dif(std::string substitution) const = 0;

};


template<typename Num = rational>
class Value : public ExpressionTempl<Num> {
public:

    Value(Num val);

    ~Value() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Num _value;
};


template<typename Num = rational>
class Variable : public ExpressionTempl<Num> {
public:
    Variable(std::string name);

    ~Variable() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    std::string _name;
};

template<typename Num = rational>
class AddExpr : public ExpressionTempl<Num> {
public:
    AddExpr(Expression<Num> lhs, Expression<Num> rhs);

    ~AddExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _lhs;
    Expression<Num> _rhs;
};

template<typename Num = rational>
class MulExpr : public ExpressionTempl<Num> {
public:
    MulExpr(Expression<Num> lhs, Expression<Num> rhs);

    ~MulExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _lhs;
    Expression<Num> _rhs;
};

template<typename Num = rational>
class SubExpr : public ExpressionTempl<Num> {
public:
    SubExpr(Expression<Num> lhs, Expression<Num> rhs);

    ~SubExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _lhs;
    Expression<Num> _rhs;
};

template<typename Num = rational>
class LnExpr : public ExpressionTempl<Num> {
public:
    LnExpr(Expression<Num> content);

    ~LnExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _content;
};

template<typename Num = rational>
class PowExpr : public ExpressionTempl<Num> {
public:
    PowExpr(Expression<Num> base, Expression<Num> exp);

    ~PowExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _base;
    Expression<Num> _exp;
};

template<typename Num = rational>
class DivExpr : public ExpressionTempl<Num> {
public:
    DivExpr(Expression<Num> lhs, Expression<Num> rhs);

    ~DivExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;


    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _lhs;
    Expression<Num> _rhs;
};


template<typename Num = rational>
class SinExpr : public ExpressionTempl<Num> {
public:
    SinExpr(Expression<Num> content);

    ~SinExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _content;
};

template<typename Num = rational>
class CosExpr : public ExpressionTempl<Num> {
public:
    CosExpr(Expression<Num> content);

    ~CosExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _content;
};


template<typename Num = rational>
class ExpExpr : public ExpressionTempl<Num> {
public:
    ExpExpr(Expression<Num> content);

    ~ExpExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override;

    std::string to_string() const override;

    Expression<Num> sub(std::map<std::string, Num> substitution) const override;

    Expression<Num> dif(std::string substitution) const override;

private:
    Expression<Num> _content;
};

inline std::string space_deleter(std::string var);

template<typename Num = rational>
inline Num parse_number(const std::string var, bool with_i);

template<>
inline complex parse_number<complex>(const std::string var, bool with_i);

template<typename Num = rational>
std::shared_ptr<ExpressionTempl<Num>> parce(std::string var);

template<typename Num = rational>
class Expression {
public:
    Expression(const std::string &var);

    Expression(Num var);

    Expression(int var);

    Expression(std::shared_ptr<ExpressionTempl<Num>> content);

    Expression(const Expression<Num> &expr);

    Expression(Expression<Num> &&expr);

    ~Expression() = default;

    Expression<Num> &operator=(const Expression<Num> &rhs);

    Expression<Num> &operator=(Expression<Num> &&rhs);

    Expression<Num> operator+(const Expression<Num> &rhs) const;

    Expression<Num> operator-(const Expression<Num> &rhs) const;

    Expression<Num> operator*(const Expression<Num> &rhs) const;

    Expression<Num> operator/(const Expression<Num> &rhs) const;

    Expression<Num> operator^(const Expression<Num> &rhs) const;

    Expression<Num> sin() const;

    Expression<Num> cos() const;

    Expression<Num> ln() const;

    Expression<Num> exp() const;

    Num eval(std::map<std::string, Num> substitution) const;

    std::string to_string() const;

    Expression<Num> sub(std::map<std::string, Num> substitution) const;

    Expression<Num> dif(std::string substitution) const;


private:


    std::shared_ptr<ExpressionTempl<Num>> _content;

};

#endif
