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
const int N = 5003;
int main() {
    int n;
    io >> n;
    vector<int> a(n + 1);
    vector<int> f(n + 1);
    vector<int> tot(n + 1);
    for (int i = 1; i <= n; ++i) {
        io >> a[i];
    }
    int max_len = 0;
    for (int i = 1; i <= n; ++i) {
        f[i] = 1;
        for (int j = 1; j < i; ++j) {
            if (a[i] < a[j]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        max_len = max(max_len, f[i]);
        for (int j = 1; j < i; ++j) {
            if (f[i] == f[j] && a[i] == a[j]) {
                tot[j] = 0;
            } else if (f[i] == f[j] + 1 && a[i] < a[j]) {
                tot[i] += tot[j];
            }
        }
        if (!tot[i]) tot[i] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (f[i] == max_len) {
            ans += tot[i];
        }
    }
    printf("%d %d", max_len, ans);
    return 0;
}