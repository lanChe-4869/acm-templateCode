
//  ��ͨ��ĸ���� 
const int MAX=2e2+10;
int c1[MAX],c2[MAX];
void part(){
	for(int i=0;i<=MAX;++i){
		c1[i]=1;c2[i]=0;
	}
	for(int k=2;k<=MAX;++k){
		for(int i=0;i<=MAX;++i){
			for(int j=0;j+i<=MAX;j+=k){
				c2[i+j]+=c1[i];
			}
		}
		for(int i=0;i<=MAX;++i){
			c1[i]=c2[i];c2[i]=0;
		}
	}
}

//  ָ����ĸ���� 
const int MAX=2e2+10;
int num[MAX],n,m;   //ÿһ����Ʒ�ĸ��� 
double c1[MAX],c2[MAX];
double fac(int n) {
    double ans=1.0;
    for(int i=1; i<=n; i++)
        ans*=i;
    return ans;
}
void part(){
	for(int i=0;i<=num[1];++i)
		c1[i]=1.0/fac(i);
	for(int i=2;i<=n;++i){  //n����Ʒ�������� ,mΪ���ٸ���Ʒ���� 
		for(int j=0;j<=m;++j){
			for(int k=0;k<=num[i]&&j+k<=m;++k){
				c2[j+k]+=c1[j]/fac(k);
			}
		}
		for(int j=0;j<=m;++j){
			c1[j]=c2[j];c2[j]=0;
		}
	}
} 
