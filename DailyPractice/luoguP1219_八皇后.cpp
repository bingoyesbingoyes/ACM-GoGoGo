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
constexpr int N = 103;
// The maximum size of the chessboard.
int n;
// The number of solutions found.
int ans;
// The positions of the queens on the board.
int queen[N];
// Arrays used to keep track of which rows, counter-diagonals, and principle-diagonals are already occupied by queens.
bool row[N];
bool counter_diagonal[N];
bool principle_diagonal[N];
// Recursive function to find solutions to the eight queens problem.
// x: the current row we are trying to place a queen in.
void dfs(int x) {
    if (x > n) {
        // A solution has been found.
        ++ans;
        // Stop searching after finding three solutions.
        if (ans > 3) return;
        // Print the positions of the queens on the board.
        for (int i = 1; i <= n; ++i) {
            printf("%d ", queen[i]);
        }
        putchar('\n');
        return;
    }
    // Try placing a queen in each column of the current row.
    for (int i = 1; i <= n; ++i) {
        if (!row[i] && !counter_diagonal[x + i] && !principle_diagonal[x - i + n]) {
            // The value of queen[x] indicates the column in which the queen on row x is placed.
            queen[x] = i;
            row[i] = true;
            counter_diagonal[x + i] = true;
            principle_diagonal[x - i + n] = true;
            // Check if we can find a solution by placing the remaining queens.
            dfs(x + 1);
            // If no solution is found, backtrack and try the next column.
            row[i] = false;
            counter_diagonal[x + i] = false;
            principle_diagonal[x - i + n] = false;
        }
    }
}
// Read the size of the chessboard from standard input and find solutions to the eight queens problem.
int main() {
    io >> n;
    dfs(1);
    // Print the number of solutions found.
    printf("%d", ans);
    return 0;
}
// use https://chat.openai.com/chat to add comments is cool, bro =w=