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
    string S;
    cin >> S;
    int N = S.size() - 1;
    rep(bit, (1 << (N))) {
        i64 tmp = S[0] - '0';
        std::string ans = std::string(1, S[0]);
        rep(i, N) {
            if (bit & (1 << i)) {
                tmp -= (S[i + 1] - '0');
                ans += '-' + std::string(1, S[i + 1]);
            } else {
                tmp += (S[i + 1] - '0');
                ans += '+' + std::string(1, S[i + 1]);
            }
        }
        if (tmp == 7) {
            std::cout << ans << "=7" << std::endl;
            return;
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}