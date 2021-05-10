#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ull, ull> pii;
typedef pair<ll, ll>pll;
template<typename T>
inline void rd(T& x) {
	int tmp = 1;
	char c = getchar();
	x = 0;
	while (c > '9' || c < '0') {
		if (c == '-')tmp = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	x *= tmp;
}
const int N = 1e4 + 10;
const int M = 2e7 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ull seed = 31;
ll gcd(ll x, ll y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}

int head[N], cntE = 0;
struct edge {
	int next, to, w;
}e[M];
void add(int u, int v, int w = 0) {
	e[cntE].w = w;
	e[cntE].to = v;
	e[cntE].next = head[u];
	head[u] = cntE++;
}
int n, m, k;
int rt, sz, maxn;
int sim[N], mxson[N];
bool vis[N];
void getroot(int x, int fx) {
	sim[x] = 1; mxson[x] = 0;
	for (int i = head[x]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (vis[v] || v == fx) continue;
		getroot(v, x);
		sim[x] += sim[v];
		mxson[x] = max(mxson[x], sim[v]);
	}
	mxson[x] = max(mxson[x], sz - sim[x]);
	if (mxson[x] < maxn) {
		maxn = mxson[x];
		rt = x;
	}
}
ll ans, dis[N];
int tot;
void dfs(int x, int fx, ll len) {
	dis[++tot] = len;
	for (int i = head[x]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (vis[v] || v == fx) continue;
		dfs(v, x, len + e[i].w);
	}
}
ll cal(int x, int len) {
	tot = 0;
	dfs(x, 0, len);
	sort(dis + 1, dis + 1 + tot);
	int l = 1, r = tot;
	int res = 0;
	while (l < r) {
		if (dis[l] + dis[r] <= k) res += r - l, ++l;
		else --r;
	}
	return res;
}
void divide(int x) {
	vis[x] = true;
	ans += cal(x, 0);
	for (int i = head[x]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (vis[v]) continue;
		ans -= cal(v, e[i].w);
		sz = sim[v];
		maxn = inf;
		getroot(rt = v, 0);
		divide(rt);
	}
}
int main() {
#ifdef _DEBUG
	FILE* _INPUT = freopen("input.txt", "r", stdin);
	//	FILE* _OUTPUT = freopen("output.txt", "w", stdout);
#endif
	int T = 1, cas = 0;
	while (scanf("%d %d", &n, &k), n | k) {
		memset(head, -1, sizeof(int) * (n + 10)); cntE = 0;
		for(int i=1;i<n;++i){
			int u, v, w; rd(u), rd(v), rd(w);
			add(u, v, w);
			add(v, u, w);
		}
		memset(vis, false, sizeof(bool) * (n + 10));
		ans = 0; sz = n; maxn = inf;
		getroot(rt = 1, 0);
		divide(rt);
		printf("%lld\n", ans);
	}
	return 0;
}
