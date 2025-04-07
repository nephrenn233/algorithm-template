struct sparse_table {
    int n;
    std::vector<std::vector<Info>> a;

    sparse_table(const std::vector<Info> &v) : n(v.size()) {
        a.assign(std::__lg(n) + 1, std::vector<Info>(n));
        for (int i = 0; i < n; ++i) {
            a[0][i] = v[i];
        }
        for (int i = 1; i <= std::__lg(n); ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                a[i][j] = a[i - 1][j] + a[i - 1][j + (1 << (i - 1))];
            }
        }
    }

    Info query(int ql, int qr) {
        int s = std::__lg(qr - ql);
        return a[s][ql] + a[s][qr - (1 << s)];
    }
};