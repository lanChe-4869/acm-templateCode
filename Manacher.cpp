#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N=110000+10;
char s1[N],s[N<<1];
int r[N<<1];
int main(){
	while(~scanf("%s",s1)){
		int len=strlen(s1),cnt=0;
		for(int i=0;i<len;++i){
			s[cnt++]='#';s[cnt++]=s1[i];
		}
		s[cnt++]='#';
		len=cnt;
		int R=-1,c=-1,ans=1;
		for(int i=0;i<len;++i){
			r[i]= R>i ?min(r[2*c-i],R-i):1;  //主要式子 
			while(i+r[i]<len&&i-r[i]>=0){
				if(s[i-r[i]]==s[i+r[i]]){
					++r[i];
				}
				else
					break;
			}
			if(i+r[i]>R){
				R=i+r[i];
				c=i;
			}
		//	printf("%d %d\n",i,r[i]);
			ans=max(ans,r[i]-1); 
		}
		printf("%d\n",ans);
	}
	return 0;
}
