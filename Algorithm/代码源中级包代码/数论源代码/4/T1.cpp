#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=50000000;
int pr[N/5],p[N+100],tot;
uint ans=0,a,b;
int n;

int main() {
    scanf("%d%u%u",&n,&a,&b);
    p[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!p[i]) p[i] = i, pr[++tot]=i,ans^=(a*i+b);
        for (int j=1;j<=tot&&pr[j]*i<=n;j++) {
            p[i*pr[j]]=pr[j];
            if (p[i]==pr[j]) break;
        }
    }
    printf("%u\n",ans);
}