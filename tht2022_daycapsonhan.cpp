#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX_K = 23;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long q;
    cin >> n >> q;

    vector<long long> a(n);
    vector<long long> all_vals;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        all_vals.push_back(a[i]);
        if (a[i] % q == 0)
            all_vals.push_back(a[i] / q);
        if (a[i] % (q * q) == 0)
            all_vals.push_back(a[i] / (q * q));
    }

    sort(all_vals.begin(), all_vals.end());
    all_vals.erase(unique(all_vals.begin(), all_vals.end()), all_vals.end());
    unordered_map<long long, int> val_to_id;
    for (int i = 0; i < (int)all_vals.size(); ++i)
        val_to_id[all_vals[i]] = i;

    int m = all_vals.size();
    vector<vector<long long>> dp(MAX_K + 1, vector<long long>(m, 0));

    for (int i = 0; i < n; ++i) {
        long long x = a[i];
        int idx = val_to_id[x];

        for (int k = MAX_K; k >= 2; --k) {
            if (x % q == 0) {
                long long prev = x / q;
                if (val_to_id.count(prev)) {
                    int prev_idx = val_to_id[prev];
                    dp[k][idx] = (dp[k][idx] + dp[k - 1][prev_idx]) % MOD;
                }
            }
        }

        dp[1][idx] = (dp[1][idx] + 1) % MOD;
    }

    vector<long long> result(n - 1, 0);
    for (int k = 2; k <= n; ++k) {
        if (k <= MAX_K) {
            long long total = 0;
            for (int i = 0; i < m; ++i)
                total = (total + dp[k][i]) % MOD;
            result[k - 2] = total;
        } else {
            result[k - 2] = 0;
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << '\n';

    return 0;
}
