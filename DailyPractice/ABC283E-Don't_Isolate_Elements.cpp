# include "iostream"
# include "cstdio"
# include "cmath"
# include "cstring"
# include "numeric"
# include "vector"
# include "algorithm"

# define D_e_Line cout << "[" << __LINE__ << "]\n"
# define D_e(x) cout << "[" << __LINE__ << "] ... " << "[" << (#x) << " :    " << (x) << "]\n"
# define FileOpen() freopen("in.txt", "r", stdin)
# define FileSave() freopen("out.txt", "w", stdout)
# define Pause() system("pause")
struct FastIO {
	template<typename ATP> inline FastIO& operator >> (ATP& x) {
		x = 0; int f = 1; char c;
		for (c = getchar(); c < '0' || c > '9'; c = getchar()) if (c == '-') f = -1;
		while (c >= '0' && c <= '9') x = x * 10 + (c ^ '0'), c = getchar();
		if (f == -1) x = -x;
		return *this;
	}
} io;
template<typename ATP> ATP Min(ATP x, ATP y) {
	return x < y ? x : y;
}
template<typename ATP> ATP Max(ATP x, ATP y) {
	return x > y ? x : y;
}
template<typename ATP> ATP Abs(ATP x) {
	return x > 0 ? x : -x;
}
using namespace std;

int main() {
    int n, m;
    io >> n >> m;
    vector a(n + 2, vector<int>(m + 2));
    vector f(n + 1, vector(2, vector<int>(2, 0x3f3f3f3f)));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            io >> a[i][j];
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        a[i][0] = a[i][m + 1] = 2;
    }
    for (int j = 1; j <= m; ++j) {
        a[0][j] = a[n + 1][j] = 2;
    }

    
    auto check = [&](int i, int st1, int st2, int st3) -> bool {
        for (int j = 1; j <= m; ++j) {
            int mid = a[i][j] ^ st2;
            int left = a[i][j - 1] ^ st2;
            int right = a[i][j + 1] ^ st2;
            int up = a[i - 1][j] ^ st1;
            int down = a[i + 1][j] ^ st3;
            if (mid != left && mid != right && mid != up && mid != down) return false;
        }
        return true;
    };

    f[0][0][0] = f[0][0][1] = f[0][1][0] = f[0][1][1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int statu_1 = 0; statu_1 <= 1; ++statu_1) { // i - 1
            for (int statu_2 = 0; statu_2 <= 1; ++statu_2) { // i
                for (int statu_3 = 0; statu_3 <= 1; ++statu_3) { // i + 1
                    if (check(i, statu_1, statu_2, statu_3) == true) {
                        f[i][statu_2][statu_3] = min(f[i][statu_2][statu_3], f[i - 1][statu_1][statu_2] + statu_2);
                    }
                }
            }
        }
    }
    int ans = min({f[n][0][0], f[n][1][0], f[n][1][1], f[n][0][1]});
    if (ans == 0x3f3f3f3f) ans = -1;
    printf("%d", ans);
    return 0;
}