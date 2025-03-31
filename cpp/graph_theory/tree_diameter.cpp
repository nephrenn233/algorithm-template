std::tuple<int, int, int> get_diameter(const std::vector<std::vector<int>> &g) {
    int n = g.size();
    
    std::vector<int> d(n, 0);
    int c = 0;
    int L = -1, R = -1;

    auto dfs = [&](auto &&self, int u, int fa) -> void {
        for (auto v : g[u]) {
            if (v == fa) continue;
            d[v] = d[u] + 1;
            if (d[v] > d[c]) c = v;
            self(self, v, u);
        }
    };

    dfs(dfs, 0, -1);
    L = c;
    d[c] = 0;
    dfs(dfs, c, -1);
    R = c;

    return {L, R, d[c]};
}