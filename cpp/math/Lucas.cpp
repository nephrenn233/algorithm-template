int lucas (int n, int m) {
    return m ? binom(n % P, m % P) * lucas(n / P, m / P) % P : 1;
}