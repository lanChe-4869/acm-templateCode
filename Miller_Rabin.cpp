#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
template<typename T>
inline void rd(T& x)
{
	int tmp = 1; char c = getchar(); x = 0;
	while (c > '9' || c < '0') { if (c == '-')tmp = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	x *= tmp;
}
const int N = 1e6 + 10;
const int S = 8;
ll mult_mod(ll a, ll b, ll c) {
	a %= c; b %= c;
	ll ret = 0, tmp = a;
	while (b) {
		if (b & 1) {
			ret += tmp;
			if (ret > c) ret -= c;
		}
		tmp <<= 1;
		if (tmp > c) tmp -= c;
		b >>= 1;
	}
	return ret;
}

ll pow_mod(ll a, ll n, ll mod) {
	ll ret = 1, tmp = a % mod;
	while (n) {
		if (n & 1) ret = mult_mod(ret, tmp, mod);
		tmp = mult_mod(tmp, tmp, mod);
		n >>= 1;
	}
	return ret;
}

bool check(ll a, ll n, ll x, ll t) {
	ll ret = pow_mod(a, x, n);
	ll last = ret;
	for (int i = 1; i <= t; ++i) {
		ret = mult_mod(ret, ret, n);
		if (ret == 1 && last != 1 && last != n - 1) return true;
		last = ret;
	}
	if (ret != 1) return true;
	return false;
}

bool Miller_Rabin(ll n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if ((n & 1) == 0) return false;
	ll x = n - 1, t = 0;
	while ((x & 1) == 0) {
		x >>= 1;
		++t;
	}
	srand(time(NULL));
	for (int i = 0; i < S; ++i) {
		ll a = rand() % (n - 1) + 1;
		if (check(a, n, x, t)) return false;
	}
	return true;
}

//------------ pollard_rho 算法进行质因素分解

ll factor[105]; int tol;
ll gcd(ll a, ll b) {
	ll t;
	while (b) {
		t = a;
		a = b;
		b = t % a;
	}
	if (a >= 0) return a;
	else return -a;
}

ll pollard_rho(ll x, ll c) {
	ll i = 1, k = 2;
	srand(time(NULL));
	ll x0 = rand() % (x - 1) + 1;
	ll y = x0;
	while (1) {
		++i;
		x0 = (mult_mod(x0, x0, x) + c) % x;
		ll d = gcd(y - x0, x);
		if (d != 1 && d != x) return d;
		if (y == x0) return x;
		if (i == k) {
			y = x0;
			k += k;
		}
	}
}

void findfac(ll n, int k) {
	if (n == 1) return;
	if (Miller_Rabin(n)) {
		factor[tol++] = n;
		return;
	}
	ll p = n;
	int c = k;
	while (p >= n) p = pollard_rho(p, c--);
	findfac(p, k);
	findfac(n / p, k);
}
int main() {
	ll n; rd(n);
	if (Miller_Rabin(n)) printf("prime");
	else {
			tol = 0;
			findfac(n, 107);
			ll ans = factor[0];
			for (int i = 1; i < tol; ++i) ans = min(ans, factor[i]);
			printf("%lld\n", ans);
		} 
}
