
//��һ�������������� 
const int N
int cnt,fac[N],num[N],prime[]={1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,7,83,89,91};
void dfs(int dep,ll ans=1){
	if(dep==n) // n��Ҫ���ж��ٸ��������������ܲ��� 
	{
		fac[++cnt]=ans;
		return;
	}
	for(int i=0;i<=num[dep];++i){
		dfs(dep+1,ans);
		ans*=prime[dep];
	}
}
void init(){
	memset(num,0,sizeof num);
	cnt=0;
}
------------------------------------------------------------
const int N
int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int n,best;//���ӵ�����Ϊn ,��ǰ����������Ϊbest 
ull ans;
void dfs(int dep,int limit,ull tmp,int num){
	if(dep>=16) return;
	if(num>best){
		best=num;
		ans=tmp;
	}
	else if(num==best&&ans>tmp){
		ans=tmp;
	}
	for(int i=1;i<=limit;++i){
		if(ans/p[dep]<tmp) return;
		dfs(dep+1,i,tmp*=p[dep],num*(i+1));
	}
}
void init(){
	ans=~0ULL;
	best=0;
	dfs(0,63,1,1);
	cout<<ans<<endl;
}
---------------------------------------------------------------

