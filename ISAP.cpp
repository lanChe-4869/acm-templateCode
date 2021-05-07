struct Edge
{
    int next,to,cap,flow;
}edge[M];
int cnt,head[N];
void addedge(int u,int v,int cap,int rw=0)
{
	edge[cnt].to=v; edge[cnt].cap=cap; edge[cnt].flow=0;
	edge[cnt].next=head[u]; head[u]=cnt++;
	edge[cnt].to=u; edge[cnt].cap=rw; edge[cnt].flow=0;
	edge[cnt].next=head[v]; head[v]=cnt++;
}
int dep[N],gap[N],cur[N];
void bfs(int st,int ed){
	memset(dep,-1,sizeof dep); memset(gap,0,sizeof gap);
	dep[ed]=0;gap[0]=1;
	queue<int>que; que.push(ed);
	while(!que.empty()){
		int u=que.front();que.pop();
		for(int i=head[u];~i;i=edge[i].next){
			int v=edge[i].to;
			if(dep[v]!=-1) continue;
			que.push(v);
			dep[v]=dep[u]+1;
			++gap[dep[v]];
		}
	}
}
int stk[N];
int sap(int st,int ed,int n){
	bfs(st,ed);
	memcpy(cur,head,sizeof head);
	int u=st,ans=0,top=0;
	while(dep[st]<n){
		if(u==ed){
			int Min=inf,posv;
			for(int i=0;i<top;++i){
				if(Min>edge[stk[i]].cap-edge[stk[i]].flow){
					Min=edge[stk[i]].cap-edge[stk[i]].flow;
					posv=i;
				}
			}
			for(int i=0;i<top;++i){
				edge[stk[i]].flow+=Min;
				edge[stk[i]^1].flow-=Min;
			}
			ans+=Min;
			top=posv;
			u=edge[stk[top]^1].to;
			continue; 
		}
		bool flag=false;
		int v;
		for(int i=cur[u];~i;i=edge[i].next){
			v=edge[i].to;
			if(edge[i].cap-edge[i].flow>0&&dep[v]+1==dep[u]){
				flag=1;
				cur[u]=i;
				break;
			}
		}
		if(flag){
			stk[top++]=cur[u];
			u=v;
			continue;
		}
		int Min=n;
		for(int i=head[u];~i;i=edge[i].next){
			if(edge[i].cap-edge[i].flow>0&&dep[edge[i].to]<Min){
				Min=dep[edge[i].to];
				cur[u]=i;
			}
		}
		--gap[dep[u]];
		if(!gap[dep[u]]) return ans;
		dep[u]=Min+1;
		++gap[dep[u]];
		if(u!=st) u=edge[stk[--top]^1].to;
	}
	return ans;
}
