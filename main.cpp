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
    i64 N,W;
    cin >> N >> W;
    vector<pair<i64, i64>> items;
    vector<i64> dp(W + 1, 0);
    rep(i,N) {
        i64 w, v;
        cin >> v >> w;
        if (w <= W) {
            items.emplace_back(v, w);
        }
    }
    N = items.size();
    rep(i,N) {
        for(i64 j = W; j >= items[i].second; j--) {
            chmax(dp[j], dp[j - items[i].second] + items[i].first);
        }
    }
    i64 ans = 0;
    rep(i,W + 1) {
        chmax(ans, dp[i]);
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