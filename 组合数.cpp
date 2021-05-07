
-----------------------------//组合数大量使用 
const int mod=;
ll fp(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
} 
const int N=1e5+10; 
ll fac[N],ifac[N];
ll C(int n,int k){
	ll ans=fac[n]*ifac[n-k]%mod*ifac[k]%mod;
	return ans;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=1e5;++i)	fac[i]=fac[i-1]*i%mod;
	ifac[N-10]=fp(fac[N-10],mod-2);
	for(int i=1e5-1;i>=0;--i) ifac[i]=(i+1)*ifac[i+1]%mod;
}
-----------------------------
//少量使用
const int mod=;
ll fp(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
} 
const int N=1e5+10;
ll C(int n,int k){
	ll tmp=fac[n-k]*fac[k]%mod;
	ll ans=fac[n]*fp(tmp,mod-2)%mod;
	return ans;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=1e5;++i)	fac[i]=fac[i-1]*i%mod;
}
-----------------------------
//简单打表使用 
ll C[][];
void init(){
	C[0][0] = 1;
	for (int i = 1; i <= ; i++)
	{
		C[i][0] = 1;
		for (int j = 1; j <= ; j++)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j]; 
	}
} 
