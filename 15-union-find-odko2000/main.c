#include "DS.h"

int table[5000][5000];
int n, m;
WeightedUF uf;

int isFree(int x, int y)
{
	return x >= 0 & y >= 0 & x < n & y < n;
}

int main()
{
	int i, x, y;
	scanf("%d%d", &n, &m);
	uf_init(&uf, n * n + 2); // Нэмэлт 2 хийсвэр оройг нэмнэ.
	for (i = 1; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		table[x][y] = 1;
		if (x == 0)
			uf_union(&uf, y + 1, 0);
		if (x == n - 1)
			uf_union(&uf, n * x + y + 1, n * n + 1);
		if (isFree(x + 1, y) && table[x + 1][y])
			uf_union(&uf, n * x + y + 1, n * (x + 1) + y + 1);
		if (isFree(x - 1, y) && table[x - 1][y])
			uf_union(&uf, n * x + y + 1, n * (x - 1) + y + 1);
		if (isFree(x, y + 1) && table[x][y + 1])
			uf_union(&uf, n * x + y + 1, n * x + y + 2);
		if (isFree(x, y - 1) && table[x][y - 1])
			uf_union(&uf, n * x + y + 1, n * x + y);
		if (uf_find(&uf, n * n + 1) == 0)
		{
			printf("%d\n", i);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}