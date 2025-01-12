struct segment_tree {
    int n;
    std::vector<int> tr, lazy;
    segment_tree(int _n) : n(_n), tr(n * 4), lazy(n * 4) {}
    segment_tree(const std::vector<int> &a) : n(a.size()), tr(n * 4), lazy(n * 4) {
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
    void push(int u, int l, int r) {
        if (lazy[u]) {
            tr[u] += lazy[u] * (r - l);
            if (r - l > 1) {
                lazy[u * 2] += lazy[u];
                lazy[u * 2 + 1] += lazy[u];
            }
            lazy[u] = 0;
        }
    }
    void range_add(int u, int l, int r, int ql, int qr, int qv) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            tr[u] += qv * (r - l);
            lazy[u] += qv;
            return;
        }
        push(u, l, r);
        int mid = (l + r) / 2;
        range_add(u * 2, l, mid, ql, qr, qv); 
        range_add(u * 2 + 1, mid, r, ql, qr, qv);
        pull(u);
    }
    void range_add(int ql, int qr, int qv) {
        range_add(1, 0, n, ql, qr, qv);
    }
    void modify(int u, int l, int r, int qp, int qv) {
        if (r - l == 1) {
            tr[u] = qv;
            return;
        }
        push(u, l, r);
        int mid = (l + r) / 2;
        if (qp < mid) {
            modify(u * 2, l, mid, qp, qv);
        } else {
            modify(u * 2 + 1, mid, r, qp, qv);
        }
        pull(u);
    }
    void modify(int qp, int qv) {
        modify(1, 0, n, qp, qv);
    }
    int range_query(int u, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tr[u];
        }
        push(u, l, r);
        int mid = (l + r) / 2;
        return range_query(u * 2, l, mid, ql, qr) + range_query(u * 2 + 1, mid, r, ql, qr);
    }
    int range_query(int ql, int qr) {
        return range_query(1, 0, n, ql, qr);
    }
};