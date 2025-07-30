#include <iostream>
#include <unordered_map>
#include <queue>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

struct hash_pair {
    size_t operator()(const pair<int, int>& p) const {
        return static_cast<size_t>(p.first) * 1000003 + p.second;
    }
};

int main() {
    int M;
    cin >> M;

    int N = 1 + 3 * M * (M + 1);

    unordered_map<pair<int, int>, int, hash_pair> honey;
    unordered_map<pair<int, int>, long long, hash_pair> dp;

    for (int i = 0; i < N; ++i) {
        int q, r, s, a;
        cin >> q >> r >> s >> a;
        honey[make_pair(q, r)] = a;
    }

    int X, Y, Z;
    cin >> X >> Y >> Z;
    pair<int, int> target = make_pair(X, Y);

    queue< pair<int, int> > q;
    pair<int, int> start = make_pair(0, -M);
    dp[start] = honey[start];
    q.push(start);

    int dq[3] = {1, -1, 0};
    int dr[3] = {0, 1, 1};

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();
        int x = cur.first;
        int y = cur.second;
        long long current = dp[cur];

        for (int i = 0; i < 3; ++i) {
            int nx = x + dq[i];
            int ny = y + dr[i];
            int nz = -nx - ny;

            if (max(abs(nx), max(abs(ny), abs(nz))) > M) continue;

            pair<int, int> next = make_pair(nx, ny);
            if (honey.find(next) == honey.end()) continue;

            long long new_val = current + honey[next];
            if (dp.find(next) == dp.end() || new_val > dp[next]) {
                dp[next] = new_val;
                q.push(next);
            }
        }
    }

    cout << dp[target] << endl;
    return 0;
}
