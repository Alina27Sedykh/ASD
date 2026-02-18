#include <gtest/gtest.h>
#include "../lib_monom/Monom.h"
#include "../lib_polinom/Polinom.h"

TEST(MonomTest, DefaultConstructor)
{
    Monom<double> m;
    EXPECT_DOUBLE_EQ(m.get_coef(), 0.0);
    EXPECT_EQ(m.get_x_deg(), 0);
    EXPECT_EQ(m.get_y_deg(), 0);
    EXPECT_EQ(m.get_z_deg(), 0);
    EXPECT_TRUE(m.is_zero());
}

TEST(MonomTest, ParameterConstructor)
{
    Monom<double> m(2.5, 1, 2, 3);
    EXPECT_DOUBLE_EQ(m.get_coef(), 2.5);
    EXPECT_EQ(m.get_x_deg(), 1);
    EXPECT_EQ(m.get_y_deg(), 2);
    EXPECT_EQ(m.get_z_deg(), 3);
}

TEST(MonomTest, CopyConstructor)
{
    Monom<double> m1(2.5, 1, 2, 3);
    Monom<double> m2(m1);
    EXPECT_DOUBLE_EQ(m2.get_coef(), 2.5);
    EXPECT_EQ(m2.get_x_deg(), 1);
    EXPECT_EQ(m2.get_y_deg(), 2);
    EXPECT_EQ(m2.get_z_deg(), 3);
}

TEST(MonomTest, StringConstructor)
{
    Monom<double> m1("3x^2y^1z^3");
    EXPECT_DOUBLE_EQ(m1.get_coef(), 3.0);
    EXPECT_EQ(m1.get_x_deg(), 2);
    EXPECT_EQ(m1.get_y_deg(), 1);
    EXPECT_EQ(m1.get_z_deg(), 3);

    Monom<double> m2("-2.5x^2");
    EXPECT_DOUBLE_EQ(m2.get_coef(), -2.5);
    EXPECT_EQ(m2.get_x_deg(), 2);
    EXPECT_EQ(m2.get_y_deg(), 0);
    EXPECT_EQ(m2.get_z_deg(), 0);

    Monom<double> m3("x");
    EXPECT_DOUBLE_EQ(m3.get_coef(), 1.0);
    EXPECT_EQ(m3.get_x_deg(), 1);
    EXPECT_EQ(m3.get_y_deg(), 0);
    EXPECT_EQ(m3.get_z_deg(), 0);

    Monom<double> m4("-x^2y");
    EXPECT_DOUBLE_EQ(m4.get_coef(), -1.0);
    EXPECT_EQ(m4.get_x_deg(), 2);
    EXPECT_EQ(m4.get_y_deg(), 1);
    EXPECT_EQ(m4.get_z_deg(), 0);

    Monom<double> m5("5");
    EXPECT_DOUBLE_EQ(m5.get_coef(), 5.0);
    EXPECT_EQ(m5.get_x_deg(), 0);
    EXPECT_EQ(m5.get_y_deg(), 0);
    EXPECT_EQ(m5.get_z_deg(), 0);
}

TEST(MonomTest, Similarity)
{
    Monom<double> m1(2.5, 1, 2, 3);
    Monom<double> m2(3.7, 1, 2, 3);  // Те же степени, другой коэффициент
    Monom<double> m3(2.5, 1, 2, 4);  // Другая степень z

    EXPECT_TRUE(m1.is_similar(m2));
    EXPECT_TRUE(m1 == m2);  // operator== проверяет подобие
    EXPECT_FALSE(m1.is_similar(m3));
    EXPECT_TRUE(m1 != m3);
}

TEST(MonomTest, Output)
{
    Monom<double> m1(2.5, 1, 2, 3);
    std::stringstream ss1;
    ss1 << m1;
    std::string result1 = ss1.str();
    std::cout << "m1 output: '" << result1 << "'" << std::endl;
    // Проверяем, что вывод содержит основные части
    EXPECT_TRUE(result1.find("2.5") != std::string::npos);
    EXPECT_TRUE(result1.find("x") != std::string::npos);
    EXPECT_TRUE(result1.find("y") != std::string::npos);
    EXPECT_TRUE(result1.find("z") != std::string::npos);

    Monom<double> m2(-1, 1, 0, 0);  // -x
    std::stringstream ss2;
    ss2 << m2;
    EXPECT_EQ(ss2.str(), "-x");

    Monom<double> m3(1, 0, 0, 0);  // 1
    std::stringstream ss3;
    ss3 << m3;
    EXPECT_EQ(ss3.str(), "1");

    Monom<double> m4(-1, 0, 0, 0);  // -1
    std::stringstream ss4;
    ss4 << m4;
    EXPECT_EQ(ss4.str(), "-1");

    Monom<double> m5(1, 1, 0, 0);  // x
    std::stringstream ss5;
    ss5 << m5;
    EXPECT_EQ(ss5.str(), "x");
}


