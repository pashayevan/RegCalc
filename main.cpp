#include <iostream>
#include <string>
#include <algorithm>
#include "calc.h"

int main() {
    std::string expr;

    while (true) {
        std::cout << "Введите выражение (или напишите 'stop' для выхода): ";
        std::getline(std::cin, expr);

        if (expr == "stop") {
            break;
        }

        try {
            expr.erase(std::remove_if(expr.begin(), expr.end(), ::isspace), expr.end());

            if (!validExpr(expr)) {
                throw std::invalid_argument("Некорректное выражение.");
            }

            double res = calc(expr);
            std::cout << "Результат: " << res << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }

    return 0;
}