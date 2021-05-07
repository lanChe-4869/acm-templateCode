void Init(string p,int lenp){
	Next[0]=Next[1]=0;
	for(int i=1;i<lenp;++i){
		int j=Next[i];
		while(j&&p[j]!=p[i]) j=Next[j];
		Next[i+1]= (p[i]==p[j])?j+1:0;
	}
}
bool kmp(string s,string p){
	Init(p,lenp);
	int j=0;
	for(int i=0;i<lens;++i){
		while(j&&s[i]!=p[j]) j=Next[j];
		if(s[i]==p[j]) ++j;
		if(j==lenp) return true;
	}
	return false;
}
