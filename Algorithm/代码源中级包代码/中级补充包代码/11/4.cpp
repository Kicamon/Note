#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rep(i, a, b) for (int i = a; i < (int)b; i++)
typedef long long ll;

// FFT_MAXN = 2^k
// fft_init() to precalc FFT_MAXN-th roots

typedef double db;
const int FFT_MAXN=262144, N = 301000;
const db pi=acos(-1.);
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
	rep(i,0,FFT_MAXN+1)nw[i]=(cp){cos(2*pi/FFT_MAXN*i),sin(2*pi/FFT_MAXN*i)};	//very slow
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

int n, sz[N], maxs[N], L;
vector<int> e[N];
bool del[N];
ll ans[N];
db f[N], g[N];

void solve(int u, int s) {
	int ms = s + 1, root = -1;
	function<void(int, int)> dfs1 = [&](int u, int par) {
		sz[u] = 1;
		maxs[u] = 0;
		for (auto v: e[u]) {
			if (del[v] || v == par) continue;
			dfs1(v, u);
			sz[u] += sz[v];
			maxs[u] = max(maxs[u], sz[v]);
		}
		maxs[u] = max(maxs[u], s - sz[u]);
		if (maxs[u] < ms) ms = maxs[u], root = u;
	};
	dfs1(u, -1);
	vector<int> d1, d2;
	d1.push_back(0);
	auto calc = [&](vector<int> &d, int sgn) {
		int m = (*max_element(d.begin(), d.end())) + 1;
		for (int i = 0; i <= m; i++) f[i] = 0;
		for (auto x : d) f[x] += 1;
		convo(f, m, f, m, g);
		for (int i = 0; i <= 2 * m; i++) ans[i] += (ll)(g[i] + 0.5) * sgn;
	};
	for (auto v : e[root]) {
		if (del[v]) continue;
		d2.clear();
		function<void(int, int, int)> dfs2 = [&](int u, int par, int dep) {
			d1.push_back(dep);
			d2.push_back(dep);
			for (auto v : e[u]) {
				if (del[v] || v == par) continue;
				dfs2(v, u, dep + 1);
			}
		};
		dfs2(v, root, 1);
		calc(d2, - 1);
	}
	calc(d1, 1);
	del[root] = true;
	for (auto v : e[root]) {
		if (!del[v]) solve(v, sz[v]);
	}
}

int main() {
	fft_init();
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	solve(1, n);
	for (int i = 1; i <= n - 1; i++)
		printf("%lld\n", ans[i] / 2);
}