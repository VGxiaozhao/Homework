#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
typedef  long long LL;
const int maxn = 1e6 + 5;

int a[maxn];
LL sum[maxn];
LL ans[maxn];

int main()
{
	freopen("d:\\in.txt", "r", stdin);
	int n;
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		stack<int> st;
		LL mxans = 0;
		memset(ans, 0, sizeof(ans));
		while (!st.empty()) st.pop();
		for (int i = 1; i <= n; i++)
		{
			sum[i] = sum[i - 1] + a[i];
			int last = i-1;
			while (!st.empty() && a[last = st.top()] <= a[i])
				st.pop();
			if (last + 1 < i)		//说明有夹缝
				ans[i] = ans[last] + (i - last-1)*min(a[last], a[i]) - (sum[i - 1] - sum[last]);
			else
				ans[i] = ans[i - 1];
			mxans = max(mxans, ans[i]);
			st.push(i);
		}
		cout << mxans << endl;
	}
	return 0;
}

/*
5
1 2 3 4 5

5
5 4 3 2 1

5
3 1 2 1 5

5
3 1 5 1 2

5
3 1 2 1 2

10
1 2 1 2 3 1 5 6 1 9

8
5 1 3 1 1 4 2 1

9
5 1 3 1 1 4 2 1 9

*/
