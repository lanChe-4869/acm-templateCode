

int n, m;
const double pi = acos(-1.0);
struct complexx {
	double x, y;
	complexx(double x = 0, double y = 0) :x(x), y(y) {}
	complexx friend operator + (complexx a, complexx b) { return complexx(a.x + b.x, a.y + b.y); }
	complexx friend operator - (complexx a, complexx b) { return complexx(a.x - b.x, a.y - b.y); }
	complexx friend operator * (complexx a, complexx b) { return complexx(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y); }
}a[N], b[N];
int rev[N], sum[N];
void fft(complexx y[], int len, int on) {//on为1或者-1,-1的时候表示逆变换
	for (int i = 0; i < len; i++) {
		if (i < rev[i]) swap(y[i], y[rev[i]]);
	}
	for (int h = 2; h <= len; h <<= 1) {
		complexx wn(cos(-on * 2 * pi / h), sin(-on * 2 * pi / h));
		for (int j = 0; j < len; j += h) {
			complexx w(1, 0);
			for (int k = j; k < j + h / 2; k++) {
				complexx u = y[k];
				complexx t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if (on == -1) {
		for (int i = 0; i < len; i++) {
			y[i].x /= len;
		}
	}
}
int main() {
#ifdef _DEBUG
	FILE* _INPUT = freopen("input.txt", "r", stdin);
	//	FILE* _OUTPUT = freopen("output.txt", "w", stdout);
#endif // !_DEBUG
	int cas = 0, T = 1;
	//	rd(T);
	while (T--) {
//	while (~scanf("%d", &n)) {
		int m1 = 0, m2 = 0;
		rd(n);
		for (int i = 1; i <= n; ++i) {
			int x; rd(x);  //x为指数
			a[x].x += 1;
			m1 = max(m1, x);
		}
		rd(m);
		for (int i = 1; i <= m; ++i) {
			int x; rd(x);
			b[x].x += 1;
			m2 = max(m2, x);
		}
		int len = 1, l = 0;
		for (; len <= m1 + m2; len <<= 1, l++);  // len<=两个多项式的最大指数和
		for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));//rev[i]位将i按二进制后的值
		fft(a, len, 1); //将 a和b 多项式转换成点集
		fft(b, len, 1);
		for (int i = 0; i < len; i++)
			a[i] = a[i] * b[i];  //转换成点集后直接相乘
		fft(a, len, -1);//从点集转换成多项式
		for (int i = 0; i <= len; ++i) sum[i] = (int)(a[i].x + 0.5); //记录在指数为i下对应乘法运算后的系数，需要四舍五入
	}
	return 0;
}
