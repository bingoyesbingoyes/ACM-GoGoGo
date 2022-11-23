# include "D:\Desktop\ICPC\Head.cpp"
using namespace std;
const int N = 3e5 + 3;
const int mod = 1e9 + 7;
struct node {
    int SSR, SR, R;
} a[N];
int Pow(int a, int b) {
    long long s = 1;
    while (b) {
        if (b & 1) s = 1ll * s * a % mod;
        a = 1ll * a * a % mod, b >>= 1;
    }
    return s;
}
int n, m;
void calc() {
    
}
int main() {
    io >> n >> m;
    for (int i = 1; i <= n; ++i) {
        io >> a[i].SSR >> a[i].SR;
        a[i].R = 100 - a[i].SSR - a[i].SR;
    }
    calc();
    while (m--) {
        int t;
        io >> t;
        node tmp = a[t];
        io >> a[t].SSR >> a[t].SR; // can here be same line?
        a[t].R = 100 - a[t].SSR - a[t].SR;
        calc();
        a[t] = tmp;
    }
}