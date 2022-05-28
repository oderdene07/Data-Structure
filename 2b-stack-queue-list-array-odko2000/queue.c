#include "DS.h"

void q_push(Queue *p, int x)
{
	    p->q_arr[p->q_len] = x;
		p->q_len = p->q_len + 1;
}

void q_pop(Queue *p)
{
		int i;
		for(i = 0; i < p->q_len; i++){
			p->q_arr[i] = p->q_arr[i + 1];
		}
		p->q_len = p->q_len - 1;
}

void q_print(Queue *p)
{
        int i;
        for (i = 0; i < p->q_len; i++) {
                printf("%d ", p->q_arr[i]);
        }
        printf("\n");
}
