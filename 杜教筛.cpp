#include <bits/stdc++.h>
using namespace std;
const int N=5e6+10;
bool isprime[N];
int prime[N],cnt=0;
int phi[N],mu[N];//phi 为欧拉函数 
ll sum1[N],sum2[N];//sum1 求mu前缀和，sum2求欧拉函数前缀和 
void init(){
	phi[1]=mu[1]=1;
	for(int i=2;i<=N-10;++i){
		if(!isprime[i]){
			prime[++cnt]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&prime[j]*i<=N-10;++j){
			isprime[prime[j]*i]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;	
			}
			mu[i*prime[j]]=-mu[i];
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(int i=1;i<=N-10;++i){
		sum1[i]=sum1[i-1]+mu[i];
		sum2[i]=sum2[i-1]+phi[i];
	}
}
unordered_map<ll,ll>w1,w2;//w1为mu前缀和，w2为欧拉函数前缀和 
ll pre_phi(ll n){
	if(n<=N-10) return sum2[n];
	if(w2[n]) return w2[n];
	ll ans=(1+n)*n/2;
	for(ll l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=pre_phi(n/l)*(r-l+1);
	}
	return w2[n]=ans;
}
ll pre_mu(ll n){
	if(n<=N-10) return 	sum1[n];
	if(w1[n]) return w1[n];
	ll ans=1;
	for(ll l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=pre_mu(n/l)*(r-l+1);
	}
	return w1[n]=ans;
}


