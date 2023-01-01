# include "../Head.cpp"
using namespace std;
// Function to calculate the GCD of two integers
int gcd(int a, int b) {
    // Use bitwise XOR and modulo to calculate GCD
    // Repeatedly applies the Euclidean algorithm until the remainder is 0    
    while (b ^= a ^= b ^= a %= b);
    return a;
}
int main() {
    int tt;
    io >> tt;
    while (tt--) {
        // Read in the length of the sequence
        int n;
        io >> n;
        // Read in the sequence of integers
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            io >> a[i];
        }
        // Sort the sequence in ascending order
        sort (a.begin(), a.end());
        // Flag to track if a pair of equal consecutive integers is found
        bool flag = true;
        for (vector<long long>::iterator it = a.begin(); next(it) != a.end(); ++it) {
            // If equal consecutive integers are found, set flag to false and break
            if (*it == *(next(it))) {
                flag = false;
                printf("NO\n");
                break;
            }
        }
        // If flag is false, skip the rest of the processing for this test case
        if (flag == false) continue;
        // Flag to track if a pair of integers with impossibility can be found using the CRT
        bool CRT_flag = true;
        // Check for the possibility of selecting two integers with impossibility using the CRT
        for (long long mod = 2; mod <= (n >> 1); ++mod) {
            // Vector to track the number of integers with each remainder when divided by the current modulus
            vector<long long> tot(mod, 0);
            // Increment the count for each remainder
            for (auto &x : a) {
                ++tot[x % mod];
            }
            // Check if there are at least two integers with the same remainder
            if (*min_element(tot.begin(), tot.end()) >= 2) {
                // If there are, set flag to false and break
                CRT_flag = false;
                break;
            }
        }
        // Print result based on CRT flag
        if (CRT_flag == true) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}