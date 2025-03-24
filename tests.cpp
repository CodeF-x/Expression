#include "expression.hpp"

template<typename Num>
void print_standart(Expression<Num> expr, std::map<std::string, Num> args, Num answer, int test_number = -1) {
    auto solution = expr.eval(args);
    std::cout << "=======================================================\n";
    std::cout << "test:: " << test_number << '\n';
    std::cout << "expr:: " << expr.to_string() << '\n';
    std::cout << "solution:: " << solution << '\n';
    std::cout << "answer:: " << answer << '\n';
    std::cout << "verdict:: " << (answer == solution ? "OK" : "FALE") << '\n';
    std::cout << "=======================================================\n";
    return;
}

void test_values() {
    std::cout << "=======================================================\n";
    std::cout << "testing values\n";
    print_standart<rational>(Expression<rational>(1), {}, 1, 1);
    print_standart<rational>(Expression<rational>(-1), {}, -1, 2);
    print_standart<rational>(Expression<rational>(2.6), {}, 2.6, 3);

    print_standart<complex>(Expression<complex>(complex(1)), {}, complex(1), 4);
    print_standart<complex>(Expression<complex>(complex(-1)), {}, complex(-1), 5);
    print_standart<complex>(Expression<complex>(complex(2.6, 0)), {}, complex(2.6, 0), 6);
    std::cout << "///////////////////////////////////////////////////////\n";
    return;
}

void test_additing_subtracting() {
    std::cout << "=======================================================\n";
    std::cout << "testing additing and subtracting\n";
    print_standart<rational>(Expression<rational>(1) + Expression<rational>(3), {}, 1 + 3, 1);
    print_standart<rational>(Expression<rational>(-1) - Expression<rational>(20), {}, -1 - 20, 2);
    print_standart<rational>(Expression<rational>(2.6) + Expression<rational>(11), {}, 2.6 + 11, 3);

    print_standart<complex>(Expression<complex>(complex(1)) - Expression<complex>(complex(3)), {},
                            complex(1) - complex(3), 4);
    print_standart<complex>(Expression<complex>(complex(-1)) + Expression<complex>(complex(11)), {},
                            complex(-1) + complex(11), 5);
    print_standart<complex>(Expression<complex>(complex(2.6, 0)) - Expression<complex>(complex(15, 9)), {},
                            complex(2.6, 0) - complex(15, 9), 6);
    std::cout << "///////////////////////////////////////////////////////\n";
    return;
}

void test_multiplicating_dividing() {
    std::cout << "=======================================================\n";
    std::cout << "testing multiplicating and dividing\n";
    print_standart<rational>(Expression<rational>(1) * Expression<rational>(3), {}, 1 * 3, 1);
    print_standart<rational>(Expression<rational>(-1) / Expression<rational>(20), {}, (double) -1 / 20, 2);
    print_standart<rational>(Expression<rational>(2.6) * Expression<rational>(11), {}, 2.6 * 11, 3);

    print_standart<complex>(Expression<complex>(complex(1)) * Expression<complex>(complex(3)), {},
                            complex(1) * complex(3), 4);
    print_standart<complex>(Expression<complex>(complex(-1)) / Expression<complex>(complex(11)), {},
                            complex(-1) / complex(11), 5);
    print_standart<complex>(Expression<complex>(complex(2.6, 0)) * Expression<complex>(complex(15, 9)), {},
                            complex(2.6, 0) * complex(15, 9), 6);
    std::cout << "///////////////////////////////////////////////////////\n";
    return;
}

void test_power() {
    std::cout << "=======================================================\n";
    std::cout << "testing power operation\n";
    print_standart<rational>(Expression<rational>(1) ^ Expression<rational>(3), {}, std::pow(1, 3), 1);
    print_standart<rational>(Expression<rational>(-1) ^ Expression<rational>(20), {}, std::pow((double) -1, 20), 2);
    print_standart<rational>(Expression<rational>(2.6) ^ Expression<rational>(11), {}, std::pow(2.6, 11), 3);

    print_standart<complex>(Expression<complex>(complex(1)) ^ Expression<complex>(complex(3)), {},
                            std::pow(complex(1), complex(3)), 4);
    print_standart<complex>(Expression<complex>(complex(-1)) ^ Expression<complex>(complex(11)), {},
                            std::pow(complex(-1), complex(11)), 5);
    print_standart<complex>(Expression<complex>(complex(2.6, 0)) ^ Expression<complex>(complex(15, 9)), {},
                            std::pow(complex(2.6, 0), complex(15, 9)), 6);
    std::cout << "///////////////////////////////////////////////////////\n";
    return;
}

void test_sin_cos_ln_exp() {
    std::cout << "=======================================================\n";
    std::cout << "testing sin cos ln exp\n";
    print_standart<rational>(Expression<rational>(1).sin(), {}, std::sin(1), 1);
    print_standart<rational>(Expression<rational>(-1).cos(), {}, std::cos(-1), 2);
    print_standart<rational>(Expression<rational>(2.6).ln(), {}, std::log(2.6), 3);
    print_standart<rational>(Expression<rational>(2.6).exp(), {}, std::exp(2.6), 4);

    print_standart<complex>(Expression<complex>(complex(1)).sin(), {}, std::sin(complex(1)), 5);
    print_standart<complex>(Expression<complex>(complex(-1)).cos(), {}, std::cos(complex(-1)), 6);
    print_standart<complex>(Expression<complex>(complex(2.6, 0)).ln(), {}, std::log(complex(2.6, 0)), 7);
    print_standart<complex>(Expression<complex>(complex(3.1, 11)).exp(), {}, std::exp(complex(3.1, 11)), 8);
    std::cout << "///////////////////////////////////////////////////////\n";
    return;
}

