int n;
const int mod;
void init(){
	inv[1]=1;
    for(int i = 2;i <= n;i++)
    {
        inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    } 
} 
