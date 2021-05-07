


bool  isprime[MAXN]={0};
int prime[MAXN],cnt;
ll sum[MAXN];
void init(const int MAX=MAXN-5){
	cnt=0,sum[0]=0;
	for(int i=2;i<MAX;++i){
		if(!isprime[i]){
			prime[++cnt]=i;sum[cnt]=sum[cnt-1]+i;
		}
		for(int j=1;j<=cnt&&prime[j]*i<MAX;++j){
			isprime[prime[j]*i]=1;
		}
	}
}


ll G(ll n,int k){    //f(i)=[i是否为质数]i;
	if(n==0) return 0;
	while(1LL*prime[k]*prime[k]>n) --k;   //f(i)=prime_i;
	ll ans;
	if(n&1) ans=(1+n)/2*n-1;
	else ans=n/2*(1+n)-1;
	if(n<=1e5&&res[n][k]) return res[n][k];
	for(int i=1;i<=k;++i){
		ans-=prime[i]*(G(n/prime[i],i-1)-sum[i-1]);  //sum[i-1] 
	}
	if(n<=1e5) res[n][k]=ans;
	return ans;
}
