
//#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <bitset>
#include <set>
#include <cstdlib>
#include <string>
#include <function> 
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
template<typename T>
inline void rd(T &x)
{
    int tmp = 1;char c = getchar();x = 0;
    while (c > '9' || c < '0'){if (c == '-')tmp = -1;c = getchar();}
    while (c >= '0' && c <= '9'){x = x * 10 + c - '0';c = getchar();}
    x *= tmp;
}
#ifdef LOCAL
    FILE *_INPUT = freopen("input.txt", "r", stdin);
	FILE* _OUTPUT=freopen("output.txt", "w", stdout);
#endif

int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
}
