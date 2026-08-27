#include <bits/stdc++.h>

using i64 = long long;

int t, n, k;
std::string s;

void solve() {
    std::cin >> n >> k >> s;

    std::vector<int> suf(n);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = (s[i] == '0' ? -1 : 1);
        if (i < n - 1) {
            suf[i] += suf[i + 1];
        }
    }

    std::sort(suf.begin() + 1, suf.end(), std::greater<int>());
    
    i64 F = 0;
    for (int i = 1; i <= n - 1; i++) {
        F += suf[i];
        if (F >= k) {
            std::cout << i + 1 << "\n";
            return ;
        }
    }
    std::cout << -1 << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}
