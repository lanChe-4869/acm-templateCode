#include<stdio.h>
#include<string.h>
#include<vector>
#include<stdlib.h>
#include<math.h>
#define max 40001
#define maxl 25
using namespace std;
typedef struct
{
    int from,to,w;
}edge;//����ṹ�������洢��
 
vector<edge>edges;
vector<int> G[max];
//����ߵ�����
int grand[max][maxl],gw[max][maxl];//x������2^i�η��Ľڵ㣬x������������2^i�η��ľ���
int depth[max];//���
int n,m,N;
void addedge(int x,int y,int w)//�ѱ߱��������ĺ���
{
   edge a={x,y,w},b={y,x,w};
   edges.push_back(a);
   edges.push_back(b);
 
   G[x].push_back(edges.size()-2);
   G[y].push_back(edges.size()-1);
}
void dfs(int x)//dfs��ͼ
{
    for(int i=1;i<=N;i++)//��һ�������ȫ������0�����ڶ����ڵ���б仯�ˣ������Ļ����鸴�ƴ����������Щ����
 
    {
        grand[x][i]=grand[grand[x][i-1]][i-1];
        gw[x][i]=gw[x][i-1]+gw[grand[x][i-1]][i-1];
       // if(grand[x][i]==0) break;
    }
 
    for(int i=0;i<G[x].size();i++)
    {   edge  e = edges[G[x][i]];
         if(e.to!=grand[x][0])//�������Ǳ������˫����������������ı߲��������׾��������Ӹ��׵Ļ��Ͳ���ִ�У���Ȼ����ѭ���ˡ�
 
           {
                depth[e.to]=depth[x]+1;//�����ӵ���ȵ������ְֵļ�1
                grand[e.to][0]=x;//��x�����Ǹ��ڵ�ĸ��׵���x
                gw[e.to][0]=e.w;//��x�����Ǹ��ڵ�ľ�����������ߵľ���
                dfs(e.to);//���������潨
           }
    }
}
void Init(){
    //nΪ�ڵ����
    N = floor(log(n + 0.0) / log(2.0));//���������2^i����
    depth[1]=0;//���������Ȳ����ڣ���-1��ʾ
    memset(grand,0,sizeof(grand));
    memset(gw,0,sizeof(gw));
    dfs(1);//��1Ϊ���ڵ㽨��
 
}
int lca(int a,int b)
{ if(depth[a] > depth[b]) swap(a, b);//��֤a��b���棬���ڼ���
    int ans = 0;
    for(int i = N; i >= 0; i--) //�����ڶ����Ʋ�֣��Ӵ�С����
        if(depth[a] < depth[b] && depth[grand[b][i]] >= depth[a])//a��b������b�������󲻻ᵽa����
            ans +=gw[b][i], b=grand[b][i];//�Ȱ���Ƚϴ��b������
 
    for(int j=N;j>=0;j--)//��ͬһ�߶���,����һ��������,�����ǲ���ͬ�ڵ㣬��ȫ������֮��grand��a����0������lca,�����н��͹���
    {
        if(grand[a][j]!=grand[b][j])
        {   ans+=gw[a][j];
            ans+=gw[b][j];
            a=grand[a][j];
            b=grand[b][j];
 
        }
    }
    if(a!=b)//a����b���������������ɫ������������
    {
        ans+=gw[a][0],ans+=gw[b][0];
    }
    return ans;
}
int main()
{ int t ;
  scanf("%d",&t);
  while(t--)
  {   scanf("%d%d",&n,&m);
      for(int i=1;i<n;i++)
      {
          int x,y,w;
          scanf("%d%d%d",&x,&y,&w);
          addedge(x,y,w);
      }
     Init();
     for(int i=1;i<=m;i++)
     {
         int x,y;
         scanf("%d%d",&x,&y);
         printf("%d\n",lca(x,y));
     }
  }
}
