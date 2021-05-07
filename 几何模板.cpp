
const double pi=acos(-1);
const double eps=
int sgn(double x){//一个数是否等于0 
	if(fabs(x)<eps) return 0;
	return x<0?-1:1; 
}
int Dcmp(double x,double y){//比较两个数的大小 
	if(fabs(x-y)<eps) return 0;
	return x<y?-1:1;
}
struct Point{
	double x,y;
	Point(){}
	Point(double x, double y):x(x),y(y){}
	Point operator+(const Point &B){ return Point(x+B.x,y+B.y);}
	Point operator-(const Point &B){ return Point(x-B.x,y-B.y);}
	Point operator*(double k){ return Point(x*k,y*k);}
	Point operator/(double k){ return Point(x/k,y/k);}
	bool operator ==(const Point &B){ return sgn(x-B.x)==0&&sgn(y-B.y)==0;}
	bool operator <(const Point &B){ return sgn(x-B.x)<0||(sgn(x-B.x)==0&&sgn(y-B.y)<0);}
};
typedef Point Vector;//向量 
double Dot(Vector A,Vector B){ return A.x*B.x+A.y*B.y;}//点积 
double Cross(Vector A,Vector B){ return A.x*B.y-A.y*B.x;}//叉积
double Len(Vector A){ return sqrt(Dot(A,A));}//求向量的长度 
double Angle(Vector A,Vector B){ return acos(Dot(A,B)/Len(A)/Len(B));} //求两向量之间的夹角
double Distance(Point A,Point B){ return hypot(A.x-B.x,A.y-B.y);} //求两点之间的距离
bool Parallel(Vector A,Vector B){ return sgn(cross(A,B))==0;} //判断两向量是否平行
Vector Rotate(Vector A,double rad){ return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));}


---------//直线
struct Line{
	Point p1,p2;
	Line(){}
	Line(Point p1,Point p2):p1(p1),p2(p2){}
	Line(Point p1,double angle){  //点斜式 
		p1=p;
		if(sgn(angle-pi/2)==0){ p2=(p1+Point(0,1));}
		else{ p2=(p1+Point(1,tan(angle)));}
	} 
	Line(double a,double b,double c){  //ax+by+c=0
		if(sgn(a)==0){ p1=Point(0,-c/b); p2=Point(1,-c/b);}
		else if(sgn(b)==0){ p1=Point(-c/a,0); p2=Point(-c/a,1);}
		else { p1=Point(0,-c/b); p2=Point(1,(-c-a)/b);}
	} 
}; 
int Point_line_relation(Point p,Line v){ //判断点与直线的关系 
	int c=sgn(Cross(p-v.p1,v.p2-v.p1));
	if(c<0) return 1; //p在直线的左边 
	if(c>0) return 2; //p在直线的右边 
	return 0;  //p在直线上 
}
bool Line_relation(Line v1,Line v2){ //判断两直线的关系 
	if(sgn(Cross(v1.p2-v1.p1,v2.p2-v2.p1))==0){
		if(Point_line_relation(v1.p1,v2)==0) return 1; //重合 
		else return 0; //平行 
	}
	return 2; //相交 
} 
bool Point_on_seg(Point p,Line v){ //判断点是否在该线段上 
	return sgn(Cross(p-v.p1,v.p2-v.p1))==0&&sgn(Dot(p-v.p1,p-v.p2))<=0;
}
bool Cross_seg(Point a,Point b,Point c,Point d){//判断两线段是否相交 
	double c1=Cross(b-a,c-a),c2=Cross(b-a,d-a);
	double d1=Cross(d-c,a-c),d2=Cross(d-c,b-c);
	return sgn(c1)*sgn(c2)<=0&&sgn(d1)*sgn(d2)<=0;//若线段的端点在线段上也算，需要 <= 
}
Point Cross_point(Point a,Point b,Point c,Point d){  //求两线段的交点 
	double s1=Cross(b-a,c-a);
	double s2=Cross(b-a,d-a);
	return Point(c.x*s2-d.x*s1,c.y*s2-d.y*s1)/(s2-s1);
}


