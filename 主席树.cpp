#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int cnt = 0;        //用cnt标记可以使用的新结点
int a[N], b[N], root[N];
//a[]是原数组,b[]是排序后数组，root[i]记录第i棵线段树的根节点编号

struct Tree{             //定义结点
    int L, R, cnt;  //L左儿子, R右儿子，cnt是结点i的个数（即图中圆圈内的数字）
    ll sum;         //sum 是这颗子树的权值和
    Tree() {
        L = R = cnt = sum = 0;
    }
}tree[N << 5];     //  <<4是乘16倍，不够用   

int update(int pre, int pl, int pr, int x) {   //建一棵只有logn个结点的新线段树
    int rt = ++cnt;          //新的结点，下面动态开点
    tree[rt].L = tree[pre].L;//该结点的左右儿子初始化为前一棵树相同位置结点的左右儿子
    tree[rt].R = tree[pre].R;
    tree[rt].cnt = tree[pre].cnt + 1;  //插了1个数，在前一棵树的相同结点加1
    tree[rt].sum = tree[pre].sum + b[x];
    int mid = (pl + pr) >> 1;
    if (pl < pr) {           //从根结点往下建logn个结点
        if (x <= mid)       //x出现在左子树，修改左子树 
            tree[rt].L = update(tree[pre].L, pl, mid, x);
        else                //x出现在右子树，修改右子树
            tree[rt].R = update(tree[pre].R, mid + 1, pr, x);
    }
    return rt;              //返回当前分配使用的新结点的编号
}
ll query(int pre, int now, int pl, int pr, int k) {    //查询区间[pre,now] 前k大的和
    if (pl == pr) return 1LL * b[pl] * k;  //到达叶子结点，找到第k小，pl是节点编号，答案是b[pl]，出现了k次，贡献 b[pl]*k
    int x = tree[tree[now].R].cnt - tree[tree[pre].R].cnt;   //线段树相减
    int mid = (pl + pr) >> 1;
     if (x >= k)     //左儿子数字大于等于k时，说明第k小的数字在左子树
        return query(tree[pre].R, tree[now].R, mid + 1, pr, k);
    else            //否则在右子树找第k-x小的数字 
        return query(tree[pre].L, tree[now].L, pl, mid, k - x) + tree[tree[now].R].sum - tree[tree[pre].R].sum;
}
int main() {
#ifdef _DEBUG
    FILE* _INPUT = freopen("input.txt", "r", stdin);
    //	FILE* _OUTPUT = freopen("output.txt", "w", stdout);
#endif
    int T; scanf("%d", &T);
    while (T--) {
        cnt = 0;
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        sort(b + 1, b + 1 + n);    //对b排序
        int sz = unique(b + 1, b + 1 + n) - b - 1; //sz等于b数组中不重复的数字的个数
        //root[0] = buildtree(1, sz);   //初始化一棵包含sz个元素的空树，实际上无必要
        for (int i = 1; i <= n; i++) {     //建n棵线段树
            int x = lower_bound(b + 1, b + 1 + sz, a[i]) - b;
            //找等于a[i]的b[x]。x是离散化后a[i]对应的值
            root[i] = update(root[i - 1], 1, sz, x);
            //建第i棵线段树，root[i]是第i棵线段树的根结点
        }
        int m; scanf("%d", &m);
        while (m--) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            ll ans = query(root[l - 1], root[r], 1, sz, k);
            //第y棵线段树减第x-1棵线段树，就是区间[x,y]的线段树
            printf("%lld\n", ans);
        }
    }
    return 0;
}
