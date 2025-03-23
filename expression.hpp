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
inline std::string make_string(Num val) {
    return std::to_string(val);
}

template<>
inline std::string make_string<complex>(complex val) {
    std::string str = std::string("(");
    str += std::to_string(val.real());
    str += std::string(" + ");
    str += std::to_string(val.imag());
    str += std::string("i)");
    return str;
}

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

    Value(Num val) : _value(val) {}

    ~Value() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        return _value;
    }

    std::string to_string() const override {
        return make_string<Num>(_value);
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return Expression<Num>(_value);
    }

    Expression<Num> dif(std::string substitution) const override {
        return Expression<Num>(0);
    }

private:
    Num _value;
};


template<typename Num = rational>
class Variable : public ExpressionTempl<Num> {
public:
    Variable(std::string name) : _name(name) {}

    ~Variable() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        auto it = substitution.find(_name);
        if (it == substitution.end()) {
            std::cout << "mistake";
        }
        return it->second;
    }

    std::string to_string() const override { return _name; }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        auto it = substitution.find(_name);
        if (it == substitution.end()) {
            return Expression<Num>(_name);
        }
        return Expression<Num>(it->second);
    }

    Expression<Num> dif(std::string substitution) const override {
        if (substitution == _name) {
            return Expression<Num>(1);
        }
        return Expression<Num>(0);
    }

private:
    std::string _name;
};

template<typename Num = rational>
class AddExpr : public ExpressionTempl<Num> {
public:
    AddExpr(Expression<Num> lhs, Expression<Num> rhs) : _lhs(lhs), _rhs(rhs) {}

    ~AddExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        Num left = _lhs.eval(substitution);
        Num right = _rhs.eval(substitution);
        return left + right;
    }

    std::string to_string() const override {
        return std::string("(") + _lhs.to_string() +
               std::string(" + ") + _rhs.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return _lhs.sub(substitution) + _rhs.sub(substitution);
    }

    Expression<Num> dif(std::string substitution) const override {
        return _lhs.dif(substitution) + _rhs.dif(substitution);
    }

private:
    Expression<Num> _lhs;
    Expression<Num> _rhs;
};

template<typename Num = rational>
class MulExpr : public ExpressionTempl<Num> {
public:
    MulExpr(Expression<Num> lhs, Expression<Num> rhs) : _lhs(lhs), _rhs(rhs) {}

    ~MulExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        Num left = _lhs.eval(substitution);
        Num right = _rhs.eval(substitution);
        return left * right;
    }

    std::string to_string() const override {
        return std::string("(") + _lhs.to_string() +
               std::string(" * ") + _rhs.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return _lhs.sub(substitution) * _rhs.sub(substitution);
    }

    Expression<Num> dif(std::string substitution) const override {
        return _lhs * _rhs.dif(substitution) + _lhs.dif(substitution) * _rhs;
    }

private:
    Expression<Num> _lhs;
    Expression<Num> _rhs;
};

template<typename Num = rational>
class SubExpr : public ExpressionTempl<Num> {
public:
    SubExpr(Expression<Num> lhs, Expression<Num> rhs) : _lhs(lhs), _rhs(rhs) {}

    ~SubExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        Num left = _lhs.eval(substitution);
        Num right = _rhs.eval(substitution);
        return left - right;
    }

    std::string to_string() const override {
        return std::string("(") + _lhs.to_string() +
               std::string(" - ") + _rhs.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return _lhs.sub(substitution) - _rhs.sub(substitution);
    }

    Expression<Num> dif(std::string substitution) const override {
        return _lhs.dif(substitution) - _rhs.dif(substitution);
    }

private:
    Expression<Num> _lhs;
    Expression<Num> _rhs;
};

template<typename Num = rational>
class LnExpr : public ExpressionTempl<Num> {
public:
    LnExpr(Expression<Num> content) : _content(content) {}

    ~LnExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        return std::log(_content.eval(substitution));
    }

    std::string to_string() const override {
        return std::string("ln(") + _content.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return ln(_content.sub(substitution));
    }

    Expression<Num> dif(std::string substitution) const override {
        return Expression<Num>(1) / _content * _content.dif(substitution);
    }

private:
    Expression<Num> _content;
};

template<typename Num = rational>
class PowExpr : public ExpressionTempl<Num> {
public:
    PowExpr(Expression<Num> base, Expression<Num> exp) : _base(base), _exp(exp) {}

