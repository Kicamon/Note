#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1000000007;

const int N = 3010;

char s[N];
int c;
ll pw[N];

int main() {
	scanf("%s%d", s, &c);
	int n = strlen(s);
	pw[0] = 1;
	for (int i = 1; i <= n; i++) {
		pw[i] = pw[i - 1] * (c + 1) % mod;
	}
	ll ans = 0, pre = 1;
	for (int i = 0; i < n; i++) {
		if (s[i] == '1') {
			// 0?????
			ans = (ans + pre * pw[n - i - 1]) % mod;
			pre = pre * c %mod;
		}
	}
	ans = (ans + pre) % mod;
	printf("%lld\n", ans);
}