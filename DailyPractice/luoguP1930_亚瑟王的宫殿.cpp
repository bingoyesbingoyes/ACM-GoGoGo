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
// Define a struct called "Chess" to represent a square on the chessboard
struct Chess {
    // The x and y coordinates of the square
    int x, y;
    // Default constructor
    Chess() : x(0), y(0) {};
    // Constructor that initializes the coordinates
    Chess(int x, int y) : x(x), y(y) {};
};
// Define a struct called "Knight" that extends the "Chess" struct
struct Knight : Chess {
    // Constructor that initializes the coordinates
    Knight(int x, int y) : Chess(x, y) {};
};
// Define a struct called "King" that extends the "Chess" struct
struct King : Chess {
    // Default constructor
    King() : Chess() {};
    // Constructor that initializes the coordinates
    King(int x, int y) : Chess(x, y) {};
};
// Define a vector to store the positions of the knights
vector<Knight> knight;
// Define a variable to store the position of the king
King king;
// Define the dimensions of the chessboard
int n, m;
// Define arrays to store the possible x and y offsets for the knight's moves
int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
// Define an array to keep track of which squares have been visited by the BFS algorithm
bool vis[43][29];
// Define an array to store the minimum distances between each pair of squares on the chessboard
long long dis[43][29][43][29];
# include "queue"
queue<Chess> q;
// Define a function to perform a BFS search to find the minimum distances between each pair of squares on the chessboard
void bfs(int start_x, int start_y) {
    // Reset the "vis" array to mark all squares as unvisited
    memset(vis, false, sizeof vis);
    // Push the starting square onto the queue
    q.push(Chess(start_x, start_y));
    // Mark the starting square as visited
    vis[start_x][start_y] = true;
    // Set the distance from the starting square to itself to 0
    dis[start_x][start_y][start_x][start_y] = 0;
    // While the queue is not empty
    while (!q.empty()) {
        // Get the coordinates of the current square
        int x = q.front().x;
        int y = q.front().y;
        // Pop the current square off the queue
        q.pop();
        // For each possible knight's move
        for (int i = 0; i < 8; ++i) {
            // Compute the coordinates of the square that the knight would move to
            int fx = x + dx[i];
            int fy = y + dy[i];
            // If the knight's move is within the bounds of the chessboard and the square has not been visited
            if (fx > 0 && fy > 0 && fx <= n && fy <= m && vis[fx][fy] == false) {
                // Mark the square as visited
                vis[fx][fy] = true;
                // Set the distance from the starting square to this square to the distance from the starting square to the current square plus 1
                dis[start_x][start_y][fx][fy] = dis[start_x][start_y][x][y] + 1;
                // Push the square onto the queue
                q.push(Chess(fx, fy));
            }
        }
    }
}
int main() {
    // Read in the dimensions of the chessboard
    io >> n >> m;
    // Initialize the "dis" array with a large number
    memset(dis, 0x3f, sizeof dis);
    // Read in the position of the king
    int column;
    char row;
    cin >> row;
    scanf("%d", &column);
    king = King(column, row - 'A' + 1);
    // Read in the positions of the knights
    while (cin >> row >> column) {
        knight.push_back(Knight(column, row - 'A' + 1));
    }
    // For each square on the chessboard
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // Perform a BFS search from this square to find the minimum distances between each pair of squares on the chessboard
            bfs(i, j);
        }
    }
    // Initialize the minimum distance to a large number
    long long ans = 0x3f3f3f3f;
    // For each square on the chessboard
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // Compute the total distance from each knight to this square
            long long sum = 0;
            bool flag_over_limit = false;
            for (auto k : knight) {
                sum += dis[k.x][k.y][i][j];
                // If the total distance exceeds the maximum distance that can be stored in the "dis" array, set a flag to indicate this
                if (sum > 0x3f3f3f3f) {
                    flag_over_limit = true;
                    break;
                }
            }
            // If the total distance exceeded the maximum distance, skip this square and move on to the next one
            if (flag_over_limit == true) continue;
            // Update the minimum distance with the total distance plus the maximum distance between the king and this square
            ans = Min(ans, sum + Max(Abs(king.x - i), Abs(king.y - j)));
            // For each knight
            for (auto k : knight) {
                // For each square within 5 squares of the knight
                for (int x = Max(1, k.x - 5); x <= Min(n, k.x + 5); ++x) {
                    for (int y = Max(1, k.y - 5); y <= Min(m, k.y + 5); ++y) {
                        //  Update the minimum distance with the total distance minus the distance from the knight to this square plus the distance from the knight to the new square plus the distance from the new square to this square plus the maximum distance between the king and the new square
                        ans = Min(ans, sum - dis[k.x][k.y][i][j] + dis[k.x][k.y][x][y] + dis[x][y][i][j] + Max(Abs(king.x - x), Abs(king.y - y)));
                    }
                }
            }
        }
    }
    // Print the minimum distance
    printf("%lld", ans);
    return 0;
}