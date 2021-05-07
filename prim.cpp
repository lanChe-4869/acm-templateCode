const int M = 1e5 + 10;
const int N = 1e3 + 10;
const int inf = 0x3f3f3f3f;
int G[N][N],dis[N],pre[N],MST;
int n;
bool used[N][N],vis[N];
void prim(){
	memset(used,false,sizeof used);
	memset(vis,false,sizeof vis);
	for(int i=1;i<=n;++i) pre[i]=1,dis[i]=G[1][i];
	vis[1]=true;  MST=0;
	for(int i=1;i<=n;++i){
		int tmp=-1;
		for(int j=1;j<=n;++j){
			if(!vis[j]&&(tmp==-1||dis[j]<dis[tmp])) tmp=j;
		}
		if(tmp==-1) return;
		used[tmp][pre[tmp]]=used[pre[tmp]][tmp]=true;
		vis[tmp]=true;
		MST+=dis[tmp];
		for(int j=1;j<=n;++j){
			if(!vis[j]&&dis[j]>G[tmp][j]){
				dis[j]=G[tmp][j];
				pre[j]=tmp;
			}
		}
	}
}
------------------------------------------------------------------------------------------------ 
//次小生成树 ,prim大概模板 
double G[N][N], dis[N], MST;//G是图中两点 i,j之间的距离    dis是每次更新后的最短距离 
bool used[N][N];//检查这条边是否是最小生成树中的边 
int n, k;
int pre[N];//父节点 
bool vis[N];
void prim() {
	memset(head, -1, sizeof head); cnt0 = 0;   //链式前向星 
	for (int i = 0; i < n; ++i) dis[i] = G[0][i], pre[i] = 0, vis[i] = false;
	MST = 0;
	vis[0] = true;
	for (int i = 1; i < n; ++i) {
		int tmp = -1;
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && (tmp == -1 || dis[j] < dis[tmp])) tmp = j;
		}
		if(tmp == -1) return; 
		vis[tmp] = true;
		used[tmp][pre[tmp]] = used[pre[tmp]][tmp] = true;
		add(tmp, pre[tmp]); add(pre[tmp], tmp);  //链式前向星加边 
		MST += dis[tmp];
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && dis[j] > G[j][tmp]) {
				dis[j] = G[j][tmp];
				pre[j] = tmp;
			}
		}
	}
}

double len[N][N];//次小生成树求点i,j之间 次小长度 
double dfs(int root, int u, int fa) {
	double ans = inf;
	for (int i = head[u]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v != fa) {
			double tmp = dfs(root, v, u);
			ans = min(ans, tmp);
			len[u][v] = len[v][u] = min(len[u][v], tmp);
		}
	}
	if (root != fa) ans = min(ans, G[root][u]);
	return ans;
}
inline solve() {
	prim();
	for (int i = 0; i < n; ++i) dfs(i, i, -1); 
}
