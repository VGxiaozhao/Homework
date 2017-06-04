#include <bits/stdc++.h>
using namespace std;

const int maxn = 205;
double d[maxn], p[maxn];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int L, w, v, n;
		scanf("%d%d%d%d", &L, &w, &v, &n);
		double cango = 1.0*w*v;
		d[n + 1] = L;
		for (int i = 1; i <= n; i++)
			scanf("%lf", &d[i]);
		for (int i = 1; i <= n; i++)
			scanf("%lf", &p[i]);

		bool ok = true;
		for (int i = n + 1; i>1; i--)
		if (d[i] - d[i - 1]>cango)
		{
			ok = false;
			break;
		}
		if (!ok)
		{
			puts("No Solution");
			continue;
		}
		double ans = 0.0;
		double curw = 0.0;
		for (int cur = 1; cur<=n;)
		{
			double minprice = d[cur + 1];
			int tag = cur + 1;
			for (int i = cur + 1; i <= n&&d[cur] + cango >= d[i]; i++)
			{
				if (p[i] <= minprice)
				{
					minprice = p[i];
					tag = i;
				}
			}
			if (p[cur]<p[tag])
			{
				ans += (w - curw)*p[cur];
				curw = w - (d[tag] - d[cur]) / v;
			}
			else if (d[cur] + curw*v<d[tag])
			{
				ans += ((d[tag] - d[cur]) / v - curw)*p[cur];
				curw = 0.0;
			}
			//cout<<ans<<endl;
			cur = tag;
		}

		printf("%.2lf\n", ans);
	}
	return 0;
}
