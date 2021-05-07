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

//队列多重背包
for(int i=1;i<=n;i++)//枚举物品种类 
{
    cin>>c[i]>>w[i]>>num[i];//c,w,num分别对应 体积,价值,个数 
    if(V/c[i] <num[i]) num[i]=V/c[i];//求lim
    for(int mo=0;mo<c[i];mo++)//枚举余数 
    {
        head=tail=0;//队列初始化 
        for(int k=0;k<=(V-mo)/c[i];k++) 
        {
            int x=k;
            int y=f[k*c[i]+mo]-k*w[i];
            while(head<tail && que[head].pos<k-num)head++;//限制长度
            while(head<tail && que[tail-1].value<=y)tail--;
            que[tail].value=y,que[tail].pos=x;
            tail++;
            f[k*c[i]+mo]=que[head].value+k*w[i];
            //加上k*w[i]的原因:
            //我们的单调队列维护的是前i-1种的状态最大值.
            //因此这里加上k*w[i].
        }
    }
} 
