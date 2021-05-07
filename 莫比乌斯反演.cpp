
//œﬂ–‘…∏ 
const int MAXN=1e6+10;
const int MAX=1e6;
int prime[MAXN],cnt,mu[MAXN];
bool isprime[MAXN];
void pre_cal(){
	mu[1]=1;
	cnt=0;
	for(int i=2;i<=MAX+5;++i){
		if(!isprime[i]){
			prime[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=MAX;++j){
			isprime[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			else{
				mu[i*prime[j]]=-mu[i];
			}
		}
	}
}
