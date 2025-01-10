template<class T>
T quick_pow (T a, i64 b) {
    T res(1);
    for ( ; b; a *= a, b >>= 1) {
        if (b & 1) res *= a;
    }
    return res;
}