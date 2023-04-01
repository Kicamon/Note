#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int pf[1010], t;

ll powmod(ll a,ll b,ll mod) {
    ll res = 1; a%=mod;
    for(;b;b>>=1) {
        if(b&1)res=res*a%mod;
        a=a*a%mod;
    }
    return res;
}

int main() {
    int p, T;
    scanf("%d%d", &p, &T);
    int m = p - 1;
    for (int i = 2; i * i <= m; i++) {
        if (m % i == 0) {
            pf[t++] = i;
            while (m % i == 0) m /= i;
        }
    }
    if (m != 1) pf[t++] = m;
    for (int tc = 0; tc < T; tc++) {
        int a;
        scanf("%d", &a);
        int d = p - 1;
        for (int i = 0; i < t; i++)
            while (d % pf[i] == 0 && powmod(a, d / pf[i], p) == 1)
                d /= pf[i];
        printf("%d\n",d);
    }
}