
//二分图匹配优化版 
int matchx[N],matchy[N],dx[N],dy[N];
bool vis[N];
bool bfs(){
	memset(dx,0,sizeof dx);
	memset(dy,0,sizeof dy);
	queue<int>que;
	for(int i=1;i<=n;++i){
		if(matchx[i]==-1) que.push(i);
	}
	bool ok=false;
	while(!que.empty()){
		int x=que.front();que.pop();
		for(int i=head[x];~i;i=e[i].next){
			int v=e[i].to;
			if(!dy[v]){
				dy[v]=dx[x]+1;
				if(matchy[v]==-1) ok=true;
				else{
					dx[matchy[v]]=dy[v]+1;
					que.push(matchy[v]);
				}
			}
		}
	}
	return ok;
}
bool dfs(int x){
	for(int i=head[x];~i;i=e[i].next){
		int v=e[i].to;
		if(dy[v]==dx[x]+1){
			dy[v]=0;
			if(matchy[v]==-1||dfs(matchy[v])){
				matchy[v]=x;
				matchx[x]=v;
				return true;
			}
		}
	}
	return false;
}
int solve(){
	memset(matchx,-1,sizeof matchx);
	memset(matchy,-1,sizeof matchy);
	int ans=0;
	while(bfs()){
		for(int i=1;i<=n;++i){
			if(matchx[i]==-1&&dfs(i)) ++ans;
		}
	}
	return ans;
}
