#include "DS.h"
/*
  Графыг эхлүүлэх функц: `g` графын хөршүүдийг хадгалах жагсаалтан хүснэгтийг эхлүүлэх функц.
  Санах ойг бэлдэж, жагсаалтын `head`, `tail` утгуудад `NULL` онооно.
 */
void gr_init_graph(Graph *g, int n)
{
	int i;
	g->adj = (List *)malloc(sizeof(List) * (n + 1));
	g->n = n;
	for (i = 0; i <= n; i++)
	{
		g->adj[i].head = g->adj[i].tail = NULL;
		g->adj[i].len = 0;
	}
}

/*
  Гүний нэвтрэлтийн функц: `g` граф дээр гүний нэвтрэлт хийн холбоост бүрдлүүдийн талаарх
  даалгаварт заагдсан мэдээллийг хэвлэнэ.
 */

void gr_connected_components(Graph *g, int *cc)
{
	int i, n = g->n;
	int *p = (int *)malloc(sizeof(int) * (n + 1));
	for (i = 1; i <= n; i++)
	{
		if (p[i] == 0)
		{
			cc[0]++;
			p[i] = cc[0];
			List list;
			l_push_front(&list, i);
			while (list.len > 0)
			{
				int a = list.head->x;
				cc[p[a]]++;
				l_pop_front(&list);
				Elm *temp = g->adj[a].head;
				while (temp != NULL)
				{
					int b = temp->x;
					if (p[b] == 0)
					{
						p[b] = p[a];
						l_push_front(&list, b);
					}
					temp = temp->next;
				}
			}
		}
	}
}

/*
  Ирмэг нэмэх функц: `g` графын ирмэгүүдийг хадгалах `adj` жагсаалтан хүснэгтэд ирмэг нэмнэ.
  Уг граф нь чиглэлгүй граф тул `x`-с `y`, `y`-с `x` гэсэн хоёр ирмэгийг оруулна.
 */
void gr_add_edge(Graph *g, int x, int y)
{
	l_push_back(&g->adj[x], y);
	l_push_back(&g->adj[y], x);
}