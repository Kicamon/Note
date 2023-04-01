#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (int)b; i++)
typedef long long ll;

// FFT_MAXN = 2^k
// fft_init() to precalc FFT_MAXN-th roots

typedef long double db;
const int FFT_MAXN=262144, N = 301000;
const db pi=acosl(-1.);
struct cp{
	db a,b;
	cp operator+(const cp&y)const{return (cp){a+y.a,b+y.b};}
	cp operator-(const cp&y)const{return (cp){a-y.a,b-y.b};}
	cp operator*(const cp&y)const{return (cp){a*y.a-b*y.b,a*y.b+b*y.a};}
	cp operator!()const{return (cp){a,-b};};
}nw[FFT_MAXN+1];int bitrev[FFT_MAXN];
void dft(cp*a,int n,int flag=1){
	int d=0;while((1<<d)*n!=FFT_MAXN)d++;
	rep(i,0,n)if(i<(bitrev[i]>>d))swap(a[i],a[bitrev[i]>>d]);
	for (int l=2;l<=n;l<<=1){
		int del=FFT_MAXN/l*flag;
		for (int i=0;i<n;i+=l){
			cp *le=a+i,*ri=a+i+(l>>1),*w=flag==1?nw:nw+FFT_MAXN;
			rep(k,0,l>>1){
				cp ne=*ri**w;
				*ri=*le-ne,*le=*le+ne;
				le++,ri++,w+=del;
			}
		}
	}
	if(flag!=1)rep(i,0,n)a[i].a/=n,a[i].b/=n;
}
void fft_init(){
	int L=0;while((1<<L)!=FFT_MAXN)L++;
	bitrev[0]=0;rep(i,1,FFT_MAXN)bitrev[i]=bitrev[i>>1]>>1|((i&1)<<(L-1));
	nw[0]=nw[FFT_MAXN]=(cp){1,0};
	rep(i,0,FFT_MAXN+1)nw[i]=(cp){cosl(2*pi/FFT_MAXN*i),sinl(2*pi/FFT_MAXN*i)};	//very slow
}

void convo(db*a,int n,db*b,int m,db*c){
	static cp f[FFT_MAXN>>1],g[FFT_MAXN>>1],t[FFT_MAXN>>1];
	int N=2;while(N<=n+m)N<<=1;
	rep(i,0,N)
		if(i&1){
			f[i>>1].b=(i<=n)?a[i]:0.0;
			g[i>>1].b=(i<=m)?b[i]:0.0;
		}else{
			f[i>>1].a=(i<=n)?a[i]:0.0;
			g[i>>1].a=(i<=m)?b[i]:0.0;
		}
	dft(f,N>>1);dft(g,N>>1);
	int del=FFT_MAXN/(N>>1);
	cp qua=(cp){0,0.25},one=(cp){1,0},four=(cp){4,0},*w=nw;
	rep(i,0,N>>1){
		int j=i?(N>>1)-i:0;
		t[i]=(four*!(f[j]*g[j])-(!f[j]-f[i])*(!g[j]-g[i])*(one+*w))*qua;
		w+=del;
	}
	dft(t,N>>1,-1);
	rep(i,0,n+m+1)c[i]=(i&1)?t[i>>1].a:t[i>>1].b;
}

int n, q, p[N], vis[N];
db f[N], g[N], h2[N];
ll h[N];
vector<ll> ans[N];
set<int> cyclen;
int main() {
	fft_init();
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d" ,&p[i]);
	for (int i = 1; i <= n; i++) if (!vis[i]) {
		int u = i;
		vector<int> cyc;
		while (!vis[u]) {
			vis[u] = true;
			cyc.push_back(u);
			u = p[u];
		}
		int m = cyc.size();
		for (int j = 0; j < m; j++) {
			f[j] = cyc[j], g[j] = cyc[(m - j) % m];
			h[j] = 0;
		}
		convo(f, m - 1, g, m - 1, h2);
		for (int j = 0; j <= 2 * m - 2; j++) {
			h[j % m] += (ll)(h2[j] + 0.5);
		}
		if (!cyclen.count(m)) {
			cyclen.insert(m);
			ans[m] = vector<ll>(m, 0);
		}
		for (int j = 0; j < m; j++) ans[m][j] += h[j];
	}
	for (int i = 0; i < q; i++) {
		int x;
		scanf("%d", &x);
		ll s = 0;
		for (auto m : cyclen) s += ans[m][x % m];
		printf("%lld\n", s);
	}
}