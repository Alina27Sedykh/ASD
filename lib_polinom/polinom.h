#pragma once
#include "Monom.h"
#include "List.h"  // Подключаем ваш список
#include <sstream>
#include <regex>
#include <vector>
#include <algorithm>

template <typename CoefType = double>
class Polynom {
private:
    List<Monom<CoefType>> _monoms;

    // Вспомогательные методы
    void simplify() {
        if (_monoms.is_empty()) return;

        List<Monom<CoefType>> result;

        // Используем обычный итератор
        for (auto it = _monoms.begin(); it != _monoms.end(); ++it) {
            Monom<CoefType> current = *it;
            bool found = false;

            // Ищем подобный в результате
            for (auto res_it = result.begin(); res_it != result.end(); ++res_it) {
                if (current.is_similar(*res_it)) {
                    Monom<CoefType> sum = current + *res_it;
                    *res_it = sum;
                    found = true;
                    break;
                }
            }

            if (!found) {
                result.push_back(current);
            }
        }

        // Очищаем текущий список
        _monoms.clear();

        // Добавляем ненулевые мономы с сортировкой
        for (auto it = result.begin(); it != result.end(); ++it) {
            if (!(*it).is_zero()) {
                insert_sorted(*it);
            }
        }
    }

    void insert_sorted(const Monom<CoefType>& m) {
        if (_monoms.is_empty()) {
            _monoms.push_back(m);
            return;
        }

        auto it = _monoms.begin();
        int pos = 0;

        while (it != _monoms.end() && *it < m) {
            ++it;
            ++pos;
        }

        if (it == _monoms.end()) {
            _monoms.push_back(m);
        }
        else {
            _monoms.insert(pos, m);
        }
    }

public:
    // Конструкторы
    Polynom() {}

    Polynom(const Monom<CoefType>& m) {
        if (!m.is_zero()) {
            _monoms.push_back(m);
        }
    }

    Polynom(const std::string& str) {
        std::string s = str;
        s.erase(remove_if(s.begin(), s.end(), isspace), s.end());

        if (s.empty()) return;

        // Разбиваем на мономы
        std::vector<std::string> monom_strs;
        size_t start = 0;

        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i] == '+' || s[i] == '-') {
                monom_strs.push_back(s.substr(start, i - start));
                start = i;
            }
        }
        monom_strs.push_back(s.substr(start));

        // Создаем мономы
        for (const auto& m_str : monom_strs) {
            try {
                Monom<CoefType> m(m_str);
                if (!m.is_zero()) {
                    insert_sorted(m);
                }
            }
            catch (...) {
                // Игнорируем ошибки
            }
        }

        simplify();
    }

    Polynom(const Polynom& other) {
        // ТЕПЕРЬ МОЖНО ИСПОЛЬЗОВАТЬ const begin/end!
        for (auto it = other._monoms.begin(); it != other._monoms.end(); ++it) {
            _monoms.push_back(*it);
        }
    }

    // Оператор присваивания
    Polynom& operator=(const Polynom& other) {
        if (this != &other) {
            _monoms.clear();
            for (auto it = other._monoms.begin(); it != other._monoms.end(); ++it) {
                _monoms.push_back(*it);
            }
        }
        return *this;
    }

    // Арифметические операции
    Polynom operator+(const Polynom& other) const {
        Polynom result = *this;

        // ТЕПЕРЬ МОЖНО ИСПОЛЬЗОВАТЬ const begin/end для other!
        for (auto it = other._monoms.begin(); it != other._monoms.end(); ++it) {
            result.insert_sorted(*it);
        }
        result.simplify();
        return result;
    }

    Polynom operator-(const Polynom& other) const {
        Polynom result = *this;

        for (auto it = other._monoms.begin(); it != other._monoms.end(); ++it) {
            result.insert_sorted(-(*it));
        }
        result.simplify();
        return result;
    }

    Polynom operator*(const Polynom& other) const {
        Polynom result;

        // ТЕПЕРЬ МОЖНО ИСПОЛЬЗОВАТЬ const begin/end для this и other!
        for (auto it1 = _monoms.begin(); it1 != _monoms.end(); ++it1) {
            for (auto it2 = other._monoms.begin(); it2 != other._monoms.end(); ++it2) {
                result.insert_sorted((*it1) * (*it2));
            }
        }

        result.simplify();
        return result;
    }

    Polynom operator*(CoefType scalar) const {
        Polynom result;

        for (auto it = _monoms.begin(); it != _monoms.end(); ++it) {
            result.insert_sorted((*it) * scalar);
        }

        return result;
    }

    Polynom operator/(CoefType scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }

        Polynom result;

        for (auto it = _monoms.begin(); it != _monoms.end(); ++it) {
            result.insert_sorted((*it) / scalar);
        }

        return result;
    }

    Polynom operator-() const {
        Polynom result;

        for (auto it = _monoms.begin(); it != _monoms.end(); ++it) {
            result.insert_sorted(-(*it));
        }

        return result;
    }

    // Операторы с присваиванием
    Polynom& operator+=(const Polynom& other) {
        *this = *this + other;
        return *this;
    }

    Polynom& operator-=(const Polynom& other) {
        *this = *this - other;
        return *this;
    }

    Polynom& operator*=(const Polynom& other) {
        *this = *this * other;
        return *this;
    }

    Polynom& operator*=(CoefType scalar) {
        *this = *this * scalar;
        return *this;
    }

    Polynom& operator/=(CoefType scalar) {
        *this = *this / scalar;
        return *this;
    }

    // Операторы сравнения
    bool operator==(const Polynom& other) const {
        if (size() != other.size()) {
            return false;
        }

        // ТЕПЕРЬ МОЖНО ИСПОЛЬЗОВАТЬ const begin/end!
        auto it1 = _monoms.begin();
        auto it2 = other._monoms.begin();

        while (it1 != _monoms.end() && it2 != other._monoms.end()) {
            // ВАЖНО: разыменовываем итераторы правильно
            if ((*it1) != (*it2) ||
                std::abs((*it1).get_coef() - (*it2).get_coef()) > 1e-10) {
                return false;
            }
            ++it1;
            ++it2;
        }

        return true;
    }

    bool operator!=(const Polynom& other) const {
        return !(*this == other);
    }

    // Вычисление значения в точке
    CoefType evaluate(CoefType x, CoefType y, CoefType z) const {
        CoefType result = 0;

        for (auto it = _monoms.begin(); it != _monoms.end(); ++it) {
            result += (*it).evaluate(x, y, z);  // или it->evaluate(x, y, z)
        }

        return result;
    }

    // Методы доступа
    bool is_empty() const { return _monoms.is_empty(); }
    int size() const { return _monoms.size(); }

    // Дружественный оператор вывода
    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const Polynom<T>& p);
};

// Реализация оператора вывода
template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynom<T>& p) {
    if (p._monoms.is_empty()) {
        os << "0";
        return os;
    }

    bool first = true;

    // ТЕПЕРЬ МОЖНО ИСПОЛЬЗОВАТЬ const begin/end!
    for (auto it = p._monoms.begin(); it != p._monoms.end(); ++it) {
        if (!first) {
            if ((*it).get_coef() > 0) {  // или it->get_coef() > 0
                os << "+";
            }
        }
        os << *it;  // Оператор << для Monom
        first = false;
    }

    return os;
}

// Внешние операторы
template <typename T>
Polynom<T> operator*(T scalar, const Polynom<T>& p) {
    return p * scalar;
}