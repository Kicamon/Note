#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int pf[1010];

ll powmod(ll a,ll b,ll mod) {
    ll res = 1; a%=mod;
    for(;b;b>>=1) {
        if(b&1)res=res*a%mod;
        a=a*a%mod;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int p;
        scanf("%d", &p);
        int m = p - 1, t = 0;
        for (int i = 2; i * i <= m; i++) {
            if (m % i == 0) {
                pf[t++] = i;
                while (m % i == 0) m /= i;
            }
        }
        if (m != 1) pf[t++] = m;
        for (int g = 1; g < p; g++) {
            bool valid = true;
            for (int i = 0; i < t; i++)
                if (powmod(g, (p - 1) / pf[i], p) == 1) {
                    valid = false;
                    break;
                }
            if (valid) {
                printf("%d\n", g);
                break;
            }
        }
    }
}