#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
char s[50][50];
int n, m;
int dp[50][50];
bool vis[50][50];

int dfs(int x, int y)
{
	if (x<1 || x>n || y<1 || y>m) return INF;
	if (s[x][y] == 'W') return INF;
	if (s[x][y] == 'X') return 0;
	if (vis[x][y] && dp[x][y] == -1) return INF;
	if (dp[x][y] != -1) return dp[x][y];
	int ret = INF;
	vis[x][y] = true;
	ret = min(ret, dfs(x + 1, y));
	ret = min(ret, dfs(x - 1, y));
	ret = min(ret, dfs(x, y + 1));
	ret = min(ret, dfs(x, y - 1));
	ret = min(ret, dfs(x - 2, y - 2));
	ret = min(ret, dfs(x - 2, y + 2));
	ret = min(ret, dfs(x + 2, y - 2));
	ret = min(ret, dfs(x - 2, y + 2));
	//vis[x][y] = false;
	if (dp[x][y] == -1) dp[x][y] = ret + 1;
	return dp[x][y] = min(dp[x][y], ret + 1);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%s", s[i] + 1);
		memset(dp, -1, sizeof(dp));
		memset(vis, 0, sizeof(vis));
		int ans = INF;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (s[i][j] == 'S')
				{
					ans = dfs(i, j);
					break;
				}
			}
		}
		if (ans >= INF)
			puts("NO ANSWER");
		else
			printf("%d\n", ans);
	}
	return 0;
}
