#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w, h, n;
    if (!(cin >> w >> h >> n)) return 0;

    vector<pii> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());

    vector<int> preMin(n + 1, INT_MAX), preMax(n + 1, INT_MIN);
    vector<int> sufMin(n + 1, INT_MAX), sufMax(n + 1, INT_MIN);

    for (int i = 0; i < n; i++) {
        preMin[i + 1] = min(preMin[i], a[i].second);
        preMax[i + 1] = max(preMax[i], a[i].second);
    }
    for (int i = n - 1; i >= 0; i--) {
        sufMin[i] = min(sufMin[i + 1], a[i].second);
        sufMax[i] = max(sufMax[i + 1], a[i].second);
    }

    auto ok = [&](int k) -> bool {
        int r = 0;
        for (int l = 0; l < n; l++) {
            while (r < n && a[r].first <= a[l].first + k - 1) r++;

            int mn = INT_MAX, mx = INT_MIN;
            if (l > 0) {
                mn = min(mn, preMin[l]);
                mx = max(mx, preMax[l]);
            }
            if (r < n) {
                mn = min(mn, sufMin[r]);
                mx = max(mx, sufMax[r]);
            }

            if (mn == INT_MAX || mx - mn + 1 <= k) return true;
        }
        return false;
    };

    int lo = 1, hi = max(w, h), ans = hi;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (ok(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << ans << "\n";
    return 0;
}
