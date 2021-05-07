#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct edge {
	int u, v, w;
	bool friend operator<(const edge& a, const edge& b) {
		return a.w < b.w;
	}
}e[M];
int fa[N], n;
int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}
int MST, num[N], ans//¿ÉÄÜÐÔ 
void kruskal() {
	for (int i = 0; i <= n; ++i) fa[i] = i, num[i] = 1;
	sort(e, e + m); MST = ans = 0;
	for (int i = 0, cntm = 0; i < m && cntm < n; ++i) {
		int fx = get(e[i].u), fy = get(e[i].v);
		if (fx != fy) {
			MST += e[i].w;
			ans += num[fx] * num[fy];
			fa[fx] = fy;
			num[fy] += num[fx];
			++cntm;
		}
	}
}
