ll Lucas(ll n,ll m,ll p)
{
    ll ans=1;
    while(n&&m&&ans)
    {
        ans=(ans*Comb(n%p,m%p,p))%p;   //���+�ݹ�
        n/=p;
        m/=p;
    }
    return ans;
}
