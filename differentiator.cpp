#include <iostream>
#include <string>
#include "expression.hpp"


void help() {
    std::cout << "Commands:\n";
    std::cout << "  differentiator --eval 'expression' x=a, y=b, ...\n";
    std::cout << "  differentiator --diff 'expression' --by var\n";
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        help();
        return 1;
    }

    std::string cmd = argv[1];
    std::string expr = argv[2];

    if (cmd == "--eval") {
        std::map<std::string, complex> c_vars;
        std::map<std::string, rational> r_vars;
        bool is_complex = false;
        std::string check = argv[3];
        if (check[check.size() - 1] == ')') is_complex = true;
        for (int i = 3; i < argc; i++) {
            std::string arg = argv[i];
            int eq = arg.find('=');
            if (eq == std::string::npos) {
                help();
                return 1;
            }
            if (is_complex) {
                int com = arg.find(',');
                if (com == std::string::npos) {
                    std::cout << "Wrong complex name. Should be (x,y).";
                    return 1;
                }
                std::string var = arg.substr(0, eq);
                std::string re = arg.substr(eq + 2, com - eq - 2);
                std::string im = arg.substr(com + 1, arg.size() - com - 1);
                c_vars[var] = complex(std::stod(re), std::stod(im));
            } else {
                std::string var = arg.substr(0, eq);
                std::string re = arg.substr(eq + 1, arg.size() - eq);
                r_vars[var] = std::stod(re);
            }
        }
        if (is_complex) {
            std::cout << Expression<complex>(expr).eval(c_vars);
        } else {
            std::cout << Expression<rational>(expr).eval(r_vars);
        }

    } else if (cmd == "--diff" && std::string(argv[3]) == "--by") { ;
        std::string var = argv[4];
        std::cout << Expression<complex>(expr).dif(var).to_string() << std::endl;
    } else {
        help();
        return 1;
    }


    return 0;
}