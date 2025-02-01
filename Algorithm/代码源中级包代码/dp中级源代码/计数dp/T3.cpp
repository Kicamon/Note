#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,p[100];
int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) p[i]=i;
    while (1) {
        bool val=1;
        for (int i=1;i<=n;i++) val&=p[i]%p[i%n+1]<=2;
        if (val) {
            for (int i=1;i<=n;i++) printf("%d ",p[i]); puts("");
        }
        if (!next_permutation(p+1,p+n+1)) break;
        if (p[1]!=1) break;
    }
}