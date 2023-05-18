#ifndef MYLIB_NUM_H_
#define MYLIB_NUM_H_

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

        num &operator++() noexcept {
            a++;
            if constexpr (!std::is_same_v<double, T>) { a %= mod; }
            return *this;
        }

        const num operator++(int) noexcept {
            const num<T> last = *this;
            ++a;
            if constexpr (!std::is_same_v<double, T>) { a %= mod; }
            return last;
        }

        num operator++() const = delete;

        num &operator--() noexcept {
            --a;
            if constexpr (!std::is_same_v<double, T>) { a %= mod; }
            return *this;
        }

        const num operator--(int) noexcept {
            const num<T> last = *this;
            --a;
            if constexpr (!std::is_same_v<double, T>) { a %= mod; }
            return last;
        }

        num operator--() const = delete;

        num operator+(const T &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) + (rhs % mod)) % mod}; }
            return num{a + rhs};
        }

        num operator+(const num &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) + (rhs.a % mod)) % mod}; }
            return num<T>{a + rhs.a};
        }

        num operator-(const T &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) - (rhs % mod)) % mod}; }
            return num<T>{a - rhs};
        }

        num operator-(const num &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) - (rhs.a % mod)) % mod}; }
            return num<T>{a + rhs.a};
        }

        num &operator+=(const T &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { a = ((a % mod) + (rhs % mod)) % mod; }
            else a += rhs;
            return *this;
        }

        num &operator+=(const num &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { a = ((a % mod) + (rhs.a % mod)) % mod; }
            else a += rhs.a;
            return *this;
        }

        num operator+=(const T &rhs) const = delete;
        num operator+=(const num &rhs) const = delete;

        num &operator-=(const T &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { a = ((a % mod) - (rhs % mod)) % mod; }
            else a -= rhs;
            return *this;
        }

        num &operator-=(const num &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { a = ((a % mod) - (rhs.a % mod)) % mod; }
            else a -= rhs.a;
            return *this;
        }

        num operator-=(const T &rhs) const = delete;
        num operator-=(const num &rhs) const = delete;

        num operator*(const T &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) * (rhs % mod)) % mod}; }
            return num<T>{a * rhs};
        }

        num operator*(const num &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { return num<T>{((a % mod) * (rhs.a % mod)) % mod}; }
            return num<T>{a * rhs.a};
        }

        num &operator*=(const T &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { a = ((a % mod) * (rhs % mod)) % mod; }
            else a *= rhs;
            return *this;
        }

        num &operator*=(const num &rhs) noexcept {
            if constexpr (!std::is_same_v<double, T>) { a = ((a % mod) * (rhs.a % mod)) % mod; }
            else a *= rhs;
            return *this;
        }

        bool operator>(const T &rhs) noexcept {
            return a > rhs;
        }

        bool operator>=(const T &rhs) noexcept {
            return a >= rhs;
        }

        bool operator<(const T &rhs) {
            return a < rhs;
        }

        bool operator<=(const T &rhs) {
            return a <= rhs;
        }

        bool operator==(const T &rhs) {
            return a == rhs;
        }

        bool operator>(const num &rhs) noexcept {
            return a > rhs.a;
        }

        bool operator>=(const num &rhs) noexcept {
            return a >= rhs.a;
        }

        bool operator<(const num &rhs) {
            return a < rhs.a;
        }

        bool operator<=(const num &rhs) {
            return a <= rhs.a;
        }

        bool operator==(const num &rhs) {
            return a == rhs.a;
        }

        num operator*=(const T &rhs) const = delete;
        num operator*=(const num &rhs) const = delete;

        num operator^(const T &rhs) noexcept {
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

        num operator^(const num &rhs) noexcept {
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

        template<typename T1>
        friend std::istream &operator>>(std::istream &cin, num<T1> &rhs) noexcept {
            return cin >> rhs.a;
        }

        template<typename T1>
        friend std::ostream &operator<<(std::ostream &cout, const num<T1> &rhs) noexcept {
            return cout << rhs.a;
        }

    private:
        T a;
    public:
        inline static long long mod = 1e9 + 7;
    };

}

#endif

