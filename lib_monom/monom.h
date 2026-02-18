#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <algorithm>

template <typename CoefType = double>
class Monom {
private:
    CoefType _coef;
    int _x_deg;
    int _y_deg;
    int _z_deg;

public:
    // Конструкторы
    Monom() : _coef(0), _x_deg(0), _y_deg(0), _z_deg(0) {}

    Monom(CoefType coef, int x_deg = 0, int y_deg = 0, int z_deg = 0)
        : _coef(coef), _x_deg(x_deg), _y_deg(y_deg), _z_deg(z_deg) {
        if (x_deg < 0 || y_deg < 0 || z_deg < 0) {
            throw std::invalid_argument("Degrees cannot be negative");
        }
    }

    Monom(const Monom& other)
        : _coef(other._coef), _x_deg(other._x_deg),
        _y_deg(other._y_deg), _z_deg(other._z_deg) {
    }

    Monom(const std::string& str) : _coef(1), _x_deg(0), _y_deg(0), _z_deg(0) {
        std::string s = str;
        s.erase(remove_if(s.begin(), s.end(), isspace), s.end());

        if (s.empty()) {
            throw std::invalid_argument("Empty string");
        }

        // Парсим коэффициент
        size_t pos = 0;
        if (s[0] == '+' || s[0] == '-') {
            pos = 1;
        }

        while (pos < s.size() && (isdigit(s[pos]) || s[pos] == '.')) {
            pos++;
        }

        if (pos > 0) {
            std::string coef_str = s.substr(0, pos);
            if (coef_str == "+") _coef = 1;
            else if (coef_str == "-") _coef = -1;
            else _coef = std::stod(coef_str);
        }
        else {
            _coef = (s[0] == '-') ? -1 : 1;
            pos = 0;
        }

        // Парсим переменные
        std::regex var_regex("([xyz])(?:\\^(\\d+))?");
        std::string vars_part = s.substr(pos);

        auto vars_begin = std::sregex_iterator(vars_part.begin(), vars_part.end(), var_regex);
        auto vars_end = std::sregex_iterator();

        for (auto i = vars_begin; i != vars_end; ++i) {
            std::smatch match = *i;
            std::string var = match[1];
            int deg = 1;
            if (match[2].matched) {
                deg = std::stoi(match[2]);
            }

            if (var == "x") _x_deg = deg;
            else if (var == "y") _y_deg = deg;
            else if (var == "z") _z_deg = deg;
        }
    }

    // Геттеры
    CoefType get_coef() const { return _coef; }
    int get_x_deg() const { return _x_deg; }
    int get_y_deg() const { return _y_deg; }
    int get_z_deg() const { return _z_deg; }
    int get_total_deg() const { return _x_deg + _y_deg + _z_deg; }

    // Сеттеры
    void set_coef(CoefType coef) { _coef = coef; }
    void set_x_deg(int deg) { _x_deg = deg; }
    void set_y_deg(int deg) { _y_deg = deg; }
    void set_z_deg(int deg) { _z_deg = deg; }

    // Операторы сравнения (проверка подобия)
    bool operator==(const Monom& other) const {
        return _x_deg == other._x_deg &&
            _y_deg == other._y_deg &&
            _z_deg == other._z_deg;
    }

    bool operator!=(const Monom& other) const {
        return !(*this == other);
    }

    // Для сортировки (лексикографический порядок по УБЫВАНИЮ степеней)
    bool operator<(const Monom& other) const {
        if (_x_deg != other._x_deg) return _x_deg > other._x_deg;
        if (_y_deg != other._y_deg) return _y_deg > other._y_deg;
        return _z_deg > other._z_deg;
    }

    // Арифметические операции с мономами
    Monom operator+(const Monom& other) const {
        if (!is_similar(other)) {
            throw std::invalid_argument("Cannot add dissimilar monoms");
        }
        return Monom(_coef + other._coef, _x_deg, _y_deg, _z_deg);
    }

    Monom operator-(const Monom& other) const {
        if (!is_similar(other)) {
            throw std::invalid_argument("Cannot subtract dissimilar monoms");
        }
        return Monom(_coef - other._coef, _x_deg, _y_deg, _z_deg);
    }

    Monom operator*(const Monom& other) const {
        return Monom(_coef * other._coef,
            _x_deg + other._x_deg,
            _y_deg + other._y_deg,
            _z_deg + other._z_deg);
    }

