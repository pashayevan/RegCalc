#include "calc.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>


bool validExpr(const std::string& input) {
    for (char c : input) {
        if (!(std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '.' || std::isspace(c))) {
            return false;
        }
    }
    return true;
}

bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}


double operate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw std::runtime_error("Division by zero");
            }
            return a / b;
        case '^': return std::pow(a, b);
        default: throw std::invalid_argument("Invalid operator");
    }
}


double calc(const std::string& expr) {
    std::vector<double> nums;
    std::vector<char> ops;
    std::string currNum;

    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];

        if (std::isdigit(c) || c == '.') {
            currNum += c;
        } else if (c == '-' && (i == 0 || isOp(expr[i - 1]) || std::isspace(expr[i - 1]))) {
            // Обработка отрицательных чисел
            currNum += c;
        } else {
            if (!currNum.empty()) {
                nums.push_back(std::stod(currNum));
                currNum.clear();
            }

            if (isOp(c)) {
                ops.push_back(c);
            } else if (!std::isspace(c)) {
                throw std::invalid_argument("Invalid character in expression");
            }
        }
    }

    if (!currNum.empty()) {
        nums.push_back(std::stod(currNum));
    }

    if (nums.size() != ops.size() + 1) {
        throw std::invalid_argument("Mismatched numbers and operators");
    }

    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == '^') {
            nums[i] = operate(nums[i], nums[i + 1], ops[i]);
            nums.erase(nums.begin() + i + 1);
            ops.erase(ops.begin() + i);
            --i;
        }
    }


    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == '*' || ops[i] == '/') {
            nums[i] = operate(nums[i], nums[i + 1], ops[i]);
            nums.erase(nums.begin() + i + 1);
            ops.erase(ops.begin() + i);
            --i;
        }
    }


    for (size_t i = 0; i < ops.size(); ++i) {
        nums[i] = operate(nums[i], nums[i + 1], ops[i]);
        nums.erase(nums.begin() + i + 1);
        ops.erase(ops.begin() + i);
        --i;
    }

    return nums[0];
}