#include "DS.h"

/* p-ийн зааж буй List-д x утгыг төгсгөлд хийнэ */
void l_push_back(List *p, int x)
{
  Elm *s = malloc(sizeof(Elm));
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

/* p-ийн зааж буй List-д x утгыг эхэнд хийнэ
   Бүх элементүүд нэг нэг байрлал хойшилно.
 */
void l_push_front(List *p, int x)
{
  Elm *s = malloc(sizeof(struct Elm));
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

/*
  p-ийн зааж буй List-д x утгыг pos байрлалд хийнэ
  pos болон түүнээс хойшхи элементүүд нэг байрлал ухарна.
  Тухайн байрлал List-ийн сүүлийн индексээс их бол төгсгөлд орно.
 */
void l_insert(List *p, int x, int pos)
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
  Elm *temp = p->head, *s = (Elm *)malloc(sizeof(Elm));
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

/*
  p-ийн зааж буй List-н эхлэлээс гаргана.
  List-ийн бүх элементүүд нэг нэг байрлал урагшилна
 */
void l_pop_front(List *p)
{
  Elm *s = p->head;
  p->head = p->head->next;
  if (p->head == NULL)
    p->tail = NULL;
  p->len--;
}

/* p-ийн зааж буй List-н төгсгөлөөс гаргана */
void l_pop_back(List *p)
{
  Elm *s = p->head;
  if (p->head->next == NULL)
  {

    p->head = NULL;
    p->tail = NULL;
  }
  else
  {
    while (s->next != p->tail)
      s = s->next;

    s->next = NULL;
    p->tail = s;
  }
  p->len--;
}

/* p-ийн зааж буй List-н pos байрлалаас гаргана.
   pos болон түүнээс хойшхи элементүүд нэг байрлал урагшилна.
   pos байрлалаас гарах боломжгүй бол юу ч хийхгүй.
 */
void l_erase(List *p, int pos)
{
  Elm *s = p->head;

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

/*
  p-ийн зааж буй List-н утгуудыг хэвлэнэ.
  Хамгийн эхний элементээс эхлэн дарааллаар, нэг мөрөнд
  нэг л элемент хэвлэнэ.
 */
void l_print(List *p)
{
  Elm *s = p->head;
  while (s != NULL)
  {
    printf("%d\n", s->x);
    s = s->next;
  }
}

/*
  p-ийн зааж буй List-с x тоог хайн олдсон хаягийг буцаана.
  Олдохгүй бол NULL хаяг буцаана.
 */
Elm *l_search(List *p, int x)
{
  Elm *s;
  int flag = 0;
  for (s = p->head; s != NULL; s = s->next)
  {
    if (s->x == x)
    {
      flag = 1;
      break;
    }
  }
  if (flag == 1)
    return s;
  else
    return NULL;
}
