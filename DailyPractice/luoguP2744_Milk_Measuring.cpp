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
const int N = 20003;
int quarts;
vector<int> bucket;
int n;
int max_depth;
bool flag;
bool f[N];
int main() {
// FileOpen();
    io >> quarts;
    io >> n;
    // Array to store the current subset being tried
    vector<int> choose(n + 1);
    for (int i = 1; i <= n; ++i) {
        int voltage;
        io >> voltage;
        bucket.emplace_back(voltage);
    }
    // Sort the set of integers in ascending order
    sort(bucket.begin(), bucket.end());

    auto check = [&]() -> bool {
        memset(f, false, (quarts + 1) * sizeof(bool));
        f[0] = true;
        // Check if there exists a subset of the current subset that adds up to the target sum
        for (int i = 1; i <= quarts; ++i) {
            for (int j = 0; j < max_depth; ++j) {
                // If the current number can be included in the subset
                if (i >= choose[j]) {
                    // Update the intermediate result
                    f[i] |= f[i - choose[j]];
                }
            }
        }
        // Return true if the target sum can be achieved
        return f[quarts];
    };

    function<void(int, int)> dfs = [&](int now, int tot) -> void {
        // Stop the search if a valid subset has been found
        if (flag == true) return;
        // If the current subset is the maximum size, check if it is a valid subset
        if (tot >= max_depth) {
            // If the current subset is valid
            if (check() == true) {
                // Print the size of the subset
                printf("%d ", max_depth);
                 // Print the numbers in the subset
                for (int i = 0; i < max_depth; ++i) {
                    printf("%d ", choose[i]);
                }
                // Set the flag to stop the search
                flag = true;
            }
            return;
        }
        // Try all possible numbers to include in the subset
        for (int i = now; i < bucket.size(); ++i) {
            // Stop the search if a valid subset has been found
            if (flag == true) return;
            // If the remaining number of buckets cannot meet the demand in any case
            if (bucket.size() - i + 1 < max_depth - tot) return;
            // Include the current number in the subset
            choose[tot] = bucket[i];
            // Recursively call the function with the next number and the same subset size
            dfs(i + 1, tot + 1);
            // Reset the current number in the subset
            choose[tot] = 0;
        }
    };

    // A correct implementation of the depth-first search algorithm to find a valid subset of a given set of integers that adds up to a target sum
    for (int i = 1; i <= bucket.size(); ++i) {
        max_depth = i;
        dfs(0, 0);
        if (flag == true) break;
    }
    return 0;
}