template<class T>
T quick_pow (T a, i64 b) {
    T res(1);
    for ( ; b; a *= a, b >>= 1) {
        if (b & 1) res *= a;
    }
    return res;
}
template <class T, T mod>
class ModInt {
private:
    T x;
public:
    ModInt (const T _x = 0) : x(_x % mod) {}
    friend std::ostream &operator << (std::ostream &os, const ModInt &z) {
        os << z.x;
        return os;
    }
    friend std::istream &operator >> (std::istream &is, ModInt &z) {
        T v;
        is >> v;
        z = ModInt(v);
        return is;
    }
    explicit operator T() {
        return x;
    }
    ModInt &operator += (const ModInt &rhs) {
        x = (x + rhs.x) % mod;
        return *this;
    }
    friend ModInt operator + (const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res += rhs;
        return res;
    }
    ModInt &operator -= (const ModInt &rhs) {
        x = (x - rhs.x) % mod;
        x = (x < 0 ? x + mod : x);
        return *this;
    }
    friend ModInt operator - (const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res -= rhs;
        return res;
    }
    ModInt &operator *= (const ModInt &rhs) {
        x = (x * rhs.x) % mod;
        return *this;
    }
    friend ModInt operator * (const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res *= rhs;
        return res;
    }
    ModInt inv() const {
        assert(x != 0);
        return quick_pow(*this, mod - 2);
    }
    ModInt &operator /= (const ModInt &rhs) {
        return *this *= rhs.inv();
    }
    friend ModInt operator / (const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res /= rhs;
        return res;
    }
};