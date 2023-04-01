#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b,ll mod) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N = 101000;
int m, T, M, G;
int x[110];
ll pr[110];
ll ans, a[N], b[N], fac[1010000], fnv[1010000];

ll binom2(ll a, ll b, int p) {
    if (b < 0 || b > a) return 0;
    return fac[a] * fnv[b] % p * fnv[a - b] % p;
}

ll binom(ll n, ll m, int p) {
    ll ans = 1;
    while (n > 0 || m > 0) {
        ans = ans * binom2(n % p, m % p, p) % p;
        n /= p; m /= p;
    }
    return ans;
}

const int mod = 999911659;
int main() {
    int n;
    scanf("%d%d",&n, &G);

    if (G % mod == 0) {
        puts("0");
        return 0;
    }
    M = mod - 1;
    m = mod - 1;
    int t = 0;
    for (int i = 2; i <= m; i++) if (m % i == 0) {
        int p = i;
        m /= i;
        x[t++] = p;
    }
    
    for (int i = 0; i < t; i++) {
        int pe = x[i];
        int Mi = M / pe;
        for (int c = 0; c < M; c += Mi)
            if (c % pe == 1) {
                pr[i] = c;
                break;
            }
    }
    for (int i = 1; i * i <= n; i++) if (n % i == 0) {
        a[T] = n; b[T] = i; T++;
        if (n / i != i) {
            a[T] = n; b[T] = n / i; T++;
        }
    }
    for (int i = 0; i < t; i++) {
        int p = x[i];
        fac[0] = 1; fnv[0] = 1;
        for (int j = 1; j < p; j++) {
            fac[j] = fac[j - 1] * j % p;
            fnv[j] = powmod(fac[j], p - 2, p);
        }
        for (int j = 0; j < T; j++) {
            ans = (ans + binom(a[j], b[j], p) * pr[i]) % M;
        }
    }
    printf("%lld\n",powmod(G, ans, mod));
}