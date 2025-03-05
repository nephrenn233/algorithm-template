namespace Trie {
    constexpr int N = 3e6 + 10;

    int trie[N][26];
    int tot = 0;
    bool exist[N];

    void clear() {
        for (int i = 0; i <= tot; ++i) {
            std::fill(trie[i], trie[i] + 26, 0);
        }
        tot = 0;
        std::fill(exist, exist + tot + 1, 0);
    }

    int new_node() {
        ++tot;
        std::fill(trie[tot], trie[tot] + 26, 0);
        return tot;
    }

    void add(std::string s) {
        int u = 0;
        for (int i = 0; i < s.size(); ++i) {
            int &v = trie[u][s[i] - 'a'];
            if (v == 0) {
                v = new_node();
            }
            u = v;
        }
        exist[u] = 1;
    }

    bool is_exist(std::string s) {
        int u = 0;
        for (int i = 0; i < s.size(); ++i) {
            int v = trie[u][s[i] - 'a'];
            if (v == 0) {
                return false;
            }
            u = v;
        }
        return exist[u];
    }
};