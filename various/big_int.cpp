constexpr int N = 1000;

struct BigInt {
    int a[N];

    BigInt(int x = 0) : a{} {
        for (int i = 0; x; ++i) {
            a[i] = x % 10;
            x /= 10;
        }
    }
    BigInt (std::string s) : a{} {
        for (int i = 0; i < s.size(); ++i) {
            a[i] = s[s.size() - i - 1] - '0';
        }
    }

    friend std::ostream &operator << (std::ostream &os, const BigInt &x) {
        int i = N - 1;
        while (i > 0 && x.a[i] == 0) {
            --i;
        }
        for (i; i >= 0; --i) {
            os << x.a[i];
        }
        return os;
    }
    friend std::istream &operator >> (std::istream &is, BigInt &x) {
        std::string s;
        is >> s;
        x = BigInt(s);
        return is;
    }

    bool operator < (const BigInt &rhs) const {
        for (int i = N - 1; i >= 0; --i) {
            if (a[i] < rhs.a[i]) {
                return true;
            } else if (a[i] > rhs.a[i]) {
                return false;
            }
        }
        return false;
    }
    bool operator > (const BigInt &rhs) const {
        return rhs < *this;
    }
    bool operator <= (const BigInt &rhs) const {
        return !(*this > rhs);
    }
    bool operator >= (const BigInt &rhs) const {
        return !(*this < rhs);
    }
    bool operator != (const BigInt &rhs) const {
        return *this < rhs || *this > rhs;
    }
    bool operator == (const BigInt &rhs) const {
        return !(*this != rhs);
    }

    BigInt &operator += (const BigInt &rhs) {
        for (int i = 0; i < N; ++i) {
            a[i] += rhs.a[i];
            if (a[i] >= 10) {
                a[i] -= 10;
                a[i + 1] += 1;
            }
        }
        return *this;
    }
    friend BigInt operator + (const BigInt &lhs, const BigInt &rhs) {
        BigInt res = lhs;
        res += rhs;
        return res;
    }

    BigInt &operator -= (const BigInt &rhs) {
        assert(*this >= rhs);
        for (int i = 0; i < N; ++i) {
            a[i] -= rhs.a[i];
            if (a[i] < 0) {
                a[i] += 10;
                a[i + 1] -= 1;
            }
        }
        return *this;
    }
    friend BigInt operator - (const BigInt &lhs, const BigInt &rhs) {
        BigInt res = lhs;
        res -= rhs;
        return res;
    }

    BigInt &operator *= (const int &rhs) {
        for (int i = 0; i < N; ++i) {
            a[i] *= rhs;
        }
        for (int i = 0; i + 1 < N; ++i) {
            a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
        return *this;
    }
    friend BigInt operator * (const BigInt &lhs, const int &rhs) {
        BigInt res = lhs;
        res *= rhs;
        return res;
    }
};