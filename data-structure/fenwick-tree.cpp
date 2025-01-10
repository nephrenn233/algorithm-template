template <typename T>
struct Fenwick {
private:
    int n;
    std::vector<T> tr;
    T sum (int p) {
        T s (0);
        while (p > 0) {
            s += tr[p - 1];
            p -= p & -p;
        }
        return s;
    }
public:
    Fenwick (int _n = 0) {
        init(_n);
    }
    void init (int _n) {
        n = _n;
        tr.assign(n, T(0));
    }
    void add (int p, const T &v) {
        assert(0 <= p && p < n);
        ++p;
        while (p <= n) {
            tr[p - 1] += v;
            p += p & -p;
        }
    }
    // return sum of a[l, r-1]
    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }
};