    Monom operator/(const Monom& other) const {
        if (other._coef == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Monom(_coef / other._coef,
            _x_deg - other._x_deg,
            _y_deg - other._y_deg,
            _z_deg - other._z_deg);
    }

    // Операции с константой
    Monom operator*(CoefType scalar) const {
        return Monom(_coef * scalar, _x_deg, _y_deg, _z_deg);
    }

    Monom operator/(CoefType scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Monom(_coef / scalar, _x_deg, _y_deg, _z_deg);
    }

    // Унарный минус
    Monom operator-() const {
        return Monom(-_coef, _x_deg, _y_deg, _z_deg);
    }

    // Операторы с присваиванием
    Monom& operator+=(const Monom& other) {
        if (!is_similar(other)) {
            throw std::invalid_argument("Cannot add dissimilar monoms");
        }
        _coef += other._coef;
        return *this;
    }

    Monom& operator-=(const Monom& other) {
        if (!is_similar(other)) {
            throw std::invalid_argument("Cannot subtract dissimilar monoms");
        }
        _coef -= other._coef;
        return *this;
    }

    Monom& operator*=(const Monom& other) {
        _coef *= other._coef;
        _x_deg += other._x_deg;
        _y_deg += other._y_deg;
        _z_deg += other._z_deg;
        return *this;
    }

    Monom& operator/=(const Monom& other) {
        if (other._coef == 0) {
            throw std::invalid_argument("Division by zero");
        }
        _coef /= other._coef;
        _x_deg -= other._x_deg;
        _y_deg -= other._y_deg;
        _z_deg -= other._z_deg;
        return *this;
    }

    Monom& operator*=(CoefType scalar) {
        _coef *= scalar;
        return *this;
    }

    Monom& operator/=(CoefType scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        _coef /= scalar;
        return *this;
    }

    // Оператор присваивания
    Monom& operator=(const Monom& other) {
        if (this != &other) {
            _coef = other._coef;
            _x_deg = other._x_deg;
            _y_deg = other._y_deg;
            _z_deg = other._z_deg;
        }
        return *this;
    }

    // Вычисление значения в точке
    CoefType evaluate(CoefType x, CoefType y, CoefType z) const {
        return _coef * std::pow(x, _x_deg) *
            std::pow(y, _y_deg) *
            std::pow(z, _z_deg);
    }

    // Вспомогательные методы
    bool is_similar(const Monom& other) const {
        return _x_deg == other._x_deg &&
            _y_deg == other._y_deg &&
            _z_deg == other._z_deg;
    }

    bool is_zero() const {
        return std::abs(_coef) < 1e-10;
    }

    void normalize() {
        if (std::abs(_coef) < 1e-10) {
            _coef = 0;
        }
    }

    // Дружественный оператор вывода
    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const Monom<T>& m);
};

// ИСПРАВЛЕННЫЙ оператор вывода - без использования os.str()
template <typename T>
std::ostream& operator<<(std::ostream& os, const Monom<T>& m) {
    if (std::abs(m._coef) < 1e-10) {
        os << "0";
        return os;
    }

    bool coefficient_printed = false;

    // Вывод коэффициента
    if (m._coef == T(1) && (m._x_deg > 0 || m._y_deg > 0 || m._z_deg > 0)) {
        // Не выводим 1 перед переменными
        coefficient_printed = false;
    }
    else if (m._coef == T(-1) && (m._x_deg > 0 || m._y_deg > 0 || m._z_deg > 0)) {
        os << "-";  // Только минус
        coefficient_printed = true;
    }
    else {
        os << m._coef;
        coefficient_printed = true;
    }

    // Вывод переменных
    if (m._x_deg > 0) {
        os << "x";
        if (m._x_deg > 1) os << "^" << m._x_deg;
    }
    if (m._y_deg > 0) {
        os << "y";
        if (m._y_deg > 1) os << "^" << m._y_deg;
    }
    if (m._z_deg > 0) {
        os << "z";
        if (m._z_deg > 1) os << "^" << m._z_deg;
    }

    // Если нет переменных, но коэффициент не был выведен
    if (m._x_deg == 0 && m._y_deg == 0 && m._z_deg == 0) {
        if (!coefficient_printed) {
            if (m._coef == T(1)) {
                os << "1";
            }
            else if (m._coef == T(-1)) {
                os << "-1";
            }
        }
    }

    return os;
}

// Внешние операторы
template <typename T>
Monom<T> operator*(T scalar, const Monom<T>& m) {
    return m * scalar;
}