


const int N=1e5+10;
int n,m,sg[N],s[N];
void getSG(){
	memset(sg,0,sizeof sg);
	for(int i=1;i<=n;++i){
		memset(s,0,sizeof s);
		for(int j=1;j<=m&&(/*取完后的石子>=0*/i-j>=0);++j){
			s[sg[i-j]]=1;
		}
		for(int j=0;;++j){
			if(!s[j]){
				sg[i]=j;
				break;
			}
		}
	}
}


//求二维 NIM 积 
#define Resolve(i, x) for (int u = (x), i = 0; (1ll << i) <= u; ++ i) if (u >> i & 1)
ll f(ll x, ll y);
ll sg[65][65];  //代表 2^64为上限 

ll g(int x, int y) {
	if (!x || !y) return 1LL << (x | y);
	if (~sg[x][y]) return sg[x][y];
	ll res = 1;
	Resolve(i, x ^ y) res <<= (1 << i);
	Resolve(i, x & y) res = f(res, 3LL << ((1 << i) - 1));
	return sg[x][y] = res;
}

ll f(ll x, ll y) {
	if (!x || !y) return x | y;
	if (x == 1 || y == 1) return max(x, y);
	ll res = 0;
	Resolve(i, x) Resolve(j, y) res ^= g(i, j);
	return res;
}
