#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <stack>
#include <deque>
#include <string>
#include <ctime>
#include <bitset>
#include <queue>
#include <cassert>
#include<unordered_set>
#include<unordered_map>
#include<string.h>
#include <random>
#include <chrono>
#include <math.h>
using namespace std;
#define ll long long
#define ld double
#define pi pair<int, int>
#define pll pair<ll, ll>
#define mint map<int, int>*;
#define vi vector<int>
#define int long long
template<typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (T& o : v) {
        is >> o;
    }
    return is;
}
class Query {
public:
    int l = 0;
    int r = 0;
    int idx = 0;
    Query(int L, int R, int Num) {
        l = L;
        r = R;
        idx = Num;
    }
};
int NOD(int a, int b) {
    if (a < 0 || b < 0) return NOD(abs(a), abs(b));
    return b ? NOD(b, a % b) : a;
}
const ld EPS = 1e-3;
const ll INF = 1e18 + 3;
const ll MOD1 = 939999971;
const ll POWER = 5;
const ll HASHMOD1 = 939999971;
const ll HASHMOD2 = 23;
const ll MOD2 = 998244353;
const ld PHI = atan(1) * 4;
const ll MOD3 = 1e9 + 7;
const int root = 31;
const int root_1 = 128805723;
const int root_pw = 1 << 23;
vector<int> dX = { 1, 0, -1, 0, };
vector<int> dY = { 0, 1, 0, -1 };
mt19937 MT(chrono::steady_clock::now().time_since_epoch().count());
ifstream fin("tmp.txt");
const int block_size = 500;
const int maxN = 2e6 + 5;
const int LOG = 19;
const int PR = 31;
stack<pair<int*, int>> roll_back;
vector<vector<pi>> here;
vector<int> sz;
vector<int> mn;
vector<int> p;
map<pair<int, int>, int> edg;
vector<bool> already;
vector<set<int>> s;
vector<int> ans;
vector<int> pos;
vector<pair<pair<bool, int>, pi>> aa;
int getP(int a) {
    if (p[a] == a) return a;
    return getP(p[a]);
}
void add(int v, int l, int r, int L, int R, pi& p1) {
    if (l > R || L > r) return;
    if (l >= L && R >= r) {
        here[v].push_back(p1);
        return;
    }
    int mid = (l + r) / 2;
    add(2 * v, l, mid, L, R, p1);
    add(2 * v + 1, mid + 1, r, L, R, p1);
}
void unite(int a, int b) {
    int p1 = getP(a);
    int p2 = getP(b);
    if (p1 == p2) return;
    if (sz[p1] < sz[p2]) swap(p1, p2);
    roll_back.push({ &sz[p1], sz[p1] });
    roll_back.push({ &mn[p1], mn[p1] });
    roll_back.push({ &p[p2], p[p2] });
    mn[p1] = min(mn[p1], mn[p2]);
    p[p2] = p1;
    sz[p1] += sz[p2];
}
vector<int> aans;
vector<int> remap;
void bd(int v, int l, int r) {
    int left_size = roll_back.size();
    for (auto x : here[v]) {
        unite(x.first, x.second);
    }
    if (l == r) {
        if (ans[l] != -1) {
            aans[l] = (mn[getP(ans[l])]);
        }
        return;
    }
    int mid = (l + r) / 2;
    bd(2 * v, l, mid);
    bd(2 * v + 1, mid + 1, r);
    while (roll_back.size() != left_size) {
        *roll_back.top().first = roll_back.top().second;
        roll_back.pop();
    }
}
void solve() {
    int N = 0, M = 0;
    cin >> N >> M;
    already.assign(M, false);
    s.assign(N, set<int>());
    pos.assign(4 * M + N, -1);
    for (int i = 0; i < N; ++i) {
        s[i].insert(4 * M + i);
        pos[4 * M + i] = i;
    }
    for (int i = 0; i < M; ++i) {
        int num = 0; cin >> num;
        num--;
        remap[i] = num;
        int fir = 4 * (M - i) - 1;
        int sec = fir - 1;
        int thi = sec - 1;
        int fr = thi - 1;
        pos[fir] = num;
        pos[sec] = num + 1;
        pos[thi] = num;
        pos[fr] = num + 1;
        s[num].insert(M - 1 - i);
        s[num + 1].insert(i);
        aa.push_back({ { false, 0 }, { fir, sec } });
        aa.push_back({ {false, 0}, {fr, thi} });
    }
    for (int ps = 0; ps < N; ++ps) {
        for (auto it1 = s[ps].end(); it1 != s[ps].begin(); ) {
            it1--;
            if (*it1 < M) {
                int num = remap[*it1];
                if (num == ps) {
                    auto it2 = it1;
                    if (it1 == s[ps].begin()) continue;
                    it2--;
                    int thi1 = 4 * (*it1 + 1) - 3;
                    innt sec = 4 * (*it2 + 1) - 2;
                    aa.push_back({})
                }
            }
            else {

            }
        }
    }
    int Q = 0; cin >> Q;
    ans.assign(Q, -1);
    for (int j = 0; j < Q; ++j) {
        char tp = 'A';
        cin >> tp;
        if (tp == 'B') {
            int num = 0;
            cin >> num;
            num--;
            ans[j] = num + M;
            continue;
        }
        int num = 0; cin >> num;
        num--;
        num = M - 1 - num;
        if (already[num]) continue;
        already[num] = true;
        int up = INF, left = INF, right = -INF, down = -INF;
        int rght_1 = INF;
        int lght_1 = INF;
        auto it1 = s[pos[num]].lower_bound(num);
        if (it1 != s[pos[num]].begin()) down = *(--it1);
        if (pos[num] != N - 1) {
            auto it2 = s[pos[num] + 1].lower_bound(num);
            if (it2 != s[pos[num] + 1].begin()) right = *--it2;
            rght_1 = *it2;
        }
        up = *s[pos[num]].upper_bound(num);
        if (pos[num] != 0) {
            left = *s[pos[num] - 1].upper_bound(num);
            auto it77 = s[pos[num] - 1].lower_bound(num);
            if (it77 != s[pos[num] - 1].begin()) lght_1 = *--it77;
        }
        if (max(right, down) != -INF) aa.push_back({ {true, j}, {num, max(right, down)} });
        if (left != INF && left < M) aa.push_back({ {true, j}, {left, num} });
        cout << num << " " << pos[num] << " "  << left << " " << right << " " << up << " " << down << " " << rght_1 << "\n";
        if(rght_1 < num) aa.push_back({ {true, j}, {up, num} });
        if (right == -INF && down == -INF) continue;
        if (rght_1 < num) {
            if (up < M) aa.push_back({ {false, j}, {up, min(right, down)} });
            else {
                if(down != -INF) aa.push_back({ {false, j}, {up, down} });
            }
        }
        if(left != INF && down != -INF && left < M) aa.push_back({ {false, j}, {left, down} });
    }
    cout << " OUT OF HERE \n";
    for (auto x : aa) cout << x.first.first << " " << x.first.second << " " << x.second.first << " " << x.second.second << "\n";
    cout << " FINITA LA COMEDIA\n";
    here.assign(4 * Q, vector<pi>());
    for (int i = 0; i < aa.size(); ++i) {
        auto pr = aa[i].second;
        if (aa[i].first.first) {
            add(1, 0, Q - 1, edg[pr], aa[i].first.second, pr);
            cout << pr.first << " " << pr.second << " " << edg[pr] << " " << aa[i].first.second << "\n";
            edg[pr] = -1;
        }
        else {
            edg[pr] = aa[i].first.second;
        }
    }
    cout << " A A A A \n";
    aans.assign(Q, 0);
    for (auto &x : edg) {
        if (x.second == -1) continue;
        pi p1 = x.first;
        cout << x.second << " " << Q - 1 << " " << p1.first << " " << p1.second << "\n";
        add(1, 0, Q - 1, x.second, Q - 1, p1);
    }
    cout << " O O  O \n";
    sz.assign(N + M, 1);
    p.assign(N + M, 0);
    mn.assign(N + M, 0);
    iota(p.begin(), p.end(), 0);
    iota(mn.begin(), mn.end(), 0);
    bd(1, 0, Q - 1);
    for (int i = 0; i < Q; ++i) {
        if (ans[i] == -1) continue;
        if (aans[i] >= M) cout << aans[i] - M + 1 << " ";
        else cout << pos[aans[i]] + 2 << " ";
    }
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(12);
    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}