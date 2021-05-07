const int N = 1e5 + 10;
int a[N],que[N];
ll solve(int x, int n) {
	int cnt = 0;
	for (int i = 2; i*i <= x; ++i) {
		if (x%i == 0) {
			a[++cnt] = i; while (x%i == 0) x /= i;
		}
	}
	if (x > 1) a[++cnt] = x;
	int cnt1 = 0; que[cnt1++] = -1;
	for (int i = 1; i <= cnt; ++i) {
		int tmp = cnt1;
		for (int j = 0; j < tmp; ++j) {
			que[cnt1++] = (-1)*que[j] * a[i];
		}
	}
	ll sum = 0;
	for (int i = 1; i < cnt1; ++i)
		sum += n / que[i];
	return sum;
}
int main() {
	n=min(p,q),m=max(p,q);
	ll ans=m;
	for(int i=2;i<=n;++i)
		ans+=m-solve(i);
	return 0;
}