---------//多边形
int check(Point pt,Point *p,int n){  //判断点与多边形的关系 
	for(int i=0;i<n;++i){
		if(p[i]==pt) return 3;   //3表示点pt在多边形的顶点上 
	}
	for(int i=0;i<n;++i){
		Line v=Line(p[i],p[(i+1)%n]);
		if(Point_on_seg(pt,v)) return 2; //2表示点在多边形的边上 
	}
	int num=0;
	for(int i=0;i<n;++i){
		int j=(i+1)%n;
		int c=sgn(Cross(pt-p[j],p[i]-p[j]));
		int u=sgn(p[i].y-pt.y),v=sgn(p[j].y-pt.y);
		if(c>0&&u<0&&v>=0) ++num;
		if(c<0&&u>=0&&v<0) --num;
	}	
	return num!=0;  //1表示点在内部，0表示点在外部 
} 
double Polygon_area(Point *p,int n){// 求多边形的面积 
	double area=0;
	for(int i=0;i<n;++i){
		area+=Cross(p[i],p[(i+1)%n]);  //将分割点放在原点来理解 
	}
	return area/2;  //面积有正负 
}
Point Polygon_center(Point *p,int n){ //求多边形的重心 
	Point ans(0,0);
	double tmp=Polygon_area(p,n);
	if(sgn(tmp)==0) return ans;
	for(int i=0;i<n;++i){
		ans=ans+(p[i]+p[(i+1)%n])*Cross(p[i],p[(i+1)%n]);
	}
	return ans/tmp/6;  //包括面积的 /2 以及求重心的 /3  
}


------//凸包
int Andrew(Point *p,int n,Point *q){//p是原图，q是凸包图 
	sort(p,p+n,[](const Point &a,const Point &b){
		if(a.x==b.x) return a.y<b.y;
		return a.x<b.x;
	});
	n=unique(p,p+n)-p;
	int num=0; //凸包的点数 
	for(int i=0;i<n;++i){
		while(num>1&&sgn(Cross(q[num-1]-q[num-2],p[i]-q[num-2]))<=0) --num;
		q[num++]=p[i];
	}
	int tmp=num;
	for(int i=n-2;i>=0;--i){
		while(num>tmp&&sgn(Cross(q[num-1]-q[num-2],p[i]-q[num-2]))<=0) --num;
		q[num++]=p[i];
	}
	if(n>1) --num;
	return num;
} 

----//分治法求最近点对
Point p[N],tmp[N];
double Clost_Pair(int l,int r){
	double dis=inf;
	if(l==r) return dis;
	if(l+1==r) return Distance(p[l],p[r]);
	int mid=l+r>>1;
	double d1=Clost_Pair(l,mid);
	double d2=Clost_Pair(mid+1,r);
	dis=min(d1,d2);
	int cnt=0;
	for(int i=l;i<=r;++i){
		if(fabs(p[mid].x-p[i].x)<=dis) tmp[cnt++]=p[i];
	} 
	sort(tmp,tmp+cnt,[](const Point &a,const Point &b){
		return a.y<b.y;
	});
	for(int i=0;i<cnt;++i){
		for(int j=i+1;j<cnt;++j){
			if(tmp[j].y-tmp[i].y>=dis) break;
			dis=min(dis,Distance(tmp[i],tmp[j]));
		}
	}
	return dis;
} 

--------//旋转卡壳
double rotate(Point p[],int n){
	double ans=0;
	Point v;
	int cur=1;
	for(int i=0;i<n;++i){
		v=p[i]-p[(i+1)%n];
		while(Cross(v,p[(cur+1)%n]-p[cur])<0) cur=(cur+1)%n; //寻找对踵点 
		ans=max(ans,max(Distance(p[i],p[cur]),Distance(p[(i+1)%n],p[(cur+1)%n])));
	}
	return ans;
} 


--------//圆
Point intersection(Point u1,Point u2,Point v1,Point v2){
	Point ret=u1;
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))/((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	ret.x+=(u2.x-u1.x)*t;
	ret.y+=(u2.y-u1.y)*t;
	return ret;
} 

void intersection_line_circle(Point c,double r,Point l1,Point l2,Point &p1,Point &p2){
	Point p=c;
	double t;
	p.x+=l1.y-l2.y;
	p.y+=l2.x-l1.x;
	p=intersection(p,c,l1,l2);
	t=sqrt(r*r-distance(p,c)*distance(p,c)/distance(l1,l2));
	p1.x=p.x+(l2.x-l1.x)*t;
	p1.y=p.y+(l2.x-l1.x)*t;
	p2.x=p.x-(l2.x-l1.x)*t;
	p2.y=p.y-(l2.y-l1.y)*t;
} 

void intersection_circle_circle(Point c1,double r1,Point c2,double r2,Point &p1,Point &p2){
	Point u,v;
	double t;
	t=(l+(r1*r1-r2*r2)/distance(c1,c2)/distance(c1,c2))/2;
	u.x=c1.x+(c2.x-c1.x)*t;
	u.y=c1.y+(c2.y-c1.y)*t;
	v.x=u.x+c1.y-c2.y;
	v.y=u.y-c1.x+c2.x;
	intersection_line_circle(c1,r1,u,v,p1,p2);
}
