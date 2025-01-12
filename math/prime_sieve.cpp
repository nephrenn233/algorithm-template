const int N = 1e5;
bool not_prime[N + 10];
int prime[N + 10], tot = 0;
for (int i = 2; i <= N; ++i) {
    if (not_prime[i] == 0) prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= N; ++j) {
        not_prime[i * prime[j]] = 1;
        if (i % prime[j] == 0) break;
    }
}