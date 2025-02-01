#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool solve() {
    int n;
    scanf("%d", &n);
    map<int, vector<pair<int,int>>> eqns;
    for (int i = 0; i < n; i++) {
        int a, m;
        scanf("%d%d", &a, &m);
        for (int j = 2; j * j <= m; j++) if (m % j == 0) {
            int p = j, pe = 1;
            while (m % j ==0) m /= j, pe = pe * j;
            eqns[p].push_back({pe, a % pe});
        }
        if (m != 1) {
            eqns[m].push_back({m, a % m});
        }
    }
    for (auto eq : eqns) {
        auto eqn = eq.second;
        int v = max_element(eqn.begin(), eqn.end()) -> second;
        for (auto p : eqn) {
            if (v % p.first != p.second) return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        puts(solve()?"Yes":"No");
    }
}