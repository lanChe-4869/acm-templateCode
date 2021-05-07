

#define lowbit(x)  ((x)&-(x))
int tree[N];
int n;
void add(int x,int d){
	while(x<=n){
		tree[x]+=d;
		x+=lowbit(x);
	}
}
int sum(int x){
	int ans=0;
	while(x>0){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
