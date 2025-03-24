#include "expression.hpp"
#include <string>
#include <complex>
#include <map>
#include <iostream>
#include <memory>

using rational = double;
using complex = std::complex<double>;


template<typename Num>
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
Value<Num>::Value(Num val) : _value(val) {}

template<typename Num>
Num Value<Num>::eval(std::map<std::string, Num> substitution) const {
    return _value;
}

template<typename Num>
std::string Value<Num>::to_string() const {
    return make_string<Num>(_value);
}

template<typename Num>
Expression<Num> Value<Num>::sub(std::map<std::string, Num> substitution) const {
    return Expression<Num>(_value);
}

template<typename Num>
Expression<Num> Value<Num>::dif(std::string substitution) const {
    return Expression<Num>(0);
}


template<typename Num>
Variable<Num>::Variable(std::string name) : _name(name) {}

template<typename Num>
Num Variable<Num>::eval(std::map<std::string, Num> substitution) const {
    auto it = substitution.find(_name);
    if (it == substitution.end()) {
        std::cout << "mistake";
    }
    return it->second;
}

template<typename Num>
std::string Variable<Num>::to_string() const { return _name; }

template<typename Num>
Expression<Num> Variable<Num>::sub(std::map<std::string, Num> substitution) const {
    auto it = substitution.find(_name);
    if (it == substitution.end()) {
        return Expression<Num>(_name);
    }
    return Expression<Num>(it->second);
}

template<typename Num>
Expression<Num> Variable<Num>::dif(std::string substitution) const {
    if (substitution == _name) {
        return Expression<Num>(1);
    }
    return Expression<Num>(0);
}


template<typename Num>

AddExpr<Num>::AddExpr(Expression<Num> lhs, Expression<Num> rhs) : _lhs(lhs), _rhs(rhs) {}

template<typename Num>
Num AddExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    Num left = _lhs.eval(substitution);
    Num right = _rhs.eval(substitution);
    return left + right;
}

template<typename Num>
std::string AddExpr<Num>::to_string() const {
    return std::string("(") + _lhs.to_string() +
           std::string(" + ") + _rhs.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> AddExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _lhs.sub(substitution) + _rhs.sub(substitution);
}

template<typename Num>
Expression<Num> AddExpr<Num>::dif(std::string substitution) const {
    return _lhs.dif(substitution) + _rhs.dif(substitution);
}


template<typename Num>
MulExpr<Num>::MulExpr(Expression<Num> lhs, Expression<Num> rhs) : _lhs(lhs), _rhs(rhs) {}


template<typename Num>
Num MulExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    Num left = _lhs.eval(substitution);
    Num right = _rhs.eval(substitution);
    return left * right;
}

template<typename Num>
std::string MulExpr<Num>::to_string() const {
    return std::string("(") + _lhs.to_string() +
           std::string(" * ") + _rhs.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> MulExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _lhs.sub(substitution) * _rhs.sub(substitution);
}

template<typename Num>
Expression<Num> MulExpr<Num>::dif(std::string substitution) const {
    return _lhs * _rhs.dif(substitution) + _lhs.dif(substitution) * _rhs;
}


template<typename Num>
SubExpr<Num>::SubExpr(Expression<Num> lhs, Expression<Num> rhs) : _lhs(lhs), _rhs(rhs) {}

template<typename Num>
Num SubExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    Num left = _lhs.eval(substitution);
    Num right = _rhs.eval(substitution);
    return left - right;
}

template<typename Num>
std::string SubExpr<Num>::to_string() const {
    return std::string("(") + _lhs.to_string() +
           std::string(" - ") + _rhs.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> SubExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _lhs.sub(substitution) - _rhs.sub(substitution);
}

template<typename Num>
Expression<Num> SubExpr<Num>::dif(std::string substitution) const {
    return _lhs.dif(substitution) - _rhs.dif(substitution);
}

template<typename Num>
LnExpr<Num>::LnExpr(Expression<Num> content) : _content(content) {}


template<typename Num>
Num LnExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    return std::log(_content.eval(substitution));
}

