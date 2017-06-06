#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 32 //种群数量
#define L 5   //二进制位数
#define MUTATE_RATE 2
#define MOD 100000007
#define SELECT_SIZE M/2
#define RANDOM_SELECT_RATE 10
int animal[M];
int selected[M] = { 0 };
int selectqueue[M], tol = 0;

int myRand()          //C语言rand函数随机性太差，封装一个自己的
{
	int ret = 1;
	for (int i = 0; i<5; i++)
		ret = ((ret*(rand() + 1)) % MOD + MOD) % MOD;
	return ret;
}

int f(int x)
{
	return -x*x + 16 * x - 3;
}

void change(int *a, int u)	//将a二进制数上第u个取反
{
	int tmp = 0;
	tmp = (*a) % (1 << u);
	*a = (((*a) >> u) ^ 1) << u | tmp;
}

void crossover(int a, int b, int *x, int *y)		//交叉两个数，产生两个新数
{
	int u = 1, v = 1;
	*x = a;
	*y = b;
	while (u == v)
	{
		u = myRand() % L;
		v = myRand() % L;
	}
	if ((a >> u)&1 != (b >> u)&1)
	{
		change(x, u);
		change(y, u);
	}
	if ((a >> v)&1 != (b >> v)&1)
	{
		change(x, v);
		change(y, v);
	}
}

void mutate(int *a)			//变异
{
	int i = myRand() % L;
	change(a, i);
}

void init()					//初始化产生种群
{
	int i, j;
	for (i = 0; i < M; i++)
	{
		animal[i] = myRand() % (1 << L);
	}
}

int getFitness()			//计算群体适应度
{
	int ret = 0;
	for (int i = 0; i<M; i++)
		ret += f(animal[i]);
	return ret;
}

void doSelect(int times)		//选择操作
{
	int ret = 0;
	tol = 0;
	memset(selected, 0, sizeof(selected));
	int sumfitness = getFitness();
	while (times--)
	for (int i = 0; i<M; i++)
	{
		if (!selected[i] && f(animal[i])>myRand() % sumfitness)
		{
			selected[i] = 1;
			selectqueue[tol++] = animal[i];
		}
	}
	for (int i = 0; i < M&&tol < SELECT_SIZE; i = (i+1)%M)
	{
		if (!selected[i] && myRand() % 100 < RANDOM_SELECT_RATE)
		{
			selected[i] = 1;
			selectqueue[tol++] = animal[i];
		}
	}
}

void findtocross()			//选择交叉操作，并将没被选择的个体淘汰
{
	int u = 1, v = 1;
	for (int i = 0; i<SELECT_SIZE; i += 2)
	{
		int x = 1, y = 1;
		crossover(selectqueue[i], selectqueue[i + 1], &x, &y);
		animal[i] = x;
		animal[i + 1] = y;
	}
	for (int i = 0; i<tol; i++)
		animal[i + SELECT_SIZE] = selectqueue[i];
}

void findtomutate()			//选择变异
{
	for (int i = 0; i<M; i++)
	{
		if (myRand() % 100 <= MUTATE_RATE)
			mutate(&animal[i]);
	}
}

void output()
{
	for (int i = 0; i<M; i++)
		printf("%d ", animal[i]);
	puts("");
}

int main()
{
	int T = 100;		//迭代次数
	int cnt[1 << (L + 1)] = { 0 };
	int ans = -1, maxshow = 0;
	srand(time(NULL));
	init();
	while (T--)
	{
		doSelect(8);
		findtocross();
		findtomutate();
	}
	output();
	for (int i = 0; i<tol; i++)
	{
		cnt[animal[i]]++;
	}
	for (int i = 0; i<(1 << L); i++)
	{
		if (cnt[i]>maxshow)
		{
			maxshow = cnt[i];
			ans = i;
		}
	}
	printf("种群中性状出现最多的是：%d\n", ans);
	return 0;
}
