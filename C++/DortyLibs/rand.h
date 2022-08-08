int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
/// [a;b]
int rnd(int a, int b) {
    return a + mt() % (b - a + 1);
}
