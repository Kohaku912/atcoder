#include<bits/stdc++.h>
#include <algorithm>
using namespace std;
using i64 = long long;
#define Yes(b) ((b)?"Yes":"No")
#define YES(b) ((b)?"YES":"NO")
#define rep(i,n) for (int i=0; i<(n); i++)
#define repe(i,a,b) for (int i=(a); i<(b); i++)
template<typename A> void chmin(A& l, const A& r){ if(r < l) l = r; }
template<typename A> void chmax(A& l, const A& r){ if(l < r) l = r; }
const i64 INF = 1001001001001001001;

void solve() {
    i64 N,W,V = 0,ans = 0, maxW = 0;
    cin >> N >> W;
    vector<pair<i64, i64>> items;
    rep(i,N) {
        i64 w, v;
        cin >> v >> w;
        items.emplace_back(v, w);
        V += v;
        chmax(maxW, w);
    }
    if(N <= 30){
        // Meet in the middle
        int nA = N / 2;
        int nB = N - nA;
        auto enum_subsets = [&](int offset, int n) {
            vector<pair<i64,i64>> res;
            int tot = 1 << n;
            for (int mask = 0; mask < tot; mask++) {
                i64 sw = 0, sv = 0;
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        sw += items[offset + i].second;
                        sv += items[offset + i].first;
                    }
                }
                if (sw <= W)
                    res.emplace_back(sw, sv);
            }
            return res;
        };

        auto A = enum_subsets(0, nA);
        auto B = enum_subsets(nA, nB);
        auto prune = [&](vector<pair<i64,i64>>& vec) {
            sort(vec.begin(), vec.end(),
                [](auto &a, auto &b) {
                    if (a.first != b.first) return a.first < b.first;
                    return a.second > b.second;
                });
            vector<pair<i64,i64>> tmp;
            i64 maxv = -1;
            for (auto &p : vec) {
                if (p.second > maxv) {
                    tmp.push_back(p);
                    maxv = p.second;
                }
            }
            vec.swap(tmp);
        };

        prune(A);
        prune(B);
        vector<i64> Bw, Bv;
        for (auto &p : B) {
            Bw.push_back(p.first);
            Bv.push_back(p.second);
        }

        for (auto &pa : A) {
            i64 wa = pa.first, va = pa.second;
            i64 rem = W - wa;
            int idx = upper_bound(Bw.begin(), Bw.end(), rem) - Bw.begin() - 1;
            if (idx >= 0) {
                ans = max(ans, va + Bv[idx]);
            } else {
                ans = max(ans, va);
            }
        }
    }else if(maxW <= 1000) {
        // Weight based knapsack
        vector<i64> dp(W + 1, 0);
        dp[0] = 0; 
        rep(i, N) {
            for (int j = W; j >= items[i].second; --j) {
                chmax(dp[j], dp[j - items[i].second] + items[i].first);
            }
        }
        rep(i, W + 1) {
            chmax(ans, dp[i]);
        }
    }else{
        // Value based knapsack
        vector<i64> dp(V+1, INF);
        dp[0] = 0; 
        rep(i,N) {
            for(i64 j = V; j >= items[i].first; j--) {
                chmin(dp[j], dp[j - items[i].first] + items[i].second);
            }
        }
        for (i64 val = V; val >= 0; --val) {
            if (dp[val] <= W) {
                ans = val;
                break;
            }
        }
    }
    cout << ans << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}