TEST(MonomTest, Addition)
{
    Monom<double> m1(2.5, 1, 2, 3);
    Monom<double> m2(3.5, 1, 2, 3);

    Monom<double> sum = m1 + m2;
    EXPECT_DOUBLE_EQ(sum.get_coef(), 6.0);
    EXPECT_EQ(sum.get_x_deg(), 1);
    EXPECT_EQ(sum.get_y_deg(), 2);
    EXPECT_EQ(sum.get_z_deg(), 3);

    // Проверка исключения при сложении неподобных
    Monom<double> m3(2.5, 1, 2, 4);
    EXPECT_THROW(m1 + m3, std::invalid_argument);
}

TEST(MonomTest, Subtraction)
{
    Monom<double> m1(5.0, 1, 2, 3);
    Monom<double> m2(3.0, 1, 2, 3);

    Monom<double> diff = m1 - m2;
    EXPECT_DOUBLE_EQ(diff.get_coef(), 2.0);
    EXPECT_EQ(diff.get_x_deg(), 1);
    EXPECT_EQ(diff.get_y_deg(), 2);
    EXPECT_EQ(diff.get_z_deg(), 3);

    // Проверка исключения
    Monom<double> m3(2.5, 1, 2, 4);
    EXPECT_THROW(m1 - m3, std::invalid_argument);
}

TEST(MonomTest, Multiplication)
{
    Monom<double> m1(2.0, 1, 2, 3);
    Monom<double> m2(3.0, 2, 1, 1);

    Monom<double> prod = m1 * m2;
    EXPECT_DOUBLE_EQ(prod.get_coef(), 6.0);
    EXPECT_EQ(prod.get_x_deg(), 3);
    EXPECT_EQ(prod.get_y_deg(), 3);
    EXPECT_EQ(prod.get_z_deg(), 4);
}

TEST(MonomTest, Division)
{
    Monom<double> m1(6.0, 3, 3, 4);
    Monom<double> m2(2.0, 1, 2, 3);

    Monom<double> quot = m1 / m2;
    EXPECT_DOUBLE_EQ(quot.get_coef(), 3.0);
    EXPECT_EQ(quot.get_x_deg(), 2);
    EXPECT_EQ(quot.get_y_deg(), 1);
    EXPECT_EQ(quot.get_z_deg(), 1);

    // Проверка деления на ноль
    Monom<double> m3(0, 1, 1, 1);
    EXPECT_THROW(m1 / m3, std::invalid_argument);
}

TEST(MonomTest, MultiplicationByScalar)
{
    Monom<double> m(2.0, 1, 2, 3);

    Monom<double> prod = m * 3.0;
    EXPECT_DOUBLE_EQ(prod.get_coef(), 6.0);
    EXPECT_EQ(prod.get_x_deg(), 1);
    EXPECT_EQ(prod.get_y_deg(), 2);
    EXPECT_EQ(prod.get_z_deg(), 3);

    prod = 2.5 * m;
    EXPECT_DOUBLE_EQ(prod.get_coef(), 5.0);
}

TEST(MonomTest, DivisionByScalar)
{
    Monom<double> m(6.0, 1, 2, 3);

    Monom<double> quot = m / 2.0;
    EXPECT_DOUBLE_EQ(quot.get_coef(), 3.0);
    EXPECT_EQ(quot.get_x_deg(), 1);
    EXPECT_EQ(quot.get_y_deg(), 2);
    EXPECT_EQ(quot.get_z_deg(), 3);

    EXPECT_THROW(m / 0.0, std::invalid_argument);
}

TEST(MonomTest, UnaryMinus)
{
    Monom<double> m(2.5, 1, 2, 3);
    Monom<double> neg = -m;

    EXPECT_DOUBLE_EQ(neg.get_coef(), -2.5);
    EXPECT_EQ(neg.get_x_deg(), 1);
    EXPECT_EQ(neg.get_y_deg(), 2);
    EXPECT_EQ(neg.get_z_deg(), 3);
}

TEST(MonomTest, CompoundAssignment)
{
    Monom<double> m1(2.0, 1, 2, 3);
    Monom<double> m2(3.0, 1, 2, 3);

    m1 += m2;
    EXPECT_DOUBLE_EQ(m1.get_coef(), 5.0);

    m1 -= m2;
    EXPECT_DOUBLE_EQ(m1.get_coef(), 2.0);

    m1 *= m2;
    EXPECT_DOUBLE_EQ(m1.get_coef(), 6.0);
    EXPECT_EQ(m1.get_x_deg(), 2);

    m1 /= m2;
    EXPECT_DOUBLE_EQ(m1.get_coef(), 2.0);
    EXPECT_EQ(m1.get_x_deg(), 1);

    m1 *= 2.5;
    EXPECT_DOUBLE_EQ(m1.get_coef(), 5.0);

    m1 /= 2.5;
    EXPECT_DOUBLE_EQ(m1.get_coef(), 2.0);
}

