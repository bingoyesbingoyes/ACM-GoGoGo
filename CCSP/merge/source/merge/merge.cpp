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
const int N = 1e5 + 3;
using namespace std;
# include "set"
set<int> st;
int main() {
// FileOpen();
    int n, K;
    io >> n >> K;
    // D_e_Line;
    for (int i = 1; i <= n; ++i) {
        int x;
        io >> x;
        st.insert(x);
    }
        // D_e(st.size());
    int turns = 0;
    while (st.size() > 1) {
        int min_del = K + 1;
        auto min_pos = st.begin();
        for (auto it1 = st.begin(), it2 = next(it1); it2 != st.end(); it1 = it2, ++it2) {
            if (*it2 - *it1 < min_del) {
                min_del = *it2 - *it1;
                min_pos = it1;
            }
        }
        int new_val = ((*min_pos + *(next(min_pos))) % K + K) % K;
        // D_e(new_val);
        st.erase(next(min_pos));
        st.erase(min_pos);
        st.insert(new_val);
        // D_e(st.size());
        ++turns;
    }
    printf("%d\n%d\n", turns, *st.begin());
    return 0;
}
/*
9 10
0 1 2 4 5 6 7 8 9
*/