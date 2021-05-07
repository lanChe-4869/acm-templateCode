
// 
const int MAXN=
const int N=
int phi[N],mu[N],prime[MAXN],cnt;
bool isprime[MAXN]={0};
void pre(int n=MAXN-5){
    phi[1] = mu[1] = 1;
    for(int i=2;i<=n;++i){
        if(!isprime[i]){
            prime[++cnt] = i;
            mu[i] = -1;phi[i] = i-1;
        }
        for(int j = 1;j <= cnt && i*prime[j] <= n;++j){
            isprime[i*prime[j]] = true;
            if(i%prime[j]){
                phi[i*prime[j]] = phi[i]*phi[prime[j]];
                mu[i*prime[j]] = -mu[i];
            }
            else{
                phi[i*prime[j]] = phi[i]*prime[j];
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
}