void test_parcing() {
    std::cout << "=======================================================\n";
    std::cout << "testing parcing\n";
    print_standart<rational>(Expression<rational>("3 + 1"), {}, 3 + 1, 1);
    print_standart<rational>(Expression<rational>("5 * 12 - 4/ 5"), {}, 5 * 12 - (double) 4 / 5, 2);
    print_standart<rational>(Expression<rational>("sin(4) ^ 11 * 5"), {}, std::pow(std::sin(4), 11) * 5, 3);

    print_standart<complex>(Expression<complex>("3 + 5i  - (1 + 2i)"), {}, complex(3, 5) - complex(1, 2), 4);
    print_standart<complex>(Expression<complex>("ln(2 + 1i) ^ exp(4 - 3i)"), {},
                            std::pow(std::log(complex(2, 1)), std::exp(complex(4, -3))), 5);
    print_standart<complex>(Expression<complex>("3 * (2 + i + 9 + 2i)"), {},
                            complex(3, 0) * (complex(2, 1) + complex(9, 2)), 6);
    std::cout << "///////////////////////////////////////////////////////\n";
    return;
}

void test_vars_sub() {
    std::cout << "=======================================================\n";
    std::cout << "testing variables and substitution\n";
    std::map<std::string, rational> arg1 = {{"x", 3}};
    std::map<std::string, rational> arg2 = {{"x", 3},
                                            {"y", 2}};
    std::map<std::string, rational> arg3 = {{"y", 11}};
    print_standart<rational>(Expression<rational>("x + 1"), {arg1}, 3 + 1, 1);
    print_standart<rational>(Expression<rational>("5 * 12 - 4/ x"), {arg1}, 5 * 12 - (double) 4 / 3, 2);
    print_standart<rational>(Expression<rational>("sin(x) ^ y * 5").sub(arg3), {arg1}, std::pow(std::sin(3), 11) * 5,
                             3);

    std::map<std::string, complex> c_arg1 = {{"x", complex(2, 5)}};
    std::map<std::string, complex> c_arg2 = {{"x", complex(-2, 8.1)},
                                             {"y", complex(-5.1, 2.5)}};
    std::map<std::string, complex> c_arg3 = {{"y", complex(10, 2)}};

    print_standart<complex>(Expression<complex>("3 + 5i  - (1 + 2i) / x"), c_arg1,
                            complex(3, 5) - complex(1, 2) / complex(2, 5), 4);
    print_standart<complex>(Expression<complex>("ln(x) ^ exp(y + 4 - 3i)"), c_arg2,
                            std::pow(std::log(complex(-2, 8.1)), std::exp(complex(-5.1, 2.5) + complex(4, -3))), 5);
    print_standart<complex>(Expression<complex>("x * (y + x ^ sin(y))").sub(c_arg1), c_arg3,
                            complex(2, 5) *
                            (complex(10, 2) + std::pow(complex(2, 5), std::sin(complex(10, 2)))), 6);
    std::cout << "///////////////////////////////////////////////////////\n";
    return;
}

void test_dif() {
    std::cout << "=======================================================\n";
    std::cout << "testing differentiation\n";
    std::map<std::string, rational> arg1 = {{"x", 3}};
    std::map<std::string, rational> arg2 = {{"y", 2}};
    print_standart<rational>(Expression<rational>("12 * x").dif("x"), {}, 12, 1);
    print_standart<rational>(Expression<rational>("sin(x)").dif("x"), {arg1}, std::cos(3), 2);
    print_standart<rational>(Expression<rational>("y * x").dif("x"), {arg2}, 2, 3);

    std::map<std::string, complex> c_arg1 = {{"x", complex(2, 5)}};
    std::map<std::string, complex> c_arg2 = {{"x", complex(2, 5)},
                                             {"y", complex(-5.1, 2.5)}};
    print_standart<complex>(Expression<complex>("x ^ 3").dif("x"), c_arg1,
                            complex(3, 0) * std::pow(complex(2, 5), 2), 4);
    print_standart<complex>(Expression<complex>("ln(x)").dif("x"), c_arg1,
                            complex(1, 0) / complex(2, 5), 5);
    print_standart<complex>(Expression<complex>(" x  ^ y").dif("x"), c_arg2,
                            complex(-5.1, 2.5) * std::pow(complex(2, 5), complex(-5.1, 2.5) - complex(1, 0)), 6);
    std::cout << "///////////////////////////////////////////////////////\n";
    return;
}

int main() {
    test_values();
    test_additing_subtracting();
    test_multiplicating_dividing();
    test_power();
    test_sin_cos_ln_exp();
    test_parcing();
    test_vars_sub();
    test_dif();
    return 0;
}
