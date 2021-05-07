int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	int ans=exgcd(b,a%b,x,y);
	int tmp=y;
	y=x-(a/b)*y;
	x=tmp;
	return ans;
}
