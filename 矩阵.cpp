
//     01矩阵求逆

const int N=505;
bitset<N<<1>a[N];
int n;
int Gauss_rev(int n){
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){//找第i列非零的行换上来
            if(a[j][i]){
                swap(a[i],a[j]);
                break;
            }
        }
        if(!a[i][i]) return 0;//无解   求秩的时候 continue;
		else ++rank; 
        for(int j=1;j<=n;j++){//其他行
            if(a[j][i]&&j!=i){
                a[j]^=a[i];
            }
        }
    }
    return rank;// 返回秩 
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

//   普通矩阵求逆
int a[N][N<<1];
int n;
int Gauss_rev(int n){
	int rank=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){//找第i列非零的行换上来
            if(a[j][i]){
                swap(a[i],a[j]);
                break;
            }
        }
        if(!a[i][i]) return 0;//无解   求秩的时候 continue;
		else ++rank; 
        int tmp=fp(a[i][i],mod-2);//逆元
        for(int j=i;j<=n*2;j++){//当前行每一列都除以a[i][i]
            a[i][j]=1LL*a[i][j]*tmp%mod;
        }
        for(int j=1;j<=n;j++){//其他行
            if(j!=i){
                tmp=a[j][i];
                for(int k=i;k<=n*2;k++){
                    a[j][k]=(a[j][k]-1LL*tmp*a[i][k]%mod+mod)%mod;
                }
            }
        }
    }
    return rank; //返回秩 
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


