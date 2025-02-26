#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calc.h"

TEST_CASE("Проверка validExpr") {
    CHECK(validExpr("5*4"));
    CHECK(validExpr("7.2+3"));
    CHECK_FALSE(validExpr("4*5#"));
    CHECK_FALSE(validExpr("invalid"));
}

TEST_CASE("Проверка isOp") {
    CHECK(isOp('+'));
    CHECK(isOp('-'));
    CHECK(isOp('/'));
    CHECK(isOp('*'));
    CHECK(isOp('^'));
    CHECK_FALSE(isOp('&'));
    CHECK_FALSE(isOp('z'));
}

TEST_CASE("Проверка operate") {
    CHECK(operate(5, 2, '+') == 7);
    CHECK(operate(8, 2, '-') == 6);
    CHECK(operate(6, 3, '*') == 18);
    CHECK(operate(9, 3, '/') == 3);
    CHECK(operate(3, 4, '^') == 81);
    CHECK_THROWS_AS(operate(5, 0, '/'), std::runtime_error);
    CHECK_THROWS_AS(operate(7, 3, '%'), std::invalid_argument);
}

TEST_CASE("Проверка calc") {
    CHECK(calc("4+3^2") == 13);
    CHECK(calc("8--2^3") == -4);
    CHECK(calc("12-6*2") == 0);
    CHECK(calc("3^2+5") == 14);
    CHECK(calc("6/0.25") == 24);
    CHECK_THROWS_AS(calc("2+3*"), std::invalid_argument);
    CHECK_THROWS_AS(calc("4//3"), std::invalid_argument);
    CHECK_THROWS_AS(calc("5^"), std::invalid_argument);
    CHECK_THROWS_AS(calc("4+3/0"), std::runtime_error);
}

TEST_CASE("Проверка некорректных выражений") {
    CHECK_THROWS_AS(calc("5+4++3"), std::invalid_argument);
    CHECK_THROWS_AS(calc("4---3"), std::invalid_argument);
    CHECK_THROWS_AS(calc("7*2#5"), std::invalid_argument);
    CHECK_THROWS_AS(calc("3.1.2+4"), std::invalid_argument);
}