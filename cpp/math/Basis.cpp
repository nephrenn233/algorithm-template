using i64 = long long;
struct Basis {
    std::vector<i64> b;
    Basis() {
        b.resize(64);
        b.assign(64, 0);
    }
    void insert (i64 x) {
        for (int j = 63; j >= 0; --j) {
            if ( (x >> j) & 1 ) {
                if (b[j]) x ^= b[j];
                else {
                    b[j] = x;
                    for (int k = j - 1; k >= 0; --k) {
                        if (b[k] && ((b[j] >> k) & 1)) b[j] ^= b[k];
                    }
                    for (int k = j + 1; k <= 63; ++k) {
                        if ((b[k] >> j) & 1) b[k] ^= b[j];
                    }
                    break;
                }
            }
        }
    }
};