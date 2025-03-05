constexpr int N = 2e5;
struct linear_sieve {
    int n;
    std::vector<int> not_prime;
    std::vector<int> primes;
    linear_sieve(int N) : n{N} {
        init();
    }
    void init() {
        not_prime.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            if (not_prime[i] == 0) primes.push_back(i);
            for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
                not_prime[i * primes[j]] = 1;
                if (i % primes[j] == 0) break;
            }
        }
    }
    bool is_prime(int x) {
        assert(x <= n);
        return !not_prime[x];
    }
} prime(N);