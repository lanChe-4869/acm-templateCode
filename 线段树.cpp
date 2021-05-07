const int N = 
const int M = 
int a[N];
struct node {
	int Max, Min;
	ll num;
}tree[N << 2];
int lazy[N << 2];
inline void pushUp(const int &rt) {
	tree[rt].num = tree[rt << 1].num + tree[rt << 1 | 1].num;
	tree[rt].Max = tree[rt << 1].Max > tree[rt << 1 | 1].Max ? tree[rt << 1].Max : tree[rt << 1 | 1].Max;
	tree[rt].Min = tree[rt << 1].Min < tree[rt << 1 | 1].Min ? tree[rt << 1].Min : tree[rt << 1 | 1].Min;
}
inline void pushDown(const int &rt,const int &l,const int &r) {
	if (lazy[rt]) {
		int mid = l + r >> 1;
		lazy[rt << 1] = lazy[rt];
		tree[rt << 1].Max = tree[rt << 1].Min = lazy[rt];
		tree[rt << 1].num = 1LL * (mid - l + 1) * lazy[rt]; 
		
		lazy[rt << 1 | 1] = lazy[rt];
		tree[rt << 1 | 1].Max = tree[rt << 1 | 1].Min = lazy[rt];
		tree[rt << 1 | 1].num = 1LL * lazy[rt] * (r - mid);

		lazy[rt] = 0;
	}
}

void build(const int &rt,const int &l,const int &r) {
	lazy[rt] = 0;
	if (l == r) {
		tree[rt].Max = tree[rt].Min = tree[rt].num = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushUp(rt);
}

void update(int rt,const int& l,const int& r,const int& ql,const int& qr,const int& x) {
	if (r<ql || l>qr || tree[rt].Min >= x) return;
	if (ql <= l && r <= qr) {
		if (x >= tree[rt].Max) {
			tree[rt].Min = tree[rt].Max = x;
			tree[rt].num = 1LL * (r - l + 1) * x;
			lazy[rt] = x;
			return;
		}
		tree[rt].Min = tree[rt].Min > x ? tree[rt].Min : x;
		if (l == r) return;
	}
	pushDown(rt, l, r);
	int mid = l + r >> 1;
	if (ql <= mid)	update(rt << 1, l, mid, ql, qr, x);
	if (qr > mid)	update(rt << 1 | 1, mid + 1, r, ql, qr, x);
	pushUp(rt);
}

int query(int rt,const int& l,const int& r,const int& ql,const int& qr, int& sum) {
	if (l > qr || r < ql || tree[rt].Min>sum) return 0;
	if (ql <= l && r <= qr && tree[rt].num <= sum) {
		sum -= tree[rt].num;
		return r - l + 1;
	}
	pushDown(rt, l, r);
	int mid = l + r >> 1;
	if (mid >= qr) return query(rt << 1, l, mid, ql, qr, sum);
	else if (mid < ql) return query(rt << 1 | 1, mid + 1, r, ql, qr, sum);
	else return query(rt << 1, l, mid, ql, qr, sum) + query(rt << 1 | 1, mid + 1, r, ql, qr, sum);
}
