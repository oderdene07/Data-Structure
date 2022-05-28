#include "DS.h"

static void swim(Heap *p, int);
static void sink(Heap *p, int);

int less(const Msg *a, const Msg *b)
{
        if (a->priority > b->priority)
                return 1;
        else if (a->priority < b->priority)
                return 0;
        else
        {
                if (a->time > b->time)
                        return 1;
                else
                        return 0;
        }
}

void insert(Heap *p, const Msg x)
{
        int j = p->h_len;
        p->h_arr[p->h_len] = x;
        p->h_len++;
        swim(p, j);
        // int i;
        // for (i = 0; i < p->h_len; i++)
        // {
        //         printf("   %d  %s\n ", p->h_arr[i].time, p->h_arr[i]);
        // }
}

static void swim(Heap *p, int k)
{
        while (k >= 0 && less(&p->h_arr[k / 2], &p->h_arr[k]))
        {
                Msg temp = p->h_arr[k];
                p->h_arr[k] = p->h_arr[k / 2];
                p->h_arr[k / 2] = temp;
                k = k / 2;
        }
}

static void sink(Heap *p, int k)
{
        while (2 * k < p->h_len)
        {
                int j = 2 * k;
                if (j < p->h_len - 1 && less(&p->h_arr[j], &p->h_arr[j + 1]))
                {
                        j++;
                }

                if (!less(&p->h_arr[k], &p->h_arr[j]))
                {
                        break;
                }

                Msg temp = p->h_arr[j];
                p->h_arr[j] = p->h_arr[k];
                p->h_arr[k] = temp;

                k = j;
        }
}

Msg delMin(Heap *p)
{
        Msg min = p->h_arr[0];
        Msg temp = p->h_arr[0];
        p->h_arr[0] = p->h_arr[p->h_len - 1];
        p->h_arr[p->h_len - 1] = temp;
        p->h_len--;
        sink(p, 0);
        // int i;
        // for (i = 0; i < p->h_len; i++)
        // {
        //         printf("   %d  %s\n ", p->h_arr[i].time, p->h_arr[i]);
        // }
        return min;
}