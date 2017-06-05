/*
    暴力搜索时间复杂度太高,采用动态规划的做法时间复杂度为O(n^2),当数据比较小的时候效率较优
*/
#include <bits/stdc++.h>
using namespace std;
int a[12],n,m;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; i++)
            scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        int maxn = m*a[n]+1;
        int* dp = new int[maxn];
        for(int i=1; i<maxn; i++)
            dp[i] = maxn;
        dp[0] = 0;
        for(int i=0; i<maxn-a[n]; i++)
        {
            if(dp[i]>=m) continue;
            for(int j=1; j<=n; j++)
            {
                dp[i+a[j]] = min(dp[i+a[j]],dp[i]+1);
            }
        }

        int st = 0,len = 1;
        int cur = 0,curst;
        for(int i=1; i<maxn; i++)
        {
            if(dp[i]<=m)
            {
                cur++;
                if(cur==1)
                    curst = i;
            }
            else
                cur = 0;
            if(cur>len)
            {
                len = cur;
                st = curst;
            }
        }
        cout<<st<<" "<<st+len-1<<endl;
        delete []dp;
    }
    return 0;
}
