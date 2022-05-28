#include "DS.h"

void s_push(Stack *p, int x)
{
        struct Elm *s = (struct Elm *)malloc(sizeof(struct Elm));
        s->x = x;
        s->next = p->top;
        p->top = s;
        p->len++;
}
void s_pop(Stack *p)
{
        struct Elm *s = p->top;
        p->top = s->next;
        p->len--;
}
void s_print(Stack *p)
{
        struct Elm *s = p->top;
        while (s != NULL)
        {
                printf("%d ", s->x);
                s = s->next;
        }
}
