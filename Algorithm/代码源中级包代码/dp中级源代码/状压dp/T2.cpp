#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

unsigned int A,B,C;
const int N = (1 << 22) + 10;
const int M = 22;

int f[N], a[N];
int n;

int main(){
    scanf("%d", &n);
    for (int i = 0; i < (1 << M); i++)
        f[i] = n + 1;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        a[i] = x;
        f[x] = min(f[x], i);
    }
   	for (int i = 0; i < M; i++)
   		for (int j = 0; j < (1 << M); j++) {
   			if (j & (1 << i)) f[j] = min(f[j], f[j - (1 << i)]);
   		}
    for (int i = 1; i <= n; i++) {
        int x = (1 << M) - 1 - a[i];
        printf("%d%c", (f[x] > n) ? -1 : f[x], " \n"[i == n]);
    }
}