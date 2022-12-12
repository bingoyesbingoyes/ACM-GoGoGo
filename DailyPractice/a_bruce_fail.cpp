# include "D:\Desktop\ICPC\Head.cpp"
using namespace std;
constexpr int mod = 1e9 + 7;
int main() {
FileOpen();
    int n, m, color;
    io >> n >> m >> color;
    vector<int> tot(color + 1);
    vector<int> colorX(n + 1);
    vector<int> colorY(m + 1);
    for (int i = 1; i <= color; ++i) io >> tot[i];
    int ans = 0;
    auto dfs = [&](auto dfs, int x, int y) {
        if (x > n) {
            // for (auto num : tot) printf("%d ", num);
            // putchar('\n');
            for (int i = 1; i <= color; ++i) {
                // chess left
                if (tot[i] != 0) return;
            }
            ++ans;
            if (ans == mod) ans = 0;
            return;
        }
        // place chess
        for (int i = 1; i <= color; ++i) {
            // if no this kind of chess left
            if (tot[i] <= 0) continue;
            // if colored but not corresponding
            if (colorX[x] != i && colorX[x]) continue;
            if (colorY[y] != i && colorY[y]) continue;
            // use one chess
            --tot[i];
            // if not colored before, color rows and columns now
            colorX[x] = colorY[y] = i;
            if (y == m)
                dfs(dfs, x + 1, 1);
            else
                dfs(dfs, x, y + 1);
            // recycle chess
            ++tot[i];
            // wash~
            colorX[x] = 0;
            colorY[y] = 0;
        }
        // no chess
        if (y == m)
            dfs(dfs, x + 1, 1);
        else
            dfs(dfs, x, y + 1);
    };
    dfs(dfs, 1, 1);
    printf("%d", ans);
    return 0;
}
/*
4 2 2
3 1
*/