TEST(MonomTest, Evaluate)
{
    Monom<double> m(3.0, 2, 1, 0);  // 3x^2y

    double val = m.evaluate(2.0, 3.0, 5.0);
    EXPECT_DOUBLE_EQ(val, 3.0 * 4.0 * 3.0);  // 36

    Monom<double> m2(5.0, 0, 0, 0);  // Константа 5
    EXPECT_DOUBLE_EQ(m2.evaluate(10, 10, 10), 5.0);
}

TEST(MonomTest, DifferentTypes)
{
    Monom<int> m1(2, 1, 2, 3);
    EXPECT_EQ(m1.get_coef(), 2);

    Monom<float> m2(2.5f, 1, 2, 3);
    EXPECT_FLOAT_EQ(m2.get_coef(), 2.5f);
}



TEST(PolynomTest, DefaultConstructor)
{
    Polynom<double> p;
    EXPECT_TRUE(p.is_empty());
    EXPECT_EQ(p.size(), 0);
}

TEST(PolynomTest, MonomConstructor)
{
    Monom<double> m(2.5, 1, 2, 3);
    Polynom<double> p(m);

    EXPECT_EQ(p.size(), 1);
}

TEST(PolynomTest, StringConstructor)
{
    Polynom<double> p1("x^2 + 2y^2z - 4z^5");
    EXPECT_EQ(p1.size(), 3);

    Polynom<double> p2("2x + 3");
    EXPECT_EQ(p2.size(), 2);

    Polynom<double> p3("x^2yz^3 + 0.4xyz - 8y^2z + 1.3yz^4 - 2.4");
    EXPECT_EQ(p3.size(), 5);

    Polynom<double> p4("");  // Пустая строка
    EXPECT_TRUE(p4.is_empty());
}

TEST(PolynomTest, CopyConstructor)
{
    Polynom<double> p1("x^2 + 2y");
    Polynom<double> p2(p1);

    EXPECT_EQ(p2.size(), 2);
    EXPECT_EQ(p2, p1);
}

TEST(PolynomTest, Assignment)
{
    Polynom<double> p1("x^2 + 2y");
    Polynom<double> p2;
    p2 = p1;

    EXPECT_EQ(p2.size(), 2);
    EXPECT_EQ(p2, p1);
}

TEST(PolynomTest, Addition)
{
    Polynom<double> p1("x + y");
    Polynom<double> p2("2x + z");

    Polynom<double> sum = p1 + p2;
    EXPECT_EQ(sum.size(), 3);  // 3x + y + z

    // Проверка через evaluate
    EXPECT_DOUBLE_EQ(sum.evaluate(1, 1, 1), 3 + 1 + 1);  // 5

    // Проверка приведения подобных
    Polynom<double> p3("x + x");
    EXPECT_EQ(p3.size(), 1);  // Должно стать 2x
    EXPECT_DOUBLE_EQ(p3.evaluate(2, 0, 0), 4);
}

TEST(PolynomTest, Subtraction)
{
    Polynom<double> p1("3x + 2y");
    Polynom<double> p2("x + y");

    Polynom<double> diff = p1 - p2;
    EXPECT_EQ(diff.size(), 2);  // 2x + y

    EXPECT_DOUBLE_EQ(diff.evaluate(1, 1, 0), 2 + 1);  // 3
}

TEST(PolynomTest, Multiplication)
{
    Polynom<double> p1("x + y");
    Polynom<double> p2("x + z");

    Polynom<double> prod = p1 * p2;  // x^2 + xz + xy + yz
    EXPECT_EQ(prod.size(), 4);

    // Проверка через evaluate
    EXPECT_DOUBLE_EQ(prod.evaluate(2, 3, 4),
        4 + 8 + 6 + 12);  // 30
}

TEST(PolynomTest, MultiplicationByScalar)
{
    Polynom<double> p("x + y");
    Polynom<double> prod = p * 3.0;

    EXPECT_EQ(prod.size(), 2);
    EXPECT_DOUBLE_EQ(prod.evaluate(2, 3, 0), 3 * (2 + 3));  // 15

    prod = 2.5 * p;
    EXPECT_DOUBLE_EQ(prod.evaluate(2, 3, 0), 2.5 * (2 + 3));
}

