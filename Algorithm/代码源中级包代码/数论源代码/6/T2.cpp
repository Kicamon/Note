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
int m, T, M, phipe;
pair<int, int> x[110];
ll pr[110];
ll ans[N], a[N], b[N], fac[1010000];

ll cntp, cnts;
ll calc(ll a, int p, int pe, int w) {
    ll val=1;
    while (a) {
        cntp += (a / p) * w;
        cnts += (a / pe) * w;
        val = val * fac[a % pe] % pe;
        a /= p;
    }
    return val;
}

ll binom(ll a, ll b, int p, int pe) {
    cntp = 0; cnts = 0;
    ll f1 = calc(a, p, pe, 1);
    ll f2 = calc(b, p, pe, -1);
    ll f3 = calc(a-b, p, pe, -1);
    ll v1 = f1 * powmod(f2 * f3 % pe, phipe - 1, pe) % pe;
    ll v2 = powmod(p, cntp, pe);
    ll v3 = powmod(fac[pe], cnts, pe);
    return v1 * v2 % pe * v3 % pe;
}

int main() {
    scanf("%d%d",&m,&T);
    M = m;
    int t = 0;
    for (int i = 2; i <= m; i++) if (m % i == 0) {
        int p = i, pe = 1;
        while (m % i == 0) m /= i, pe *= i;
        x[t++] = {p, pe};
    }
    
    for (int i = 0; i < t; i++) {
        int pe = x[i].se;
        for (int c = 0; c < M; c++)
            if (c % pe == 1 && c % (M / pe) == 0) {
                pr[i] = c;
                break;
            }
    }
    for (int i = 0; i < T; i++) {
        scanf("%lld%lld", &a[i], &b[i]);
    }
    for (int i = 0; i < t; i++) {
        int p = x[i].fi, pe = x[i].se;
        fac[0] = 1;
        for (int j = 1; j <= pe; j++) {
            if (j % p == 0) fac[j] = fac[j - 1];
            else fac[j] = fac[j - 1] * j % pe;
        }
        phipe = pe / p * (p - 1);
        for (int j = 0; j < T; j++) {
            ans[j] = (ans[j] + binom(a[j], b[j], p, pe)
                * pr[i]) % M;
        }
    }
    for (int j = 0; j < T; j++) {
        printf("%lld\n", ans[j]);
    }
}