#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 13;

bool g[maxn][maxn],used[maxn];
double x1[maxn],y1[maxn];
double x2[maxn],y2[maxn];
int link[maxn],n;

bool dfs(int u)
{
    for(int v=1; v<=n; v++)
        if(g[u][v]&&!used[v])
    {
        used[v] = true;
        if(link[v]==-1||dfs(link[v]))
        {
            link[v] = u;
            return true;
        }
    }
    return false;
}

int hungary()
{
    int ret = 0;
    memset(link,-1,sizeof(link));
    for(int i=1; i<=n; i++)
    {
        memset(used,0,sizeof(used));
        if(dfs(i)) ret++;
    }
    return ret;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1; i<=n; i++)
            scanf("%lf%lf",&x1[i],&y1[i]);
        for(int i=1; i<=n; i++)
            scanf("%lf%lf",&x2[i],&y2[i]);
        memset(g,0,sizeof(g));
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            if(x1[i]>=x2[j]&&y1[i]>=y2[j])
                g[j][i] = g[i][j] = true;
        cout<<hungary()<<endl;
    }
    return 0;
}
