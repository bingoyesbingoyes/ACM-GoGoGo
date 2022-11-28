# include "iostream"
# include "cstdio"
# include "cmath"
# include "cstring"
# include "numeric"
# include "vector"
# include "algorithm"
# include "bits/stdc++.h"

# define D_e_Line printf("\n-------------\n")
# define D_e(x) cout << "[" << (#x) << " :    " << (x) << "]\n"
# define FileOpen() freopen("in.txt", "r", stdin)
# define FileSave() freopen("out.txt", "w", stdout)
# define Pause() system("pause")
struct FastIO {
	template<typename ATP> inline FastIO& operator >> (ATP &x) {
		x = 0; int f = 1; char c;
		for (c = getchar(); c < '0' || c > '9'; c = getchar()) if (c == '-') f = -1;
		while (c >= '0' && c <= '9') x = x * 10 + (c ^ '0'), c = getchar();
		if (f == -1) x = -x;
		return *this;
	}
} io;
using namespace std;
constexpr int N = 1031;
// use __in128 instead of high precision, u know, for convenience
__int128 f[N][N];
int main() {
// FileOpen();
    __int128 n;
    __int128 r, g, b, T;
    io >> n >> r >> g >> b >> T;
    for (__int128 i = 1; i <= n; ++i) {
        // radiation tower only
        f[0][i] = f[0][i - 1] + g * T * (long long) (n - i);
    }
    // put both jamming and radiation
    for (__int128 i = 1; i <= n; ++i) {
        for (__int128 j = 1; i + j <= n; ++j) {
            __int128 k = n - i - j;
            if (k < 0) break;
            f[i][j] = max(f[i - 1][j] + j * g * b * k, f[i][j - 1] + (b * i + T) * g * k);
        }
    }
    // well, now let's consider the laser
    __int128 ans = 0;
    // here, must from 0, because we may not need any jamming tower
    for (__int128 i = 0; i <= n; ++i) {
        for (__int128 j = 0; i + j <= n; ++j) {
            __int128 k = n - i - j;
            if (k < 0) break;
            // i jamming, j radiation, k laser (i + j + k == n)
            ans = max(ans, f[i][j] + (b * i + T) * k * r);
        }
    }
    // __int128 can't use cout or printf
    auto write = [&](auto write, __int128 x) -> void {
        if (x > 9) write(write, x / 10);
        putchar(x % 10 + '0');
    };
    write(write, ans);
    return 0;
}
/*
5 4 3 2 1
*/
/*
radiate R -> sigma x * g
jamming J -> T + b
laser   L -> r
The laser tower must be placed behind
Reasonably, we should arrange the surplus space in front to the radiation tower and jamming tower
let f[i][j] := i jamming towers and j radiation towers placing in the space of the front i + j grid, causing the greatest damage to ants
k := n - i - j -> the rest gird
case 1: from -1 jamming tower
    add a jamming tower, and -> tot{radiation} * g * b * restTowers
case 2: from -1 radiation tower
    add a radiation tower, and -> (tot{jamming} * b + T) * restTowers * r
time? -> b * i + T
f[i][j] = max{f[i - 1][j] + j * g * b * k, f[i][j - 1] + (b * i + T) * r * k}
*/