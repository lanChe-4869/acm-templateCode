
const double pi=acos(-1);
const double eps=
int sgn(double x){//һ�����Ƿ����0 
	if(fabs(x)<eps) return 0;
	return x<0?-1:1; 
}
int Dcmp(double x,double y){//�Ƚ��������Ĵ�С 
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
typedef Point Vector;//���� 
double Dot(Vector A,Vector B){ return A.x*B.x+A.y*B.y;}//��� 
double Cross(Vector A,Vector B){ return A.x*B.y-A.y*B.x;}//���
double Len(Vector A){ return sqrt(Dot(A,A));}//�������ĳ��� 
double Angle(Vector A,Vector B){ return acos(Dot(A,B)/Len(A)/Len(B));} //��������֮��ļн�
double Distance(Point A,Point B){ return hypot(A.x-B.x,A.y-B.y);} //������֮��ľ���
bool Parallel(Vector A,Vector B){ return sgn(cross(A,B))==0;} //�ж��������Ƿ�ƽ��
Vector Rotate(Vector A,double rad){ return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));}


---------//ֱ��
struct Line{
	Point p1,p2;
	Line(){}
	Line(Point p1,Point p2):p1(p1),p2(p2){}
	Line(Point p1,double angle){  //��бʽ 
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
int Point_line_relation(Point p,Line v){ //�жϵ���ֱ�ߵĹ�ϵ 
	int c=sgn(Cross(p-v.p1,v.p2-v.p1));
	if(c<0) return 1; //p��ֱ�ߵ���� 
	if(c>0) return 2; //p��ֱ�ߵ��ұ� 
	return 0;  //p��ֱ���� 
}
bool Line_relation(Line v1,Line v2){ //�ж���ֱ�ߵĹ�ϵ 
	if(sgn(Cross(v1.p2-v1.p1,v2.p2-v2.p1))==0){
		if(Point_line_relation(v1.p1,v2)==0) return 1; //�غ� 
		else return 0; //ƽ�� 
	}
	return 2; //�ཻ 
} 
bool Point_on_seg(Point p,Line v){ //�жϵ��Ƿ��ڸ��߶��� 
	return sgn(Cross(p-v.p1,v.p2-v.p1))==0&&sgn(Dot(p-v.p1,p-v.p2))<=0;
}
bool Cross_seg(Point a,Point b,Point c,Point d){//�ж����߶��Ƿ��ཻ 
	double c1=Cross(b-a,c-a),c2=Cross(b-a,d-a);
	double d1=Cross(d-c,a-c),d2=Cross(d-c,b-c);
	return sgn(c1)*sgn(c2)<=0&&sgn(d1)*sgn(d2)<=0;//���߶εĶ˵����߶���Ҳ�㣬��Ҫ <= 
}
Point Cross_point(Point a,Point b,Point c,Point d){  //�����߶εĽ��� 
	double s1=Cross(b-a,c-a);
	double s2=Cross(b-a,d-a);
	return Point(c.x*s2-d.x*s1,c.y*s2-d.y*s1)/(s2-s1);
}


---------//�����
int check(Point pt,Point *p,int n){  //�жϵ������εĹ�ϵ 
	for(int i=0;i<n;++i){
		if(p[i]==pt) return 3;   //3��ʾ��pt�ڶ���εĶ����� 
	}
	for(int i=0;i<n;++i){
		Line v=Line(p[i],p[(i+1)%n]);
		if(Point_on_seg(pt,v)) return 2; //2��ʾ���ڶ���εı��� 
	}
	int num=0;
	for(int i=0;i<n;++i){
		int j=(i+1)%n;
		int c=sgn(Cross(pt-p[j],p[i]-p[j]));
		int u=sgn(p[i].y-pt.y),v=sgn(p[j].y-pt.y);
		if(c>0&&u<0&&v>=0) ++num;
		if(c<0&&u>=0&&v<0) --num;
	}	
	return num!=0;  //1��ʾ�����ڲ���0��ʾ�����ⲿ 
} 
double Polygon_area(Point *p,int n){// �����ε���� 
	double area=0;
	for(int i=0;i<n;++i){
		area+=Cross(p[i],p[(i+1)%n]);  //���ָ�����ԭ������� 
	}
	return area/2;  //��������� 
}
Point Polygon_center(Point *p,int n){ //�����ε����� 
	Point ans(0,0);
	double tmp=Polygon_area(p,n);
	if(sgn(tmp)==0) return ans;
	for(int i=0;i<n;++i){
		ans=ans+(p[i]+p[(i+1)%n])*Cross(p[i],p[(i+1)%n]);
	}
	return ans/tmp/6;  //��������� /2 �Լ������ĵ� /3  
}


------//͹��
int Andrew(Point *p,int n,Point *q){//p��ԭͼ��q��͹��ͼ 
	sort(p,p+n,[](const Point &a,const Point &b){
		if(a.x==b.x) return a.y<b.y;
		return a.x<b.x;
	});
	n=unique(p,p+n)-p;
	int num=0; //͹���ĵ��� 
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

----//���η���������
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

--------//��ת����
double rotate(Point p[],int n){
	double ans=0;
	Point v;
	int cur=1;
	for(int i=0;i<n;++i){
		v=p[i]-p[(i+1)%n];
		while(Cross(v,p[(cur+1)%n]-p[cur])<0) cur=(cur+1)%n; //Ѱ�Ҷ���� 
		ans=max(ans,max(Distance(p[i],p[cur]),Distance(p[(i+1)%n],p[(cur+1)%n])));
	}
	return ans;
} 


--------//Բ
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
