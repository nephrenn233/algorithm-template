std::vector<i64> inverse(int n, const i64 &p) {
    std::vector<i64> inv(n + 1, 0);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
    return inv;
}