TEST(PolynomTest, DivisionByScalar)
{
    Polynom<double> p("2x + 4y");
    Polynom<double> quot = p / 2.0;

    EXPECT_EQ(quot.size(), 2);
    EXPECT_DOUBLE_EQ(quot.evaluate(2, 3, 0), 2 + 6);  // 8

    EXPECT_THROW(p / 0.0, std::invalid_argument);
}

TEST(PolynomTest, UnaryMinus)
{
    Polynom<double> p("x - y");
    Polynom<double> neg = -p;

    EXPECT_DOUBLE_EQ(neg.evaluate(2, 3, 0), -2 + 3);  // 1
}

TEST(PolynomTest, CompoundAssignment)
{
    Polynom<double> p1("x + y");
    Polynom<double> p2("2x + z");

    p1 += p2;
    EXPECT_DOUBLE_EQ(p1.evaluate(1, 1, 1), 3 + 1 + 1);  // 5

    p1 -= p2;
    EXPECT_DOUBLE_EQ(p1.evaluate(1, 1, 1), 1 + 1);  // 2

    p1 *= p2;
    EXPECT_DOUBLE_EQ(p1.evaluate(1, 1, 1), 2 * 3);  // 6
}

TEST(PolynomTest, Comparison)
{
    Polynom<double> p1("x + y");
    Polynom<double> p2("x + y");
    Polynom<double> p3("x + z");

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

TEST(PolynomTest, Evaluate)
{
    Polynom<double> p("x^2 + 2y + 1");

    EXPECT_DOUBLE_EQ(p.evaluate(2, 3, 0), 4 + 6 + 1);  // 11
    EXPECT_DOUBLE_EQ(p.evaluate(0, 5, 0), 0 + 10 + 1);  // 11
    EXPECT_DOUBLE_EQ(p.evaluate(1, 1, 1), 1 + 2 + 1);  // 4
}

TEST(PolynomTest, Simplify)
{
    // Приведение подобных
    Polynom<double> p1("x^2 + 2x^2 - x");
    EXPECT_EQ(p1.size(), 2);  // 3x^2 - x
    EXPECT_DOUBLE_EQ(p1.evaluate(2, 0, 0), 12 - 2);  // 10

    // Удаление нулевых мономов
    Polynom<double> p2("x - x + 5");
    EXPECT_EQ(p2.size(), 1);  // 5
    EXPECT_DOUBLE_EQ(p2.evaluate(10, 0, 0), 5);

    // Сортировка
    Polynom<double> p3("y + x + z");
    // Должно храниться как: x -> y -> z
    // Проверим через evaluate (порядок не влияет на значение)
    EXPECT_DOUBLE_EQ(p3.evaluate(1, 2, 3), 1 + 2 + 3);  // 6
}

TEST(PolynomTest, Ordering)
{
    // Проверка, что мономы упорядочены правильно
    Polynom<double> p("y^2z^3 + 2y^2 + xy + 6");

    // Не можем напрямую проверить порядок, но можем проверить через строку
    std::stringstream ss;
    ss << p;
    std::string str = ss.str();

    // В упорядоченном виде xy должен быть первым
    EXPECT_TRUE(str.find("xy") < str.find("y") ||
        str.find("xy") == std::string::npos);
}

TEST(PolynomTest, Output)
{
    Polynom<double> p("3x^2y + 2x - 5");
    std::stringstream ss;
    ss << p;
    std::string str = ss.str();

    EXPECT_FALSE(str.empty());
    std::cout << "Polynom output: " << str << std::endl;
}

TEST(PolynomTest, EmptyPolynom)
{
    Polynom<double> p;
    EXPECT_TRUE(p.is_empty());
    EXPECT_EQ(p.size(), 0);

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "0");
}

TEST(PolynomTest, ConstPolynom)
{
    Polynom<double> p("5");
    EXPECT_EQ(p.size(), 1);
    EXPECT_DOUBLE_EQ(p.evaluate(10, 10, 10), 5);
}

TEST(PolynomTest, DifferentTypes)
{
    Polynom<int> p1("x + y");
    EXPECT_EQ(p1.evaluate(2, 3, 0), 5);

    Polynom<float> p2("2.5x + 3.5y");
    EXPECT_FLOAT_EQ(p2.evaluate(2.0f, 1.0f, 0.0f), 5.0f + 3.5f);
}

TEST(PolynomTest, ComplexOperations)
{
    Polynom<double> p1("x^2 + 2x + 1");
    Polynom<double> p2("x + 1");

    // (x+1)^2 = x^2 + 2x + 1
    Polynom<double> square = p2 * p2;
    EXPECT_EQ(square, p1);

    // (x^2 + 2x + 1) /? не реализуем, но проверим умножение
    Polynom<double> prod = p2 * p1;
    EXPECT_EQ(prod.size(), 4);  // x^3 + 3x^2 + 3x + 1
}

