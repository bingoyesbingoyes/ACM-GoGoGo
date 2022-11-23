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
const int N = 1e5 + 3;
# include "set"
# include "queue"
set<int> st;
int n, K;
struct node {
    int x, y;
    bool operator < (const node &els) const {
        if (y - x != els.y - els.x) return y - x > els.y - els.x;
        return  x + y > els.x + els.y;
    }
};
priority_queue<node> q;
int main() {
FileOpen();
FileSave();
    io >> n >> K;
    for (int i = 1; i <= n; ++i) {
        int x;
        io >> x;
        st.insert(x);
    }
    for (auto it = st.begin(); next(it) != st.end(); ++it) {
        q.push({*it, *next(it)});
    }
    // while (!q.empty()) {
    //     printf("[%d %d]\n", q.top().x, q.top().y);
    //     q.pop();
    // }
    // return 0;
    int turns = 0;
    while (st.size() > 1) {
        node now = q.top();
        q.pop();
        auto it1 = st.find(now.x);
        auto it2 = st.find(now.y);
        if (it1 == st.end() || it2 == st.end()) continue;
        ++turns;
        if (it1 != st.begin() && next(it2) != st.end()) {
            q.push({*prev(it1), *next(it2)});
        }
        st.erase(now.x);
        st.erase(now.y);
        int new_val = (now.x + now.y) % K;
        auto it3 = st.find(new_val);
        if (it3 == st.end()) {
            st.insert(new_val);
            it3 = st.find(new_val);
            if (it3 != st.begin()) {
                q.push({*prev(it3), *it3});
            }
            if (next(it3) != st.end()) {
                q.push({*it3, *next(it3)});
            }
        }
    }
    printf("%d\n%d\n", turns, *st.begin());
    return 0;
}
/*
9 10
0 1 2 4 5 6 7 8 9
*/