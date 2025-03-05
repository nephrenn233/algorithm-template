struct segment_tree {
    int n;
    std::vector<Info> tr;
    segment_tree(int _n) : n(_n), tr(_n * 4) {}
    segment_tree(const std::vector<Info> &a) : n(a.size()), tr(n * 4) {
        auto build = [&](auto &&self, int u, int l, int r) -> void {
            if (r - l == 1) {
                tr[u] = a[l];
                return;
            }
            int mid = (l + r) / 2;
            self(self, u * 2, l, mid);
            self(self, u * 2 + 1, mid, r);
            pull(u);
        };
        build(build, 1, 0, n);
    }
    void pull(int u) {
        tr[u] = tr[u * 2] + tr[u * 2 + 1];
    }
    void modify(int u, int l, int r, int qp, const Info &qv) {
        if (r - l == 1) {
            tr[u] = qv;
            return;
        }
        int mid = (l + r) / 2;
        if (qp < mid) modify(u * 2, l, mid, qp, qv);
        else modify(u * 2 + 1, mid, r, qp, qv);
        pull(u);
    }
    void modify(int qp, const Info &qv) {
        modify(1, 0, n, qp, qv);
    }
    void add(int u, int l, int r, int qp, const Info &qv) {
        if (r - l == 1) {
            tr[u] = tr[u] + qv;
            return;
        }
        int mid = (l + r) / 2;
        if (qp < mid) add(u * 2, l, mid, qp, qv);
        else add(u * 2 + 1, mid, r, qp, qv);
        pull(u);
    }
    void add(int qp, const Info &qv) {
        add(1, 0, n, qp, qv);
    }
    Info range_query(int u, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return {};
        }
        if (ql <= l && r <= qr) {
            return tr[u];
        }
        int mid = (l + r) / 2;
        return range_query(u * 2, l, mid, ql, qr) + range_query(u * 2 + 1, mid, r, ql, qr);
    }
    Info range_query(int ql, int qr) {
        // assert(ql < qr);
        if (ql >= qr) return {};
        return range_query(1, 0, n, ql, qr);
    }
};