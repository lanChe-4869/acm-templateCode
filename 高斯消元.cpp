


//  高斯消元  异或和版 
bitset<202>a[202];
int gauss(int n) {
	int res = 0;
	for (int i = 1, p = 1; i <= n; i++) {
		int m = p;
		if (!a[m][i]) {
			for (int j = p + 1; j <= n; j++) {
				if (a[j][i]) {
					m = j;
					break;
				}
			}
		}
		if (!a[m][i]) {
			continue;
		}
		if (p != m)swap(a[p], a[m]);
		for (int j = p + 1; j <= n; j++) {
			if (a[j][i]) {
				a[j] ^= a[p];
			}
		}
		++res;
		p++;
	}
	return res;
}
