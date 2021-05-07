vector<int>G[N];            //
int cnt,dfn[N],low[N],scc[N],top,stk[N],num;
void dfs(int x){
	stk[top++]=x;
	dfn[x]=low[x]=++num;
	int sz=G[x].size();
	for(int i=0;i<sz;++i){
		int v=G[x][i];
		if(!dfn[v]){
			dfs(v);
			low[x]=min(low[x],low[v]);
		}
		else if(!scc[v]) low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x]){
		++cnt;
		while(1){
			int v=stk[--top];
			scc[v]=cnt;
			if(x==v) break;
		}
	}
}
inline void tarjan(const int &n){
	memset(dfn,0,sizeof dfn);
	memset(scc,0,sizeof scc);
	memset(low,0,sizeof low);
	cnt=top=num=0;
	for(int i=1;i<=n;++i){
		if(!dfn[i])
			dfs(i);
		//tow_SAT  ÈçÏÂ
	//	if(!dfn[i<<1]) dfs(i<<1);
	//	if(!dfn[i<<1|1]) dfs(i<<1|1) 
	}
}
// Ëõµã 
//two-SAT
bool two_SAT(){
	for(int i=1;i<=n;++i){
		if(scc[i<<1]==scc[i<<1|1]) return false;
	}
	return true;
}
