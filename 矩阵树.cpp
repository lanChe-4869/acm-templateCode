
const int N
//计算行列式 
ll a[N][N];
ll gauss(int n) {
	int sign = 0;
	ll ans = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			int x = i, y = j;
			while (a[y][i]) {
				ll t = a[x][i] / a[y][i];
				for (int k = i; k <= n; ++k) 
					a[x][k] = (a[x][k] - a[y][k] * t) % mod;
				swap(x, y); 
			}
			if (x != i) {
				for (int k = 1; k <= n; ++k) 
					swap(a[i][k], a[x][k]);
				sign ^= 1; 
			}
		}
		ans = ans * a[i][i] % mod;
	}
	if (sign) ans = -ans;
	if (ans < 0) ans += mod;
	return ans;
}
ll a[N][N];
void init(){
	memset(a,0,sizeof a);
	int n,m;
	for(int i=1;i<=m;++i){
		int u,v,w;read(u),read(v),read(w);
		a[u][v]=--a[v][u];
		++a[u][u];
		++a[v][v];
	}
	gauss(n-1);
}
