#include "DS.h"

void l_push_back(List *p, Token x)
{
  TokenElm *s = malloc(sizeof(struct TokenElm));
  if (s == NULL)
  {
    return;
  }
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

void l_push_front(List *p, Token x)
{
  TokenElm *s = malloc(sizeof(struct TokenElm));
  s->x = x;
  s->next = p->head;
  if (p->head == NULL && p->tail == NULL)
  {
    p->head = p->tail = s;
  }
  else
  {
    p->head = s;
  }
  p->len++;
}

void l_insert(List *p, Token x, int pos)
{
  if (pos == p->len)
  {
    l_push_back(p, x);
    return;
  }
  if (pos == 0)
  {
    l_push_front(p, x);
    return;
  }
  TokenElm *temp = p->head, *s = (TokenElm *)malloc(sizeof(TokenElm));
  s->x = x;
  int i;
  for (i = 1; i < pos; i++)
  {
    temp = temp->next;
  }
  s->next = temp->next;
  temp->next = s;
  p->len++;
}

void l_pop_front(List *p)
{
  TokenElm *s = p->head;
  p->head = p->head->next;
  if (p->head == NULL)
    p->tail = NULL;
  p->len--;
}

void l_pop_back(List *p)
{
  TokenElm *s = p->head;
  if (p->head->next == NULL)
  {
    free(p->head);
    p->head = NULL;
    p->tail = NULL;
  }
  else
  {
    while (s->next != p->tail)
      s = s->next;

    free(p->tail);
    s->next = NULL;
    p->tail = s;
  }
  p->len--;
}

void l_erase(List *p, int pos)
{
  TokenElm *s = p->head;

  if (pos == 0)
    l_pop_front(p);

  if (pos < p->len && pos > 0)
  {
    int i;
    for (i = 1; i < pos; i++)
    {
      if (s->next != NULL)
      {
        s = s->next;
      }
    }
    s->next = s->next->next;
    p->len--;
  }
}

void l_print(List *p)
{
  struct TokenElm *s = p->head;
  while (s != NULL)
  {
    if (s->x.flag)
    {
      printf("%d", s->x.val);
    }
    else
    {
      printf("%c", s->x.op);
    }
    s = s->next;
  }
  printf("\n");
}
