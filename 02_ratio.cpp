#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

namespace hse::cpp {

    long long gcd(long long a, long long b) {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            long long t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    struct ratio {
    private:
        /**
         * Nominator and denominator have GCD 1, denominator is greater than zero.
         */
        int nominator, denominator;

    public:
        ratio(long long nominator_ = 0, long long denominator_ = 1) {
            assert(denominator_ != 0);
            long long g = gcd(nominator_, denominator_);
            if (denominator_ < 0) {
                g *= -1;
            }
            nominator_ = nominator_ / g;
            denominator_ /= g;

            assert(nominator_ <= std::numeric_limits<int>::max());
            assert(nominator_ >= std::numeric_limits<int>::min());
            assert(denominator_ <= std::numeric_limits<int>::max());

            nominator = nominator_;
            denominator = denominator_;
        }

        int get_nominator() const { return nominator; }
        int get_denominator() const { return denominator; }

        ratio operator+() const {
            return *this;
        }

        ratio operator-() const {
            return ratio(-nominator, denominator);
        }

        ratio operator *(ratio const &b) const {
            return ratio(
                    static_cast<long long>(nominator) * b.nominator,
                    static_cast<long long>(denominator) * b.denominator
            );
        }

        ratio operator /(ratio const &b) const {
            return *this * ratio(b.denominator, b.nominator);
        }

        bool operator ==(ratio const &b) const {
            return nominator == b.nominator && denominator == b.denominator;
        }

        friend std::ostream& operator <<(std::ostream& out, ratio const &r);
        friend ratio operator +(ratio const &a, ratio const &b);
    };

    ratio operator +(ratio const &a, ratio const &b) {
        return ratio(
                static_cast<long long>(a.get_nominator()) * b.get_denominator() +
                static_cast<long long>(a.get_denominator()) * b.get_nominator(),
                static_cast<long long>(a.get_denominator()) * b.get_denominator()
        );
    }

    ratio& operator +=(ratio &a, ratio const &b) {
        return a = a + b;
    }

    ratio operator -(ratio const &a, ratio const &b) {
        return a + (-b);
    }

    std::ostream& operator <<(std::ostream& out, ratio const &r) {
        out << r.nominator;
        out << "/" << r.denominator;
        return out;
    }

    std::istream& operator >>(std::istream& in, ratio &r) {
        long long a, b;
        char c;
        in >> a >> c >> b;
        assert(c == '/');
        r = ratio(a, b);
        return in;
    }

    struct bigint {};

    // PREFIX; ++a
    bigint & operator++(bigint &a) {
        // TODO increment plz
        return a;
    }
    // POSTFIX; a++
    bigint operator++(bigint &a, int) {
        bigint old_value = a;
        ++a;
        return old_value;
    }
}

int main() {
    std::vector<int> v{1, 2, 3};
    v.size();

    using hse::cpp::ratio;

    ratio a(1), b(2, 5);
    +a;
    -b;

    a = (b += 3);

    ratio c;

    using hse::cpp::bigint;

    bigint xx;
    ++xx;
    xx++;

    std::cin >> a;

    std::cout << a + b << std::endl;
    std::cout << a << std::endl;
    return 0;
}
