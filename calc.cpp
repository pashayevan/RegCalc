#include "calc.h"
#include <vector>
#include <stack>
#include <regex>
#include <stdexcept>
#include <cmath>
#include <iostream>

bool validExpr(const std::string& input) {
    std::regex pattern(R"(\s*([-+]?\d+(\.\d+)?)\s*([+\-*/^]\s*([-+]?\d+(\.\d+)?))*\s*)");
    return std::regex_match(input, pattern);
}

bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

std::vector<std::string> tokenize(const std::string& expr) {
    std::regex tokenRegex(R"(\d+(\.\d+)?|[+\-*/^()])");
    std::sregex_iterator begin(expr.begin(), expr.end(), tokenRegex), end;
    std::vector<std::string> tokens;

    for (auto it = begin; it != end; ++it) {
        tokens.push_back(it->str());
    }
    return tokens;
}

std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;
    std::stack<std::string> opStack;

    for (const auto& token : tokens) {
        if (std::regex_match(token, std::regex(R"(\d+(\.\d+)?)"))) {
            output.push_back(token);
        } else if (isOperator(token)) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(token)) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        } else if (token == "(") {
            opStack.push(token);
        } else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.pop();
        }
    }

    while (!opStack.empty()) {
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}

double operate(double a, double b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Деление на ноль");
        return a / b;
    }
    if (op == "^") return std::pow(a, b);
    throw std::invalid_argument("Некорректный оператор");
}

double evaluatePostfix(const std::vector<std::string>& postfix) {
    std::stack<double> stack;

    for (const auto& token : postfix) {
        if (std::regex_match(token, std::regex(R"(\d+(\.\d+)?)"))) {
            stack.push(std::stod(token));
        } else {
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(operate(a, b, token));
        }
    }

    return stack.top();
}

double calc(const std::string& expr) {
    auto tokens = tokenize(expr);
    auto postfix = infixToPostfix(tokens);
    return evaluatePostfix(postfix);
}

