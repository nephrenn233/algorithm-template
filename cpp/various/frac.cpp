template <class T>
struct Frac {
    T a, b; // \frac{a}{b}
    Frac(T _a, T _b) : a(_a), b(_b) {
        norm();
    }
    Frac() : Frac(0, 1) {}
    Frac(T _a) : Frac(_a, 1) {}
    explicit operator double() const {
        return double(1) * a / b;
    }
    void norm() {
        if (b < 0) {
            a = -a;
            b = -b;
        }
        T g = std::gcd(a, b);
        a /= g, b /= g;
    }
    Frac &operator += (const Frac &rhs) {
        a = a * rhs.b + b * rhs.a;
        b = b * rhs.b;
        norm();
        return *this;
    }
    friend Frac operator + (const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        lhs += rhs;
        return lhs;
    }
    Frac &operator -= (const Frac &rhs) {
        a = a * rhs.b - b * rhs.a;
        b = b * rhs.b;
        norm();
        return *this;
    }
    friend Frac operator - (const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        lhs -= rhs;
        return res;
    }
    Frac &operator *= (const Frac &rhs) {
        a = a * rhs.a;
        b = b * rhs.b;
        norm();
        return *this;
    }
    friend Frac operator * (const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        lhs *= rhs;
        return res;
    }
    Frac &operator /= (const Frac &rhs) {
        a = a * rhs.b;
        b = b * rhs.a;
        norm();
        return *this;
    }
    friend Frac operator / (const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res /= rhs;
        return res;
    }
    friend std::ostream &operator << (std::ostream &os, const Frac &x) {
        os << x.a << "/" << x.b;
        return os;
    }
};