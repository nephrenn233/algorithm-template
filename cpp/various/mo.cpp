// 0-indexed
struct Mo {
    int n;
    std::vector<std::pair<int, int>> lr;
    Mo (int _n) : n(_n) {}
    void add(int l, int r) {
        lr.push_back({l, r});
    }
    template <class AL, class AR, class RL, class RR, class O>
    void run(AL add_left, AR add_right, RL remove_left, RR remove_right, O out) {
        int q = lr.size(), bs = n / std::clamp<int>(std::sqrt(q * 2 / 3), 1, n);
        std::vector<int> order(q);
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(), 
            [&](int i, int j) {
                auto [li, ri] = lr[i];
                auto [lj, rj] = lr[j];
                if (li / bs != lj / bs) {
                    return li < lj;
                }
                return ri < rj;
            });
        int l = 0, r = 0;
        for (auto i : order) {
            auto [li, ri] = lr[i];
            while (l > li) add_left(--l);
            while (r < ri) add_right(r++);
            while (l < li) remove_left(l++);
            while (r > ri) remove_right(--r);
            out(i);
        }
    }
};

int rL = 0, rR = 0;
auto add_left = [&](int i) -> void {
    --rL;
    assert(i == rL);
    // operation
};
auto add_right = [&](int i) -> void {
    assert(i == rR);
    // operation
    ++rR;
};
auto remove_left = [&](int i) -> void {
    assert(i == rL);
    // operation
    ++rL;
};
auto remove_right = [&](int i) -> void {
    --rR;
    assert(i == rR);
    // operation
};
auto out = [&](int qi) -> void {
    // get answer
};

mo.run(add_left, add_right, remove_left, remove_right, out);