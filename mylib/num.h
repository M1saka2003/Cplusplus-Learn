#ifndef num_HEAD_
#define num_HEAD_

#include <iostream>
#include <cmath>

namespace mylib {
    template<typename T=long long>
    struct num {

        num() = default;
        explicit num(T &value) noexcept { a = value; }
        explicit num(T &&value) noexcept { a = value; }
        num(const num &value) noexcept { a = value.a; }

        ~num() = default;

        num &operator++() noexcept;
        const num operator++(int) noexcept;
        num operator++() const = delete;

        num &operator--() noexcept;
        const num operator--(int) noexcept;
        num operator--() const = delete;

        num operator+(const T &rhs) noexcept;
        num operator+(const num &rhs) noexcept;

        num operator-(const T &rhs) noexcept;
        num operator-(const num &rhs) noexcept;

        num &operator+=(const T &rhs) noexcept;
        num &operator+=(const num &rhs) noexcept;
        num operator+=(const T &rhs) const = delete;
        num operator+=(const num &rhs) const = delete;

        num &operator-=(const T &rhs) noexcept;
        num &operator-=(const num &rhs) noexcept;
        num operator-=(const T &rhs) const = delete;
        num operator-=(const num &rhs) const = delete;

        num operator*(const T &rhs) noexcept;
        num operator*(const num &rhs) noexcept;

        num &operator*=(const T &rhs) noexcept;
        num &operator*=(const num &rhs) noexcept;
        num operator*=(const T &rhs) const = delete;
        num operator*=(const num &rhs) const = delete;

        num operator^(const T &rhs) noexcept;
        num operator^(const num &rhs) noexcept;

        template<typename T1>
        friend std::istream &operator>>(std::istream &cin, num<T1> &rhs) noexcept;

        template<typename T1>
        friend std::ostream &operator<<(std::ostream &cout, const num<T1> &rhs) noexcept;

    private:
        T a;
    public:
        inline static long long mod = 1e9 + 7;
    };

    template<typename T>
    num<T> num<T>::operator^(const num &rhs) noexcept {
        if constexpr (std::is_same_v<double, T>) { return num<T>{pow(a, rhs.a)}; }
        else {
            T power = rhs.a, base = a;
            T res = 1;
            while (power) {
                if (power & 1) {
                    res = res * base % mod;
                }
                base = base * base % mod;
                power >>= 1;
            }
            return num<T>{res};
        }
    }

    template<typename T>
    num<T> num<T>::operator^(const T &rhs) noexcept {
        if constexpr (std::is_same_v<double, T>) { return num<T>{std::pow(a, rhs)}; }
        else {
            T power = rhs, base = a;
            T res = 1;
            while (power) {
                if (power & 1) {
                    res = res * base % mod;
                }
                base = base * base % mod;
                power >>= 1;
            }
            return num<T>{res};
        }
    }

    template<typename T>
    num<T> &num<T>::operator*=(const num &rhs) noexcept {
        a *= rhs.a;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return *this;
    }

    template<typename T>
    num<T> &num<T>::operator*=(const T &rhs) noexcept {
        a *= rhs;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return *this;
    }

    template<typename T>
    num<T> num<T>::operator*(const num &rhs) noexcept {
        if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) * (rhs.a % mod)) % mod}; }
        return num<T>{a * rhs.a};
    }
    template<typename T>
    num<T> num<T>::operator*(const T &rhs) noexcept {
        if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) * (rhs % mod)) % mod}; }
        return num<T>{a * rhs};
    }

    template<typename T>
    num<T> &num<T>::operator-=(const num &rhs) noexcept {
        a -= rhs.a;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return *this;
    }

    template<typename T>
    num<T> &num<T>::operator-=(const T &rhs) noexcept {
        a -= rhs;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return *this;
    }

    template<typename T>
    num<T> num<T>::operator-(const num &rhs) noexcept {
        if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) - (rhs.a % mod)) % mod}; }
        return num<T>{a + rhs.a};
    }

    template<typename T>
    num<T> num<T>::operator-(const T &rhs) noexcept {
        if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) - (rhs % mod)) % mod}; }
        return num<T>{a - rhs};
    }

    template<typename T>
    num<T> &num<T>::operator+=(const num &rhs) noexcept {
        a += rhs.a;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return *this;
    }

    template<typename T>
    num<T> &num<T>::operator+=(const T &rhs) noexcept {
        a += rhs;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return *this;
    }
    template<typename T1>
    std::istream &operator>>(std::istream &cin, num<T1> &rhs) noexcept {
        return cin >> rhs.a;
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &cout, const num<T1> &rhs) noexcept {
        return cout << rhs.a;
    }

    template<typename T>
    const num<T> num<T>::operator++(int) noexcept {
        const num<T> last = *this;
        ++a;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return last;
    }

    template<typename T>
    num<T> &num<T>::operator++() noexcept {
        a++;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return *this;
    }

    template<typename T>
    num<T> num<T>::operator+(const T &rhs) noexcept {
        if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) + (rhs % mod)) % mod}; }
        return num{a + rhs};
    }

    template<typename T>
    num<T> num<T>::operator+(const num<T> &rhs) noexcept {
        if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) + (rhs.a % mod)) % mod}; }
        return num<T>{a + rhs.a};
    }

    template<typename T>
    num<T> &num<T>::operator--() noexcept {
        --a;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return *this;
    }

    template<typename T>
    const num<T> num<T>::operator--(int) noexcept {
        const num<T> last = *this;
        --a;
        if constexpr (!std::is_same_v<double, T>) { a %= mod; }
        return last;
    }
}

#endif

