void zero_one_pack(int cost,int value){
	for(int i=volume;i>=cost;--i){
		dp[i]=min(dp[i],dp[i-cost]+value);
	}
}

void multi_pack(void){
	for(int k=1;tot;k*=2){
		zero_one_pack(k*cost,k*value);
		tot-=k;
		k=min(k,tot);
	}
}

void complete_pack(int cost,int value){
	for(int i=cost;i<=volume;++i){
		dp[i]=min(dp[i],dp[i-cost]+value);
	}
	return;
}

//���ж��ر���
for(int i=1;i<=n;i++)//ö����Ʒ���� 
{
    cin>>c[i]>>w[i]>>num[i];//c,w,num�ֱ��Ӧ ���,��ֵ,���� 
    if(V/c[i] <num[i]) num[i]=V/c[i];//��lim
    for(int mo=0;mo<c[i];mo++)//ö������ 
    {
        head=tail=0;//���г�ʼ�� 
        for(int k=0;k<=(V-mo)/c[i];k++) 
        {
            int x=k;
            int y=f[k*c[i]+mo]-k*w[i];
            while(head<tail && que[head].pos<k-num)head++;//���Ƴ���
            while(head<tail && que[tail-1].value<=y)tail--;
            que[tail].value=y,que[tail].pos=x;
            tail++;
            f[k*c[i]+mo]=que[head].value+k*w[i];
            //����k*w[i]��ԭ��:
            //���ǵĵ�������ά������ǰi-1�ֵ�״̬���ֵ.
            //����������k*w[i].
        }
    }
} 
