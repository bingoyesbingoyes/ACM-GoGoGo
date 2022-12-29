# include "iostream"
# include "cstdio"
# include "cmath"
# include "cstring"
# include "numeric"
# include "vector"
# include "algorithm"

# define D_e_Line cout << "[" << __LINE__ << "]\n"
# define D_e(x) cout << "[" << (#x) << " :    " << (x) << "] ... " << __LINE__ << "\n"
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
    int tt;
    io >> tt;
    while (tt--) {
        int n, m;
        // Read in the dimensions of the matrix
        io >> n >> m;
        // Initialize the matrix with the given dimensions
        vector a(n + 1, vector<int> (m + 1));
        // Read in the values of the elements of the matrix
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                io >> a[i][j];
            }
        }
        
        // Define a function to check if a square of a given size exists in the matrix
        function<bool(int, vector<vector<int>>)> check = [&](int l, vector<vector<int>> a) -> bool {
            // Initialize a 2D prefix sum array
            vector sum(n + 1, vector<int>(m + 1, 0));
            // Calculate the prefix sum for each element in the matrix
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    // Mark the element as 1 if it is greater than or equal to the given size, 0 otherwise
                    a[i][j] = (a[i][j] >= l);
                    // Calculate the prefix sum for this element
                    sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
                }
            }
            // Iterate through all possible top-left corners of the square
            for (int i = 1; i <= n; ++i) {
                // Check if the square goes out of bounds of the matrix
                if (i + l - 1 > n) break;
                for (int j = 1; j <= m; ++j) {
                    // Check if the square goes out of bounds of the matrix
                    if (j + l - 1 > m) break;
                    // Check if the sum of the elements in the sub-matrix is equal to the size of the square (all elements are 1)
                    if (sum[i - 1][j - 1] + sum[i + l - 1][j + l - 1] - sum[i - 1][j + l - 1] - sum[i + l - 1][j - 1] == l * l) return true;
                }
            }
            // Return false if no such square is found
            return false;
        };
        
        // Perform binary search on the range [1, min(n, m)] to find the largest possible size of the square sub-matrix
        int l = 1, r = min(n, m), ans = - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (check(mid, a)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
         // Print the answer to the console
        printf("%d\n", ans);
    }
    return 0;
}