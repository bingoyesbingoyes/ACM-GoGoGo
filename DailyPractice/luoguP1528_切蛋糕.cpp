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
// Declare variables
int n;
int m;
int cake[53];
int mouth[1031];
int sum[1031];
int total_cake;
int waste_cake;
int need_cake;
// Define a function for depth-first search
bool dfs(int now_mouth, int cake_from) {
    // If all mouths have been fed, return true
    if (now_mouth <= 0) return true;
    // If there is not enough cake to feed the remaining mouths, return false
    if (total_cake - waste_cake < need_cake) return false;
    // Try feeding each cake to the current mouth
    for (int i = cake_from; i <= m; ++i) {
        // If the current cake is large enough to feed the current mouth
        if (cake[i] >= mouth[now_mouth]) {
            // Feed the current mouth with the current cake
            cake[i] -= mouth[now_mouth];
            // If the current cake becomes smaller than the smallest mouth, add its remaining size to the waste_cake variable
            if (cake[i] < mouth[1]) waste_cake += cake[i];
            // If the next mouth has the same size as the current mouth, try feeding the remaining mouths using the same cake
            if (mouth[now_mouth] == mouth[now_mouth - 1]) {
                if (dfs(now_mouth - 1, i) == true) {
                    // If it is possible to feed the remaining mouths using the same cake, restore the current cake and return true
                    cake[i] += mouth[now_mouth];
                    return true;
                }
            // If the next mouth has a different size from the current mouth, try feeding the remaining mouths using the smallest cake
            } else if (dfs(now_mouth - 1, 1) == true) {
                // If it is not possible to feed the remaining mouths using the current cake, restore the current cake and the waste_cake variable
                cake[i] += mouth[now_mouth];
                return true;
            }
            if (cake[i] < mouth[1]) waste_cake -= cake[i];
            cake[i] += mouth[now_mouth];
        }
    }
    // If it is not possible to feed the remaining mouths using any of the cakes, return false
    return false;
}
int main() {
    // Read the number of cakes and the sizes of the cakes
    io >> m;
    for (int i = 1; i <= m; ++i) {
        io >> cake[i];
        total_cake += cake[i];
    }
    // Read the number of mouths and the capacities of the mouths
    io >> n;
    for (int i = 1; i <= n; ++i) {
        io >> mouth[i];
    }
    // Sort the sizes of the cakes and the capacities of the mouths in ascending order
    sort(mouth + 1, mouth + n + 1);
    // Compute the prefix sums of the capacities of the mouths
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + mouth[i];
    }
    // Initialize the answer variable
    int ans = 0;
    // Initialize the left and right boundaries of the binary search
    int l = 1, r = n;
    // If the total capacity of the mouths is greater than the total size of the cakes, decrease the right boundary of the binary search
    while (r && sum[r] > total_cake) --r;
    // Perform binary search to find the maximum number of mouths that can be fed
    while (l <= r) {
        // Compute the midpoint of the left and right boundaries
        int mid = l + r >> 1;
        // Initialize the waste_cake variable
        waste_cake = 0;
        // Compute the minimum amount of cake needed to feed mid mouths
        need_cake = sum[mid];
        if (dfs(mid, 1) == true) {
            // If it is possible to feed mid mouths using the cakes, update the answer and increase the left boundary of the binary search
            ans = mid;
            l = mid + 1;
        } else {
            // If it is not possible to feed mid mouths using the cakes, decrease the right boundary of the binary search
            r = mid - 1;
        }
    }
    // Print the answer and return 0
    return printf("%d", ans), 0;
}
// u know what, I have got a crush in coding with chatGPT :)