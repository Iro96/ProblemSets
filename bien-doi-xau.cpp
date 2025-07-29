#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    int m;
    cin >> m;

    int W = (n + 63) >> 6;
    vector< vector<uint64_t> > bits(26, vector<uint64_t>(W, 0ULL));

    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        int w = i >> 6;
        int b = i & 63;
        bits[c][w] |= (1ULL << b);
    }

    while (m--) {
        int l, r;
        char c1, c2;
        cin >> l >> r >> c1 >> c2;
        if (c1 == c2) continue;
        int x = c1 - 'a';
        int y = c2 - 'a';

        int wl = l >> 6;
        int bl = l & 63;
        int wr = r >> 6;
        int br = r & 63;

        if (wl == wr) {
            uint64_t mask = (~0ULL >> (63 - br));
            mask &= (~0ULL << bl);
            uint64_t tgt = bits[x][wl] & mask;
            bits[x][wl] ^= tgt;
            bits[y][wl] |= tgt;
        } else {
            uint64_t maskl = (~0ULL << bl);
            uint64_t tgtl = bits[x][wl] & maskl;
            bits[x][wl] ^= tgtl;
            bits[y][wl] |= tgtl;

            for (int w = wl + 1; w < wr; w++) {
                uint64_t tgt = bits[x][w];
                bits[x][w] ^= tgt;
                bits[y][w] |= tgt;
            }

            uint64_t maskr = (~0ULL >> (63 - br));
            uint64_t tgtr = bits[x][wr] & maskr;
            bits[x][wr] ^= tgtr;
            bits[y][wr] |= tgtr;
        }
    }

    string ans(n, '?');
    for (int i = 0; i < n; i++) {
        int w = i >> 6;
        int b = i & 63;
        for (int c = 0; c < 26; c++) {
            if (bits[c][w] >> b & 1ULL) {
                ans[i] = char('a' + c);
                break;
            }
        }
    }

    cout << ans;
    return 0;
}
