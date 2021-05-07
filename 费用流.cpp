
const int N 
const int M
const int inf=0x3f3f3f3f;
int head[N],cnt;
struct edge{
	int to,cap,cost,next;
	edge(){}
	edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}e[M]; 
void add(int u,int v,int cap,int w){
	e[cnt]=edge(v,cap,w,head[u]);
	head[u]=cnt++;
	e[cnt]=edge(u,0,-w,head[v]);
	head[v]=cnt++;
}
int n,m;
bool vis[N];
int dis[N],pre[N];
bool spfa(int s,int t){
	memset(vis,false,sizeof vis);
	memset(dis,inf,sizeof dis);
	memset(pre,-1,sizeof pre);
	queue<int>que;
	dis[s]=0;
	que.push(s);
	vis[s]=1;
	while(!que.empty()){
		int u=que.front();
		que.pop();
		vis[u]=false;
		for(int i=head[u];~i;i=e[i].next){
			int v=e[i].to;
			if(e[i].cap>0&&dis[v]>dis[u]+e[i].cost){
				dis[v]=dis[u]+e[i].cost;
				pre[v]=i;
				if(!vis[v]){
					vis[v]=1;
					que.push(v);
				}
			}
		}
	}
	return dis[t]!=inf;
}
int mincost(int s,int t){
	int mincost=0;
	while(spfa(s,t)){
		int tmp=inf;
		for(int v=t;v!=s;v=e[pre[v]^1].to){
			tmp=min(tmp,e[pre[v]].cap);
		}
		for(int v=t;v!=s;v=e[pre[v]^1].to){
			e[pre[v]].cap-=tmp;
			e[pre[v]^1].cap+=tmp;
		}
		mincost+=dis[t]*tmp;
	}
	return mincost;
}
