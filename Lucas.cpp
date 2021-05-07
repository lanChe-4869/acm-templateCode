ll Lucas(ll n,ll m,ll p)
{
    ll ans=1;
    while(n&&m&&ans)
    {
        ans=(ans*Comb(n%p,m%p,p))%p;   //²ð·Ö+µÝ¹é
        n/=p;
        m/=p;
    }
    return ans;
}
