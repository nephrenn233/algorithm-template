template<typename T>
T floor_div(T a, T b) {
    assert(b != 0);
    T d = a / b;
    if (a % b != 0 && ((a > 0) ^ (b > 0))) {
        d -= 1;
    }
    return d;
}

template<typename T>
T ceil_div(T a, T b) {
    assert(b != 0);
    T d = a / b;
    if (a % b != 0 && !((a > 0) ^ (b > 0))) {
        d += 1;
    }
    return d;
}