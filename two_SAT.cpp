#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int head[N],cnt;//Á´Ê½Ç°ÏòĞÇ 
bool vis[N<<1];
int top,stk[N<<1];
bool dfs(int u){
	if(vis[u^1]) return false;
	if(vis[u]) return true;
	vis[u]=true;
	stk[top++]=u;
	for(int i=head[u];~i;i=e[i].next){
		if(!dfs(e[i].to)) return false;
	}
	return true;
}
bool two_SAT(int n){
	memset(vis,false,sizeof vis);
	for(int i=0;i<n*2;i+=2){
		if(vis[i]||vis[i^1]) continue;
		top=0;
		if(!dfs(i)){
			while(top) vis[stk[--top]]=false;
			if(!dfs(i^1)) return false;
		}
	}
	return true;
}
void printAns(){
	for(int i=0;i<n*2;i+=2){
		if(vis[i]) printf("%d ",i);
		else printf("%d ",i^1);
	}
} 
