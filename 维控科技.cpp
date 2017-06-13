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
    CBox(int height,int index,LL sum,LL ans):
        m_nHeight(height),
        m_nIndex(index),
        m_lSum(sum),
        m_lAns(ans)
        {

        }
    int getHeight()
    {
        return m_nIndex;
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
    int m_nHeight,m_nIndex;
    LL m_lSum,m_lAns;
};

class CSolver
{
public:
    CSolver()
    {
        while(!m_st.empty())
            m_st.pop();
    }
    ~CSolver()
    {
        while(!m_st.empty())
            m_st.pop();
    }
    static void init()
    {
        while(!m_st.empty())
            m_st.pop();
    }
    static LL getAns(int a[],int st,int ed)
    {
        LL ret = 0,sum = 0;
        m_st.push(CBox(a[st],st,0,0));
        sum = a[st];
        for(int i=st+1; i<=ed; i++)
        {
            CBox* last = NULL;
            while(!m_st.empty() && (last=&m_st.top())->getHeight() <=a[i])
                m_st.pop();
            LL temp=0;
            if(last->getIndex()+1<i)
                temp = last->getAns() + (i-last->getIndex()-1)*min(last->getHeight(),a[i]) - ( sum-last->getSum());
            else
                temp = last->getAns();
            sum = sum + a[i];
            m_st.push(CBox(a[i],i,sum,temp));
            ret = max(ret,temp);
        }
        return ret;
    }
private:
    static stack<CBox> m_st;
};


int main()
{
	//freopen("d:\\in.txt", "r", stdin);
	int n;
	while (scanf("%d", &n) != EOF)
	{
	    int* a = new int[n+1];
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
        cout<<CSolver::getAns(a,1,n)<<endl;
        delete[] a;
//		stack<int> st;
//		LL mxans = 0;
//		memset(ans, 0, sizeof(ans));
//		while (!st.empty()) st.pop();
//		for (int i = 1; i <= n; i++)
//		{
//			sum[i] = sum[i - 1] + a[i];
//			int last = i-1;
//			while (!st.empty() && a[last = st.top()] <= a[i])
//				st.pop();
//			if (last + 1 < i)		//说明有夹缝
//				ans[i] = ans[last] + (i - last-1)*min(a[last], a[i]) - (sum[i - 1] - sum[last]);
//			else
//				ans[i] = ans[i - 1];
//			mxans = max(mxans, ans[i]);
//			st.push(i);
//		}
//		cout << mxans << endl;
	}
	return 0;
}
