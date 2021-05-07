#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=1e4+10;
int n,cnt,u,v;
int head[N],fa[N];
bool vis[N],root[N];
struct node{
	int to,next;
}a[N<<1];
int get (int x){
	if(x==fa[x])
		return x;
	return fa[x]=get(fa[x]);
}
void add(int x,int y){
	a[cnt].to=y;
	a[cnt].next=head[x];
	head[x]=cnt++;
}
void lca(int x){
	for(int i=head[x];i!=-1;i=a[i].next){
		lca(a[i].to);
		int fx=get(x),fy=get(a[i].to);
		if(fx!=fy)
			fa[get(fy)]=get(fx);
		vis[a[i].to]=true;
	}
	if(x==u&&vis[v]){
		printf("%d\n",get(v));
		return;
	}
	if(x==v&&vis[u]){
		printf("%d\n",get(u));
		return;
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		memset(a,0,sizeof a);
		memset(head,-1,sizeof head);
		memset(vis,false,sizeof vis);
		memset(root,true,sizeof root);
		cnt=0;
		scanf("%d",&n);
		for(int i=1;i<n;++i){
			scanf("%d %d",&u,&v);
			add(u,v);
			root[v]=false;
			fa[i]=i;
		}
		fa[n]=n;
		scanf("%d %d",&u,&v);
		for(int i=1;i<=n;++i){
			if(root[i]){
				lca(i);
				break;
			}
		}
	}
	return 0;
}
