#include "DS.h"

void uf_init(WeightedUF *p_uf, int n)
{
	p_uf->N = n;
	p_uf->id = (int *)malloc(sizeof(int) * n);
	p_uf->sz = (int *)malloc(sizeof(int) * n);
	int i;
	for (i = 0; i < n; i++)
	{
		p_uf->id[i] = i;
		p_uf->sz[i] = 1;
	}
}

int uf_connected(WeightedUF *p_uf, int p, int q)
{
	return uf_find(p_uf, p) == uf_find(p_uf, q);
}

int uf_find(WeightedUF *p_uf, int p)
{
	if (p_uf->id[p] == p)
		return p_uf->id[p] = p;
	else
		return p_uf->id[p] = uf_find(p_uf, p_uf->id[p]);
}

void uf_union(WeightedUF *p_uf, int p, int q)
{
	int pid = uf_find(p_uf, p);
	int qid = uf_find(p_uf, q);
	if (pid == qid)
		return;
	if (qid == 0 || p_uf->sz[qid] < p_uf->sz[pid])
	{
		int tmp = qid;
		qid = pid;
		pid = tmp;
	}
	if (pid == 0)
	{
		p_uf->sz[pid] += p_uf->sz[qid];
		p_uf->id[qid] = pid;
		return;
	}
	p_uf->sz[qid] += p_uf->sz[pid];
	p_uf->id[pid] = qid;
}