template<typename Num>
std::string LnExpr<Num>::to_string() const {
    return std::string("ln(") + _content.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> LnExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _content.sub(substitution).ln();
}

template<typename Num>
Expression<Num> LnExpr<Num>::dif(std::string substitution) const {
    return Expression<Num>(1) / _content * _content.dif(substitution);
}

template<typename Num>
PowExpr<Num>::PowExpr(Expression<Num> base, Expression<Num> exp) : _base(base), _exp(exp) {}

template<typename Num>
Num PowExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    Num left = _base.eval(substitution);
    Num right = _exp.eval(substitution);
    return std::pow(left, right);
}

template<typename Num>
std::string PowExpr<Num>::to_string() const {
    return std::string("(") + _base.to_string() +
           std::string(" ^ ") + _exp.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> PowExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _base.sub(substitution) ^ _exp.sub(substitution);
}

template<typename Num>
Expression<Num> PowExpr<Num>::dif(std::string substitution) const {
    return _exp * (_base ^ (_exp - Expression<Num>(1))) * _base.dif(substitution) +
           (_base ^ _exp) * _base.ln() * _exp.dif(substitution);
}


template<typename Num>
DivExpr<Num>::DivExpr(Expression<Num> lhs, Expression<Num> rhs) : _lhs(lhs), _rhs(rhs) {}

template<typename Num>
Num DivExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    Num left = _lhs.eval(substitution);
    Num right = _rhs.eval(substitution);
    return left / right;
}

template<typename Num>
std::string DivExpr<Num>::to_string() const {
    return std::string("(") + _lhs.to_string() +
           std::string(" / ") + _rhs.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> DivExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _lhs.sub(substitution) / _rhs.sub(substitution);
}

template<typename Num>
Expression<Num> DivExpr<Num>::dif(std::string substitution) const {
    return _lhs.dif(substitution) * _rhs - _lhs * _rhs.dif(substitution) / (_rhs ^ Expression<Num>(2));
}


template<typename Num>
SinExpr<Num>::SinExpr(Expression<Num> content) : _content(content) {}

template<typename Num>
Num SinExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    return std::sin(_content.eval(substitution));
}

template<typename Num>
std::string SinExpr<Num>::to_string() const {
    return std::string("sin(") + _content.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> SinExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _content.sub(substitution).sin();
}

template<typename Num>
Expression<Num> SinExpr<Num>::dif(std::string substitution) const {
    return _content.cos() * _content.dif(substitution);
}


template<typename Num>
CosExpr<Num>::CosExpr(Expression<Num> content) : _content(content) {}

template<typename Num>
Num CosExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    return std::cos(_content.eval(substitution));
}

template<typename Num>
std::string CosExpr<Num>::to_string() const {
    return std::string("cos(") + _content.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> CosExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _content.sub(substitution).cos();
}

template<typename Num>
Expression<Num> CosExpr<Num>::dif(std::string substitution) const {
    return _content.sin() * _content.dif(substitution);
}


template<typename Num>
ExpExpr<Num>::ExpExpr(Expression<Num> content) : _content(content) {}

template<typename Num>
Num ExpExpr<Num>::eval(std::map<std::string, Num> substitution) const {
    return std::exp(_content.eval(substitution));
}

template<typename Num>
std::string ExpExpr<Num>::to_string() const {
    return std::string("exp(") + _content.to_string() +
           std::string(")");
}

template<typename Num>
Expression<Num> ExpExpr<Num>::sub(std::map<std::string, Num> substitution) const {
    return _content.sub(substitution).exp();
}

template<typename Num>
Expression<Num> ExpExpr<Num>::dif(std::string substitution) const {
    return _content.exp() * _content.dif(substitution);
}


inline std::string space_deleter(std::string var) {
    std::string res = std::string("");
    for (int i = 0; i < var.size(); i++) {
        if (var[i] != ' ')res += var[i];
    }
    return res;
}

template<typename Num>
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


template<typename Num>
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


template<typename Num>
Expression<Num>::Expression(const std::string &var) {
    _content = parce<Num>(space_deleter(var));

}

template<typename Num>
Expression<Num>::Expression(Num var) {
    _content = std::make_shared<Value<Num>>(var);
}

