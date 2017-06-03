/*
    @author:    xiaozhao
    @Date:      1st,May,2017
    knn算法，在二维空间中生成一组随机的训练样例，f(x)的取值为-1或者1.再随机生成测试样例,
    k设置为11
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3+5;
const int K = 101;

struct Node
{
    double x,y;
    int f;
}node[maxn];

struct dis
{
    double d;
    int f;
    dis(){}
    dis(double _d,int _f): d(_d),f(_f){}
    bool operator<(const dis& cmp) const
    {
        return d<cmp.d;
    }
};
vector<dis> p;

void generateTrain()
{
    srand(time(NULL));
    for(int i=0; i<maxn; i++)
    {
        node[i].x = rand()%maxn/10;
        node[i].y = rand()%maxn/10;
        node[i].f = rand()%2;
        if(node[i].f==0)
            node[i].f = -1;
    }
}

void addToVector(const Node& a,double x,double y)
{
    double d = (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);
    d = sqrt(d);
    p.push_back(dis(d,a.f));
}

int main()
{
    generateTrain();
    double x,y;
    while(1)
    {
        p.clear();
        puts("please input x:");
        scanf("%lf",&x);
        puts("please input y:");
        scanf("%lf",&y);
        p.clear();
        for(int i=0; i<maxn; i++)
            addToVector(node[i],x,y);
        sort(p.begin(),p.end());
        int cnt1 = 0,cnt_1=0;
        cnt1 = cnt_1 = 0;
        for(int i=0; i<K; i++)
        {
            if(p[i].f==1)
                cnt1++;
            else
                cnt_1++;
        }
        printf("1: %d -1:%d\n",cnt1,cnt_1);
        if(cnt1>cnt_1)
            puts("f(x,y)=1");
        else
            puts("f(x,y)=-1");
    }
    return 0;
}
