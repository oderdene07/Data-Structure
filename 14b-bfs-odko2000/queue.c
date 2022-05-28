#include "DS.h"

void q_push(Queue *p, int x)
{
        struct Elm *s = malloc(sizeof(struct Elm));
        s->x = x;
        s->next = NULL;
        if (p->head == NULL && p->tail == NULL)
        {
                p->head = p->tail = s;
        }
        else
        {
                p->tail->next = s;
                p->tail = s;
        }
        p->len++;
}
void q_pop(Queue *p)
{
        struct Elm *s = p->head;
        p->head = p->head->next;
        if (p->head == NULL)
                p->tail = NULL;
        p->len--;
}
void q_print(Queue *p)
{
        struct Elm *s = p->head;
        while (s != NULL)
        {
                printf("%d\n", s->x);
                s = s->next;
        }
}