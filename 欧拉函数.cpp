const int MAXN
int cnt=0;
int prime[MAXN],phi[MAXN];
bool isPrime[MAXN];
void get_phi(const int MAX=MAXN-5){
	cnt=0;
	memset(isPrime,0,sizeof isPrime);
	for(int i=2;i<MAXN;++i){
		if(!isPrime[i]){
			prime[cnt++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<cnt&&prime[j]*i<MAX;++j){
			isPrime[prime[j]*i]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else{
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
			}
		}
	}
}
------------------------------------------------------------ 
ll eular(ll n)
{
    ll ans = n;
    for(int i=0;prime[i]*prime[i]<=n&&i<cnt;++i)
    {
        if(n%prime[i]== 0)
        {
            ans = ans/prime[i]*(prime[i]-1);
            while(n%prime[i] == 0)
                n/=prime[i];
        }
    }
    if(n > 1) ans = ans/n*(n-1);
    return ans;
}
----------------------------------------------------------- 
ll eular(ll n)
{
    ll ans = n;
    for(int i=2;i*i<=n;++i)
    {
        if(n%i== 0)
        {
            ans = ans/i*(i-1);
            while(n%i == 0)
                n/=i;
        }
    }
    if(n > 1) ans = ans/n*(n-1);
    return ans;
}
---------------------------------------------------------
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