    ~PowExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        Num left = _base.eval(substitution);
        Num right = _exp.eval(substitution);
        return std::pow(left, right);
    }

    std::string to_string() const override {
        return std::string("(") + _base.to_string() +
               std::string(" ^ ") + _exp.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return _base.sub(substitution) ^ _exp.sub(substitution);
    }

    Expression<Num> dif(std::string substitution) const override {
        return _exp * (_base ^ (_exp - Expression<Num>(1))) * _base.dif(substitution) +
               (_base ^ _exp) * ln(_base) * _exp.dif(substitution);
    }

private:
    Expression<Num> _base;
    Expression<Num> _exp;
};

template<typename Num = rational>
class DivExpr : public ExpressionTempl<Num> {
public:
    DivExpr(Expression<Num> lhs, Expression<Num> rhs) : _lhs(lhs), _rhs(rhs) {}

    ~DivExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        Num left = _lhs.eval(substitution);
        Num right = _rhs.eval(substitution);
        return left / right;
    }


    std::string to_string() const override {
        return std::string("(") + _lhs.to_string() +
               std::string(" / ") + _rhs.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return _lhs.sub(substitution) / _rhs.sub(substitution);
    }

    Expression<Num> dif(std::string substitution) const override {
        return _lhs.dif(substitution) * _rhs - _lhs * _rhs.dif(substitution) / (_rhs ^ Expression<Num>(2));
    }

private:
    Expression<Num> _lhs;
    Expression<Num> _rhs;
};


template<typename Num = rational>
class SinExpr : public ExpressionTempl<Num> {
public:
    SinExpr(Expression<Num> content) : _content(content) {}

    ~SinExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        return std::sin(_content.eval(substitution));
    }

    std::string to_string() const override {
        return std::string("sin(") + _content.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return sin(_content.sub(substitution));
    }

    Expression<Num> dif(std::string substitution) const override {
        return cos(_content) * _content.dif(substitution);
    }

private:
    Expression<Num> _content;
};

template<typename Num = rational>
class CosExpr : public ExpressionTempl<Num> {
public:
    CosExpr(Expression<Num> content) : _content(content) {}

    ~CosExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        return std::cos(_content.eval(substitution));
    }

    std::string to_string() const override {
        return std::string("cos(") + _content.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return cos(_content.sub(substitution));
    }

    Expression<Num> dif(std::string substitution) const override {
        return sin(_content) * _content.dif(substitution);
    }

private:
    Expression<Num> _content;
};


template<typename Num = rational>
class ExpExpr : public ExpressionTempl<Num> {
public:
    ExpExpr(Expression<Num> content) : _content(content) {}

    ~ExpExpr() override = default;

    Num eval(std::map<std::string, Num> substitution) const override {
        return std::exp(_content.eval(substitution));
    }

