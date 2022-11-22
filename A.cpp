# include "iostream"
# include "cstdio"
# include "cmath"
# include "cstring"
# include "numeric"
# include "vector"
# include "algorithm"

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
const int N = 1e6 + 3;
int a[N];
long long sum[N];
int main() {
    int tt;
    io >> tt;
    while (tt--) {
        int n;
        io >> n;
        for (int i = 1; i <= n; ++i) {{
            int x;
            io >> x;
            sum[i] = sum[i - 1] + x;
        }}
        long long ans = 0;
        ans = max({ans, sum[n] * 114, sum[n] * 514});
        for (int i = 1; i < n; ++i) {
            ans = max(ans, sum[i] * 114 + (sum[n] - sum[i]) * 514);
        }
        printf("%lld\n", ans);
    }
    return 0;
}