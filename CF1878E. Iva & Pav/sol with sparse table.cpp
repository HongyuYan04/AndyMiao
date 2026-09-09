#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    const int logn = std::__lg(n);
    std::vector<std::vector<int>> f(logn + 1, std::vector<int>(n + 1));
    
    f[0] = a;

    for (int j = 1; j <= logn; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[j][i] = f[j - 1][i] & f[j - 1][i + (1 << (j - 1))];
        }
    }

    auto Query = [&](int l, int r) -> int {
        int t = std::__lg(r - l + 1);
        return f[t][l] & f[t][r - (1 << t) + 1];
    };

    int q;
    std::cin >> q;

    while (q--) {
        int l, k;
        std::cin >> l >> k;

        int lo = l, hi = n;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (Query(l, mid) >= k) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        if (Query(l, lo) >= k) {
            std::cout << lo << " ";
        } else {
            std::cout << -1 << " ";
        }
    }
    std::cout << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}