    std::string to_string() const override {
        return std::string("exp(") + _content.to_string() +
               std::string(")");
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const override {
        return exp(_content.sub(substitution));
    }

    Expression<Num> dif(std::string substitution) const override {
        return exp(_content) * _content.dif(substitution);
    }

private:
    Expression<Num> _content;
};

inline std::string space_deleter(std::string var) {
    std::string res = std::string("");
    for (int i = 0; i < var.size(); i++) {
        if (var[i] != ' ')res += var[i];
    }
    return res;
}

template<typename Num = rational>
inline Num parse_number(const std::string var, bool with_i) {
    return std::stod(var);;
}

template<>
inline complex parse_number<complex>(const std::string var, bool with_i) {
    if (var.empty()) {
        return complex(0, 1);
    }
    if (with_i)
        return complex(0, std::stod(var));
    else
        return complex(std::stod(var), 0);
}


template<typename Num = rational>
std::shared_ptr<ExpressionTempl<Num>> parce(std::string var) {
    int scobe = 0;
    for (int i = var.size() - 1; i >= 0; i -= 1) {
        if (var[i] == ')')
            scobe += 1;
        if (var[i] == '(')
            scobe -= 1;
        if (var[i] == '+' and scobe == 0) {
            return std::make_shared<AddExpr<Num>>(Expression<Num>(var.substr(0, i)),
                                                  Expression<Num>(var.substr(i + 1, var.size())));
        }
        if (var[i] == '-' and scobe == 0)
            return std::make_shared<SubExpr<Num>>(Expression<Num>(var.substr(0, i)),
                                                  Expression<Num>(var.substr(i + 1, var.size())));
    }

    for (int i = var.size() - 1; i >= 0; i -= 1) {
        if (var[i] == ')')
            scobe += 1;
        if (var[i] == '(')
            scobe -= 1;
        if (var[i] == '*' and scobe == 0)
            return std::make_shared<MulExpr<Num>>(Expression<Num>(var.substr(0, i)),
                                                  Expression<Num>(var.substr(i + 1, var.size())));
        if (var[i] == '/' and scobe == 0)
            return std::make_shared<DivExpr<Num>>(Expression<Num>(var.substr(0, i)),
                                                  Expression<Num>(var.substr(i + 1, var.size())));
    }
    for (int i = var.size() - 1; i >= 0; i -= 1) {
        if (var[i] == ')')
            scobe += 1;
        if (var[i] == '(')
            scobe -= 1;
        if (var[i] == '^' and scobe == 0)
            return std::make_shared<PowExpr<Num>>(Expression<Num>(var.substr(0, i)),
                                                  Expression<Num>(var.substr(i + 1, var.size())));
    }
    if (var[0] == '(')

        return parce<Num>(var.substr(1, var.size() - 2));
    if (var.substr(0, 3) == "sin")
        return std::make_shared<SinExpr<Num>>(Expression<Num>(var.substr(4, var.size() - 5)));
    if (var.substr(0, 3) == "cos")
        return std::make_shared<CosExpr<Num>>(Expression<Num>(var.substr(4, var.size() - 5)));
    if (var.substr(0, 3) == "exp")
        return std::make_shared<ExpExpr<Num>>(Expression<Num>(var.substr(4, var.size() - 5)));
    if (var.substr(0, 2) == "ln")
        return std::make_shared<LnExpr<Num>>(Expression<Num>(var.substr(3, var.size() - 4)));


    if (var[var.size() - 1] == 'i') {

        return std::make_shared<Value<Num>>(parse_number<Num>(var.substr(0, var.size() - 1), true));

    }


    if (!var.empty() && (var.find_first_not_of("0123456789") == var.npos)) {
        return std::make_shared<Value<Num>>(parse_number<Num>(var.substr(0, var.size()), false));;
    }

    return std::make_shared<Variable<Num>>(var);

}


template<typename Num = rational>
class Expression {
public:
    Expression(const std::string &var) {
        _content = parce<Num>(space_deleter(var));

    }

    Expression(Num var) {
        _content = std::make_shared<Value<Num>>(var);
    }

    Expression(int var) {
        _content = std::make_shared<Value<Num>>((Num) var);
    }

    friend Expression<Num> operator+(const Expression<Num> &lhs, const Expression<Num> &rhs) {
        return Expression(std::make_shared<AddExpr<Num>>(lhs, rhs));
    }

    friend Expression<Num> operator-(const Expression<Num> &lhs, const Expression<Num> &rhs) {
        return Expression(std::make_shared<SubExpr<Num>>(lhs, rhs));
    }

    friend Expression<Num> operator*(const Expression<Num> &lhs, const Expression<Num> &rhs) {
        return Expression(std::make_shared<MulExpr<Num>>(lhs, rhs));
    }

    friend Expression<Num> operator/(const Expression<Num> &lhs, const Expression<Num> &rhs) {
        return Expression(std::make_shared<DivExpr<Num>>(lhs, rhs));
    }

    friend Expression<Num> operator^(const Expression<Num> &lhs, const Expression<Num> &rhs) {
        return Expression(std::make_shared<PowExpr<Num>>(lhs, rhs));
    }

    friend Expression<Num> sin(const Expression<Num> &content) {
        return Expression(std::make_shared<SinExpr<Num>>(content));
    }

    friend Expression<Num> cos(const Expression<Num> &content) {
        return Expression(std::make_shared<CosExpr<Num>>(content));
    }

    friend Expression<Num> ln(const Expression<Num> &content) {
        return Expression(std::make_shared<LnExpr<Num>>(content));
    }

    friend Expression<Num> exp(const Expression<Num> &content) {
        return Expression(std::make_shared<ExpExpr<Num>>(content));
    }

    Num eval(std::map<std::string, Num> substitution) const {
        return _content->eval(substitution);
    }

    std::string to_string() const {
        return _content->to_string();
    }

    Expression<Num> sub(std::map<std::string, Num> substitution) const {
        return _content->sub(substitution);
    }

    Expression<Num> dif(std::string substitution) const {
        return _content->dif(substitution);
    }

private:
    Expression(std::shared_ptr<ExpressionTempl<Num>> content) : _content(content) {}


    std::shared_ptr<ExpressionTempl<Num>> _content;

};

#endif
