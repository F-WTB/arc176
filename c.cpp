#include <bits/stdc++.h>
#include <atcoder/all>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace atcoder;
using ll = long long;
using bint = boost::multiprecision::cpp_int;
using mint = modint998244353;
using pr = pair<int, int>;
ostream &operator<<(ostream &os, const mint &x) {
    os << x.val();
    return os;
}
template <class T>
inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template <class T>
inline bool chmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
struct fast {
    fast() {
        cin.tie(0);
        ios::sync_with_stdio(0);
    }
} fast;

int N, M, A, B, C;
map<int, vector<pr>> mp;

int f(pr &x, pr &y) {
    if (x.first == y.first) return x.first;
    if (x.first == y.second) return x.first;
    if (x.second == y.first) return x.second;
    if (x.second == y.second) return x.second;
    return -1;
}
int f(vector<pr> &v) {
    int N = v.size();
    if (N < 2) return -1;
    if (N == 2)
        return f(v[0], v[1]);
    int t = f(v[0], v[1]);
    for (int i = 2; i < N; ++i)
        if (f(v[0], v[i]) != t) return -1;
    return t;
}

bool b[200000];

mint fct[200001] = {1};
mint prm(int n, int k) {
    if (n - k < 0) return 0;
    return fct[n] / fct[n - k];
}

int main() {
    for (int i = 0; i < 200000; ++i) fct[i + 1] = fct[i] * (i + 1);

    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        cin >> A >> B >> C, --A, --B, --C;
        if (C == 0) {
            cout << 0 << '\n';
            return 0;
        }
        mp[C].emplace_back(A, B);
    }

    int cnt = 0;
    mint ans = 1;
    for (auto [k, v] : mp) {
        if (v.size() == 1) {
            int c = !b[v[0].first] + !b[v[0].second];
            if (!c) {
                cout << 0 << '\n';
                return 0;
            }
            if (c == 2) ans *= 2 * (k - cnt);
        } else {
            int t = f(v);
            int c = 0;
            if (b[t]) {
                cout << 0 << '\n';
                return 0;
            }
            for (auto [x, y] : v) {
                if (x != t && !b[x]) ++c;
                if (y != t && !b[y]) ++c;
            }
            ans *= prm(k - cnt, c);
        }
        for (auto [x, y] : v) {
            if (!b[x]) ++cnt;
            b[x] = 1;
            if (!b[y]) ++cnt;
            b[y] = 1;
        }
    }
    cout << ans * fct[N - cnt] << '\n';
}
