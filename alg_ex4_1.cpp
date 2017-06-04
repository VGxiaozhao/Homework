#include <bits/stdc++.h>
using namespace std;

int dp[505],len;
int a[505];
int main()
{
	int T,n;
	scanf("%d",&T);
	while (T--)
	{
		len = 0;
		scanf("%d", &n);
		for(int i=1; i<=n; i++)
            scanf("%d",&a[i]);
		for(int i = n; i>0; i--)
		{
		    int tmp = 0;
            for(int j=i+1; j<=n; j++)
                if(a[i]<a[j])
                    tmp = max(tmp,dp[j]);
            dp[i] = tmp+1;

            len = max(len,dp[i]);
		}
		for(int i=1; i<=n; i++)
            printf("%d %d\n",a[i],dp[i]);
		cout << len << endl;
		for(int i=1; i<=n; i++)
            if(dp[i]==len)
        {
            len--;
            printf("%d ",a[i]);
        }
        puts("");
	}
	return 0;
}
