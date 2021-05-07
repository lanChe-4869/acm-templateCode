#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int cnt = 0;        //��cnt��ǿ���ʹ�õ��½��
int a[N], b[N], root[N];
//a[]��ԭ����,b[]����������飬root[i]��¼��i���߶����ĸ��ڵ���

struct Tree{             //������
    int L, R, cnt;  //L�����, R�Ҷ��ӣ�cnt�ǽ��i�ĸ�������ͼ��ԲȦ�ڵ����֣�
    ll sum;         //sum �����������Ȩֵ��
    Tree() {
        L = R = cnt = sum = 0;
    }
}tree[N << 5];     //  <<4�ǳ�16����������   

int update(int pre, int pl, int pr, int x) {   //��һ��ֻ��logn���������߶���
    int rt = ++cnt;          //�µĽ�㣬���涯̬����
    tree[rt].L = tree[pre].L;//�ý������Ҷ��ӳ�ʼ��Ϊǰһ������ͬλ�ý������Ҷ���
    tree[rt].R = tree[pre].R;
    tree[rt].cnt = tree[pre].cnt + 1;  //����1��������ǰһ��������ͬ����1
    tree[rt].sum = tree[pre].sum + b[x];
    int mid = (pl + pr) >> 1;
    if (pl < pr) {           //�Ӹ�������½�logn�����
        if (x <= mid)       //x���������������޸������� 
            tree[rt].L = update(tree[pre].L, pl, mid, x);
        else                //x���������������޸�������
            tree[rt].R = update(tree[pre].R, mid + 1, pr, x);
    }
    return rt;              //���ص�ǰ����ʹ�õ��½��ı��
}
ll query(int pre, int now, int pl, int pr, int k) {    //��ѯ����[pre,now] ǰk��ĺ�
    if (pl == pr) return 1LL * b[pl] * k;  //����Ҷ�ӽ�㣬�ҵ���kС��pl�ǽڵ��ţ�����b[pl]��������k�Σ����� b[pl]*k
    int x = tree[tree[now].R].cnt - tree[tree[pre].R].cnt;   //�߶������
    int mid = (pl + pr) >> 1;
     if (x >= k)     //��������ִ��ڵ���kʱ��˵����kС��������������
        return query(tree[pre].R, tree[now].R, mid + 1, pr, k);
    else            //�������������ҵ�k-xС������ 
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
        sort(b + 1, b + 1 + n);    //��b����
        int sz = unique(b + 1, b + 1 + n) - b - 1; //sz����b�����в��ظ������ֵĸ���
        //root[0] = buildtree(1, sz);   //��ʼ��һ�ð���sz��Ԫ�صĿ�����ʵ�����ޱ�Ҫ
        for (int i = 1; i <= n; i++) {     //��n���߶���
            int x = lower_bound(b + 1, b + 1 + sz, a[i]) - b;
            //�ҵ���a[i]��b[x]��x����ɢ����a[i]��Ӧ��ֵ
            root[i] = update(root[i - 1], 1, sz, x);
            //����i���߶�����root[i]�ǵ�i���߶����ĸ����
        }
        int m; scanf("%d", &m);
        while (m--) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            ll ans = query(root[l - 1], root[r], 1, sz, k);
            //��y���߶�������x-1���߶�������������[x,y]���߶���
            printf("%lld\n", ans);
        }
    }
    return 0;
}
