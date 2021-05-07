

#include <bits/stdc++.h>    //无权图的最大边数匹配 
using namespace std;
typedef long long ll;
const int N=5e2+10;
const int M=1e5+10;
vector<int>vec[N];
int match[N];
int k,m,n;
bool vis[N];
bool dfs(int x){
	for(int i=0;i<vec[x].size();++i){
		int v=vec[x][i];
		if(!vis[v]){
			vis[v]=1;
			if(match[v]!=-1||dfs(match[v])){
				match[v]=x;
				return true;
			}
		}
	}
	return false;
}

//----------------------------------------------------
int match[N], lx[N], ly[N], slack[N];//二分图带权最大匹配 
int G[N][N];
bool visx[N], visy[N];
int nx, ny;
bool dfs(int x) {
	visx[x] = true;
	for (int i = 0; i < ny; ++i) {
		if (visy[i]) continue;
		int tmp = lx[x] + ly[i] - G[x][i];
		if (!tmp) {
			visy[i] = true;
			if (match[i] == -1 || dfs(match[i])) {
				match[i] = x;
				return true;
			}
		}
		else if (slack[i] > tmp) {
			slack[i] = tmp;
		}
	}
	return false;
}
void KM() {
	memset(match, -1, sizeof(int) * (ny + 10));
	memset(ly, 0, sizeof(int) * (ny + 10));
	for (int i = 0; i < nx; ++i) {
		lx[i] = 0;
		for (int j = 0; j < ny; ++j) {
			if (lx[i] < G[i][j]) lx[i] = G[i][j];
		}
	}
	for (int i = 0; i < nx; ++i) {
		memset(slack, inf, sizeof(int) * (ny + 10));
		while (1) {
			memset(visx, false, sizeof(bool) * (nx + 10));
			memset(visy, false, sizeof(bool) * (ny + 10));
			if (dfs(i)) break;
			int tmp = inf;
			for (int j = 0; j < ny; ++j) {
				if (!visy[j] && tmp > slack[j]) tmp = slack[j];
			}
			for (int j = 0; j < nx; ++j) {
				if (visx[j]) lx[j] -= tmp;
			}
			for (int j = 0; j < ny; ++j) {
				if (visy[j]) ly[j] += tmp;
				else slack[j] -= tmp;
			}
		}
	}
}
/*	for(int i=0;i<ny;++i){   输出 
		if(match[i]!=-1)
			ans+=G[match[i]][i];
	}*/

