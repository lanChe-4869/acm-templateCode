int head[N],cnt;
struct edge{
	int next,to,cap,flow;
	edge(){}
	edge(int next,int to,int cap,int flow):next(next),to(to),cap(cap),flow(flow){} 
}e[M];
void add(int u,int v,int cap,int flow){
	e[cnt]=edge(head[u],v,cap,0);
	head[u]=cnt++;
	e[cnt]=edge(head[v],u,0,0);
	head[v]=cnt++;
}
int n,m;
int d[N];
bool bfs(int st,int ed){
	memset(d,-1,sizeof d);
	d[st]=1;
	queue<int>que;
	que.push(st);
	while(!que.empty()){
		int u=que.front();que.pop();
		for(int i=head[u];~i;i=e[i].next){
			int v=e[i].to;
			if(d[v]==-1&&e[i].cap-e[i].flow>0){
				d[v]=d[u]+1;
				que.push(v);
			}
		}
	}
	return d[ed]>0;
}
int dfs(int x,int ed,int flow){
	if(x==ed) return flow;
	int tmp=flow;
	for(int i=head[x];~i;i=e[i].next){
		int v=e[i].to;
		if(d[v]==d[x]+1&&e[i].cap-e[i].flow>0){
			int t=dfs(v,ed,min(flow,e[i].cap-e[i].flow));
			e[i].flow+=t;
			e[i^1].flow-=t;
			flow-=t;
		}
	}
	return tmp-flow;
}
int dinic(int st,int ed){
	int sum=0;
	while(bfs(st,ed)){
		sum+=dfs(st,ed,inf);
	}
	return sum;
}
