# include "../Head.cpp"
using namespace std;
int main() {
    // Read in the number of congruences
    int n;
    io >> n;
    // Read in the moduli and remainders for each congruence
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        io >> a[i] >> b[i];
    }
    // Calculate the product of all the moduli
    long long M = 1;
    for (auto &x : a) {
        M *= x;
    }
    // Function for extended Euclidean algorithm to find gcd and linear combination 
    function<void(long long, long long, long long&, long long&)> exgcd = [&](long long a, long long b, long long& x, long long& y) -> void {
        if (!b) {
            x = 1;
            y = 0;
        } else {
            exgcd(b, a % b, y, x);
            y -= a / b * x;
        }
    };
    long long ans = 0;
    // Iterate over each congruence
    for (int i = 0; i < n; ++i) {
        // Calculate m_i, the product of all the moduli except for a[i]
        long long m_i = M / a[i];
        long long x, y;
        // Use extended Euclidean algorithm to find inverse of m_i modulo a[i]
        exgcd(m_i, a[i], x, y);
        // m_i * x === 1 (mod a[i])
        // m_i * x + a[i] * y == gcd(m_i, a[i]) == 1
        // x is the inverse of m_i modulo a[i] (x >= 0)
        x = (x % a[i] + a[i]) % a[i];
        // Add the solution for this congruence to the final answer
        ans = (ans + m_i * x * b[i]) % M;
    }
    // Output the final answer, making sure it is positive
    printf("%lld", (ans + M) % M);
}
/* 
x === b[i] (mod a[i])
*/