const int MAXN
bool  isprime[MAXN]={0};
int prime[MAXN];
void init(const int MAX=MAXN-5){
	int cnt=0;
	for(int i=2;i<MAX;++i){
		if(!isprime[i]){
			prime[++cnt]=i;
		}
		for(int j=1;j<=cnt&&prime[j]*i<MAX;++j){
			isprime[prime[j]*i]=1;
			if(i%prime[j]==0) break; 
		}
	}
}
