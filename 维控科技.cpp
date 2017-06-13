#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
typedef  long long LL;

class CBox
{
public:
	CBox(){}
	~CBox(){}
	CBox(int height, int index, LL sum, LL ans) :
		m_nHeight(height),
		m_nIndex(index),
		m_lSum(sum),
		m_lAns(ans){}

	int getHeight()
	{
		return m_nHeight;
	}

	LL getAns()
	{
		return m_lAns;
	}

	int getIndex()
	{
		return m_nIndex;
	}

	LL getSum()
	{
		return m_lSum;
	}

private:
	int m_nHeight, m_nIndex;
	LL m_lSum, m_lAns;
};

class CSolver
{
public:
	static void init()
	{
		while (!m_st.empty())
			m_st.pop();
	}
	static LL getAns(int a[], int st, int ed)
	{
		init();
		LL ret = 0, sum = 0;
		m_st.push(CBox(a[st], st, a[st], 0));
		sum = a[st];
		for (int i = st + 1; i <= ed; i++)
		{
			CBox* last = NULL;		//记录单调栈最后一个访问的元素
			while (!m_st.empty() && (last = &m_st.top())->getHeight() <= a[i])			//当栈顶比当前小，说明可以形成坑，弹出元素
				m_st.pop();
			LL temp = 0;
			if (last->getIndex() + 1 < i)			//这样表示可以形成坑
				temp = last->getAns() + (i - last->getIndex() - 1) * min(last->getHeight(), a[i]) - (sum - last->getSum());
			else
				temp = last->getAns();
			sum = sum + a[i];
			m_st.push(CBox(a[i], i, sum, temp));
			ret = max(ret, temp);
		}
		return ret;
	}
private:
	static stack<CBox> m_st;
};

stack<CBox> CSolver::m_st;

int main()
{
	freopen("d:\\test.txt", "r", stdin);
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int* a = new int[n + 1];
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		cout << CSolver::getAns(a, 1, n) << endl;
		delete[] a;
	}
	return 0;
}