template<typename Num>
Expression<Num>::Expression(int var) {
    _content = std::make_shared<Value<Num>>((Num) var);
}

template<typename Num>
Expression<Num>::Expression(const Expression<Num> &expr): _content(expr._content) {}

template<typename Num>
Expression<Num>::Expression(Expression<Num> &&expr): _content(std::move(expr._content)) {}

template<typename Num>
Expression<Num>::Expression(std::shared_ptr<ExpressionTempl<Num>> content) : _content(content) {}

template<typename Num>
Expression<Num> &Expression<Num>::operator=(const Expression<Num> &rhs) {
    _content = rhs._content;
    return *this;
}

template<typename Num>
Expression<Num> &Expression<Num>::operator=(Expression<Num> &&rhs) {
    _content = std::move(rhs._content);
    return *this;
}

template<typename Num>
Expression<Num> Expression<Num>::operator+(const Expression<Num> &rhs) const {
    return Expression<Num>(std::make_shared<AddExpr<Num>>(*this, rhs));
}

template<typename Num>
Expression<Num> Expression<Num>::operator-(const Expression<Num> &rhs) const {
    return Expression<Num>(std::make_shared<SubExpr<Num>>(*this, rhs));
}

template<typename Num>
Expression<Num> Expression<Num>::operator*(const Expression<Num> &rhs) const {
    return Expression<Num>(std::make_shared<MulExpr<Num>>(*this, rhs));
}

template<typename Num>
Expression<Num> Expression<Num>::operator/(const Expression<Num> &rhs) const {
    return Expression<Num>(std::make_shared<DivExpr<Num>>(*this, rhs));
}

template<typename Num>
Expression<Num> Expression<Num>::operator^(const Expression<Num> &rhs) const {
    return Expression<Num>(std::make_shared<PowExpr<Num>>(*this, rhs));
}

template<typename Num>
Expression<Num> Expression<Num>::sin() const {
    return Expression<Num>(std::make_shared<SinExpr<Num>>(_content));
}

template<typename Num>
Expression<Num> Expression<Num>::cos() const {
    return Expression<Num>(std::make_shared<CosExpr<Num>>(_content));
}

template<typename Num>
Expression<Num> Expression<Num>::ln() const {
    return Expression<Num>(std::make_shared<LnExpr<Num>>(_content));
}

template<typename Num>
Expression<Num> Expression<Num>::exp() const {
    return Expression<Num>(std::make_shared<ExpExpr<Num>>(_content));
}

template<typename Num>
Num Expression<Num>::eval(std::map<std::string, Num> substitution) const {
    return _content->eval(substitution);
}

template<typename Num>
std::string Expression<Num>::to_string() const {
    return _content->to_string();
}

template<typename Num>
Expression<Num> Expression<Num>::sub(std::map<std::string, Num> substitution) const {
    return _content->sub(substitution);
}

template<typename Num>
Expression<Num> Expression<Num>::dif(std::string substitution) const {
    return _content->dif(substitution);
}


template
class Expression<double>;

template
class Expression<std::complex<double>>;


template
class Value<double>;

template
class Value<std::complex<double>>;

template
class Variable<double>;

template
class Variable<std::complex<double>>;


template
class AddExpr<double>;

template
class AddExpr<std::complex<double>>;

template
class MulExpr<double>;

template
class MulExpr<std::complex<double>>;

template
class SubExpr<double>;

template
class SubExpr<std::complex<double>>;

template
class DivExpr<double>;

template
class DivExpr<std::complex<double>>;

template
class PowExpr<double>;

template
class PowExpr<std::complex<double>>;

template
class SinExpr<double>;

template
class SinExpr<std::complex<double>>;

template
class CosExpr<double>;

template
class CosExpr<std::complex<double>>;

template
class ExpExpr<double>;

template
class ExpExpr<std::complex<double>>;

template
class LnExpr<double>;

template
class LnExpr<std::complex<double>>;

template
std::string make_string<double>(double val);

template
double parse_number(const std::string var, bool with_i);

template
std::shared_ptr<ExpressionTempl<double>> parce(std::string var);


