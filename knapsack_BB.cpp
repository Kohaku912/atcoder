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

struct Item {
    i64 v, w;
    double density;
};
struct Node {
    int depth;
    i64 value, weight;
};
static const int MAXN = 100000;
static const int MAXSTACK = 1<<20;
Item items[MAXN];
i64 N,W,cum_v[MAXN+1], cum_w[MAXN+1];
double calc_upper(int depth, i64 rem) {
    if (rem <= 0) return 0.0;
    i64 tot_w = cum_w[N] - cum_w[depth];
    i64 tot_v = cum_v[N] - cum_v[depth];
    if (rem >= tot_w) return (double)tot_v;
    double ub = 0.0;
    i64 used = 0;
    for (int i = depth; i < N; ++i) {
        i64 v = items[i].v;
        i64 w = items[i].w;
        if (used + w <= rem) {
            ub += v;
            used += w;
        } else {
            ub += (rem - used) * (items[i].density);
            break;
        }
    }
    return ub;
}
void solve() {
    cin >> N >> W;
    rep(i,N) {
        cin >> items[i].v >> items[i].w;
        items[i].density = (double)items[i].v / items[i].w;
    }

    sort(items, items+N, [](const Item& a, const Item& b){
        if (a.density != b.density) return a.density > b.density;
        if (a.w != b.w) return a.w < b.w;
        return a.v > b.v;
    });

    cum_v[0] = cum_w[0] = 0;
    for(int i = 0; i < N; ++i){
        cum_v[i+1] = cum_v[i] + items[i].v;
        cum_w[i+1] = cum_w[i] + items[i].w;
    }

    static Node stk[MAXSTACK];
    int top = 0;
    stk[top++] = {0, 0, 0};
    i64 best = 0;

    while(top){
        Node cur = stk[--top];
        int d = cur.depth;
        i64 val = cur.value;
        i64 wt  = cur.weight;

        if (val > best) best = val;
        if (d == N) continue;
        if (val + (cum_v[N] - cum_v[d]) <= best) continue;
        double ub = val + calc_upper(d, W - wt);
        if (ub <= best) continue;
        stk[top++] = {d+1, val, wt};
        i64 w = items[d].w, v = items[d].v;
        if (wt + w <= W) {
            stk[top++] = {d+1, val+v, wt+w};
        }
    }
    cout << best << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}