#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 32 //种群数量
#define L 5   //二进制位数
#define MUTATE_RATE 5
#define MOD 100000007
int animal[M];
int selected[M] = { 0 };
int selectqueue[M], tol = 0;
int sumfitness;

int f(int x)
{
	return -x*x+16*x-3;
	//return x*x;
}

void change(int *a,int u)
{
    int tmp = 0;
    tmp = (*a)%(1<<u);
    *a = (((*a)>>u)^1)<<u|tmp;
}

void crossover(int* a, int *b)
{
	sumfitness -= f(*a);
	sumfitness -= f(*b);
	int u = 1, v = 1;
	while (u == v)
	{
		u = rand() % L;
		v = rand() % L;
	}
	if ((*a)&(1 << u) != (*b)&(1 << u))
	{
		//*a ^= (1 << u);
		//*b ^= (1 << u);
		change(a,u);
		change(b,u);
	}
	if ((*a)&(1 << v) != (*b)&(1 << v))
	{
//		*a ^= (1 << v);
//		*b ^= (1 << v);
        change(a,v);
        change(b,v);
	}
	if(*a>=1<<L||*b>=1<<L)
    {
        printf("%d %d",u,v);
        puts("what?");
    }
	sumfitness += f(*a);
	sumfitness += f(*b);
}

int myRand()          //
{
	int ret = 1;
	for (int i = 0; i<5; i++)
		ret = ((ret*(rand() + 1)) % MOD + MOD) % MOD;
	return ret;
}

void mutate(int *a)
{
	sumfitness -= f(*a);
	int i = myRand() % L;
	//*a ^= 1 << L;
	change(a,i);
	sumfitness += f(*a);
}

void init()
{
	int i, j;
	sumfitness = 0;
	for (i = 0; i<M; i++)
	{
		animal[i] = myRand() % (1 << L);
		sumfitness += f(animal[i]);
	}
}

int doSelect(int times)
{
	int ret = 0;
	tol = 0;
	memset(selected, 0, sizeof(selected));
	while (tol<times)
	for (int i = 0; i<M; i++)
	{
		if (f(animal[i])>myRand() % sumfitness && !selected[i])
		{
			selected[i] = 1;
			selectqueue[tol++] = i;
		}
	}
	return ret;
}

void findtocross(int times)
{
	int u = 1, v = 1;
	while (times--)
	{
		u = v = 1;
		while (u == v)
		{
			u = rand() % tol;
			v = rand() % tol;
		}
		crossover(&animal[selectqueue[u]], &animal[selectqueue[v]]);
	}
}

void findtomutate()
{
	for (int i = 0; i<M; i++)
	{
		if (myRand() % 100 <= MUTATE_RATE)
			mutate(&animal[i]);
	}
}

void test()
{
//	for (int i = 0; i<32; i++)
//		printf("%d %d\n", i, f(i));
    int a = 5;  //00101
    change(&a,4);
    printf("%d\n",a);
}

int main()
{
	//test();
	int T = 100;
	int cnt[1 << L+1] = { 0 };
	int ans = -1, maxshow = 0;
	srand(time(NULL));
	init();
	while (T--)
	{
		doSelect(8);
		findtocross(tol / 2 * 3);
		findtomutate();
	}
	doSelect(8);
	for (int i = 0; i<tol; i++)
	{
		cnt[animal[selectqueue[i]]]++;
	}
	for (int i = 0; i<(1 << L); i++)
	{
		if (cnt[i]>maxshow)
		{
			maxshow = cnt[i];
			ans = i;
		}
	}
	printf("%d\n", ans);
	//_sleep(1000);
	return 0;
}
