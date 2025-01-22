std::vector<PII> factorize(int x) {
    assert(x > 1);
    std::vector<PII> res;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                x /= i;
                ++cnt;
            }
            res.push_back({i, cnt});
        }
    }
    if (x != 1) {
        res.push_back({x, 1});
    }
    return res;
}