#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
template<typename T>
inline void rd(T& x)
{
	int tmp = 1; char c = getchar(); x = 0;
	while (c > '9' || c < '0') { if (c == '-')tmp = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	x *= tmp;
}
const int N = 3e5 + 10;
const int M = 1e7 + 10;
const int mod = 1e9 + 7, inf = 0x3f3f3f3f;
int head[N], cntE = 0;
struct edge {
	int next, to;
}e[M];
void add(int u, int v) {
	e[cntE].to = v;
	e[cntE].next = head[u];
	head[u] = cntE++;
}
int n;
int bit[N], a[N];
int fa[N][25] = { 0 }, h[N], lg[N];
int b[N];

void dfs(int x, int fx,int dep) {
	fa[x][0] = fx;
	h[x] = dep;
	for (int i = head[x]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v == fx) continue;
		dfs(v, x, dep + 1);
	}
}

void init() {
	dfs(a[1], 0, 0);
	for (int j = 1; j <= 20; ++j) {
		for (int i = 1; i <= n; ++i) {
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
		}
	}
	lg[0] = 0;
	for (int i = 1; i <= N - 10; ++i) {
		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
	}
}

int lca(int u,int v) {
	if (h[u] < h[v]) swap(u, v);
	for (int i = 0, tmp = h[u] - h[v]; i <= 19; ++i) {
		if ((1 << i) & tmp) u = fa[u][i];
	}
	if (u == v) return u;
	for (int i = lg[h[u]] - 1; i >= 0; --i) {
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}
//--------------------
int ans[N];
void dfs(int x, int fx) {
	for (int i = head[x]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v == fx) continue;
		dfs(v, x);
		ans[x] += ans[v];
	}
	ans[x] += b[x];
}
int main() {
#ifdef _DEBUG
		FILE* _INPUT = freopen("input.txt", "r", stdin);
	//	FILE* _OUTPUT = freopen("output.txt", "w", stdout);
#endif
	rd(n);
	memset(head, -1, sizeof(int) * (n + 10)); cntE = 0;
	for (int i = 1; i <= n; ++i) rd(a[i]);
	for (int i = 1; i < n; ++i) {
		int u, v; rd(u), rd(v);
		add(u, v);
		add(v, u);
	}
	init();
	memset(b, 0, sizeof(int) * (n + 10));
	memset(ans, 0, sizeof(int) * (n + 10));
	for (int i = 1; i <= n - 1; ++i) {
		int fx = lca(a[i], a[i + 1]);
		++b[a[i]];
		++b[a[i + 1]];
		--b[fx];
		--b[fa[fx][0]];
	}
 	dfs(a[1], 0);
	++ans[a[1]];
	for (int i = 1; i <= n; ++i) {
		printf("%d\n", ans[i] - 1);
	}
	return 0;
}
