const i64 base = 131, mod1 = 998244353, mod2 = 1e9 + 7;
typedef std::pair<i64, i64> PII;

std::vector<PII> get_hash(std::string s) {
    int n = s.size();
    std::vector<PII> res(n);
    i64 h1 = 0, h2 = 0;
    for (int i = 0; i < n; ++i) {
        h1 = (h1 * base % mod1 + s[i] - '0' + 1) % mod1;
        h2 = (h2 * base % mod2 + s[i] - '0' + 1) % mod2;
        res[i] = std::make_pair(h1, h2);
    }
    return res;
}

PII query(std::vector<PII> res, int l, int r) {
    i64 h1 = (res[r].first - (l - 1 >= 0 ? res[l - 1].first : 0) * quick_pow(base, r - l + 1, mod1) % mod1 + mod1) % mod1;
    i64 h2 = (res[r].second - (l - 1 >= 0 ? res[l - 1].second : 0) * quick_pow(base, r - l + 1, mod2) % mod2 + mod2) % mod2;
    return std::make_pair(h1, h2);
}