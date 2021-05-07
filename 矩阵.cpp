
//     01��������

const int N=505;
bitset<N<<1>a[N];
int n;
int Gauss_rev(int n){
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){//�ҵ�i�з�����л�����
            if(a[j][i]){
                swap(a[i],a[j]);
                break;
            }
        }
        if(!a[i][i]) return 0;//�޽�   ���ȵ�ʱ�� continue;
		else ++rank; 
        for(int j=1;j<=n;j++){//������
            if(a[j][i]&&j!=i){
                a[j]^=a[i];
            }
        }
    }
    return rank;// ������ 
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
        a[i][i+n]=1;
    }
    if(!Gauss_rev(n)){
        puts("No Solution");
    }else{
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                printf("%d ",a[i][j+n]);
            }
            puts("");
        }
    }
    return 0;
}
----------------------------- 

//   ��ͨ��������
int a[N][N<<1];
int n;
int Gauss_rev(int n){
	int rank=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){//�ҵ�i�з�����л�����
            if(a[j][i]){
                swap(a[i],a[j]);
                break;
            }
        }
        if(!a[i][i]) return 0;//�޽�   ���ȵ�ʱ�� continue;
		else ++rank; 
        int tmp=fp(a[i][i],mod-2);//��Ԫ
        for(int j=i;j<=n*2;j++){//��ǰ��ÿһ�ж�����a[i][i]
            a[i][j]=1LL*a[i][j]*tmp%mod;
        }
        for(int j=1;j<=n;j++){//������
            if(j!=i){
                tmp=a[j][i];
                for(int k=i;k<=n*2;k++){
                    a[j][k]=(a[j][k]-1LL*tmp*a[i][k]%mod+mod)%mod;
                }
            }
        }
    }
    return rank; //������ 
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
        a[i][i+n]=1;
    }
    if(!Gauss_rev(n)){
        puts("No Solution");
    }else{
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                printf("%d ",a[i][j+n]);
            }
            puts("");
        }
    }
    return 0;
}


