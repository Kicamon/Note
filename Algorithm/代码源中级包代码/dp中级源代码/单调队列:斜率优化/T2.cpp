#include<bits/stdc++.h>
using namespace std;

const int N = 2e2 + 9;
const int dx[5]={0, -1, 1, 0, 0},dy[5]={0, 0, 0, -1, 1};

int f[N][N], n, m, ans;
char G[N][N];
struct T {int x,y;} q[N];
void sol(int x, int y, int l, int d, int n) {
    int h = 1, t = 0;
    for (int i = 1; i <= n; i++) {
        if (G[x][y] == 'x') h = 1, t = 0;
        else {
            int v = f[x][y] - i;
            while (h <= t && q[t].x < v) --t;
            q[++t] = {v, i};
            while(h <= t && i - q[h].y > l) ++h;
            f[x][y] = i + q[h].x;
            ans = max(ans, f[x][y]);
        }
        x += dx[d];
        y += dy[d];
    }
}
int main(){
    memset(f,-63,sizeof f);
    int x, y, k;
    cin>>n>>m>>x>>y>>k;
    f[x][y]=0;
    for (int i=1;i<=n;++i) cin>>G[i]+1;
    for(int i=1;i<=k;++i) {
        int x, y, z;
        cin >> x >> y >> z;
        y = y - x + 1;
        if(z==1) for(int j=1;j<=m;++j) sol(n,j,y,z, n);
        else if(z==2) for(int j=1;j<=m;++j) sol(1,j,y,z, n);
        else if(z==3) for(int j=1;j<=n;++j) sol(j,m,y,z, m);
        else for(int j=1;j<=n;++j) sol(j,1,y,z, m);
    }
    cout<<ans<<'\n';
}
