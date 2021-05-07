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
}edge;//这个结构体用来存储边
 
vector<edge>edges;
vector<int> G[max];
//保存边的数组
int grand[max][maxl],gw[max][maxl];//x向上跳2^i次方的节点，x到他上面祖先2^i次方的距离
int depth[max];//深度
int n,m,N;
void addedge(int x,int y,int w)//把边保存起来的函数
{
   edge a={x,y,w},b={y,x,w};
   edges.push_back(a);
   edges.push_back(b);
 
   G[x].push_back(edges.size()-2);
   G[y].push_back(edges.size()-1);
}
void dfs(int x)//dfs建图
{
    for(int i=1;i<=N;i++)//第一个几点就全部都是0咯，第二个节点就有变化了，不理解的话建议复制代码输出下这些数组
 
    {
        grand[x][i]=grand[grand[x][i-1]][i-1];
        gw[x][i]=gw[x][i-1]+gw[grand[x][i-1]][i-1];
       // if(grand[x][i]==0) break;
    }
 
    for(int i=0;i<G[x].size();i++)
    {   edge  e = edges[G[x][i]];
         if(e.to!=grand[x][0])//这里我们保存的是双向边所以与他相连的边不是他父亲就是他儿子父亲的话就不能执行，不然就死循环了。
 
           {
                depth[e.to]=depth[x]+1;//他儿子的深度等于他爸爸的加1
                grand[e.to][0]=x;//与x相连那个节点的父亲等于x
                gw[e.to][0]=e.w;//与x相连那个节点的距离等于这条边的距离
                dfs(e.to);//深搜往下面建
           }
    }
}
void Init(){
    //n为节点个数
    N = floor(log(n + 0.0) / log(2.0));//最多能跳的2^i祖先
    depth[1]=0;//根结点的祖先不存在，用-1表示
    memset(grand,0,sizeof(grand));
    memset(gw,0,sizeof(gw));
    dfs(1);//以1为根节点建树
 
}
int lca(int a,int b)
{ if(depth[a] > depth[b]) swap(a, b);//保证a在b上面，便于计算
    int ans = 0;
    for(int i = N; i >= 0; i--) //类似于二进制拆分，从大到小尝试
        if(depth[a] < depth[b] && depth[grand[b][i]] >= depth[a])//a在b下面且b向上跳后不会到a上面
            ans +=gw[b][i], b=grand[b][i];//先把深度较大的b往上跳
 
    for(int j=N;j>=0;j--)//在同一高度了,他们一起向上跳,跳他们不相同节点，当全都跳完之后grand【a】【0】就是lca,上面有解释哈。
    {
        if(grand[a][j]!=grand[b][j])
        {   ans+=gw[a][j];
            ans+=gw[b][j];
            a=grand[a][j];
            b=grand[b][j];
 
        }
    }
    if(a!=b)//a等于b的情况就是上面土色字体的那种情况
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
