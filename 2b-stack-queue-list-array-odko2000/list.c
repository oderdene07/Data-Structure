#include "DS.h"

void l_push_back(List *p, int x)
{
	p->l_arr[p->l_len] = x;
	p->l_len++;
}

void l_push_front(List *p, int x)
{
	int i;
	for (i = p->l_len; i >= 0; i--)
	{
		p->l_arr[i + 1] = p->l_arr[i];
	}
	p->l_len++;
	p->l_arr[0] = x;
}

void l_insert(List *p, int x, int pos)
{
	if (pos > p->l_len)
	{
		p->l_arr[p->l_len] = x;
		p->l_len++;
	}
	else
	{
		int i;
		for (i = p->l_len; i >= pos; i--)
		{
			p->l_arr[i + 1] = p->l_arr[i];
		}
		p->l_len++;
		p->l_arr[pos] = x;
	}
}

void l_pop_front(List *p)
{
	int i;
	for (i = 0; i < p->l_len; i++)
	{
		p->l_arr[i] = p->l_arr[i + 1];
	}
	p->l_len--;
}

void l_pop_back(List *p)
{
	p->l_len--;
}

void l_erase(List *p, int pos)
{
	if (pos < p->l_len)
	{
		int i;
		for (i = pos; i < p->l_len; i++)
		{
			p->l_arr[i] = p->l_arr[i + 1];
		}
		p->l_len--;
	}
}

void l_print(List *p)
{
	int i;
	for (i = 0; i < p->l_len; i++)
	{
		printf("%d ", p->l_arr[i]);
	}
	printf("\n");
}

int l_search(List *p, int x)
{
	int i, count;
	for (i = 0; i < p->l_len; i++)
	{
		count = 0;
		if (p->l_arr[i] == x)
		{
			return i;
			count++;
		}
	}
	if (count == 0)
		return -1;
}