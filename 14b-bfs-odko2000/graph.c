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
  Төвшний нэвтрэлтийн функц: `g` граф дээр `s` оройгоос эхлэн төвшний нэвтрэлтийг хийнэ.
  `pi`: Төвшний нэвтрэлт хийсний дараа `pi[u]` нь `u` оройд ямар оройгоос ирснийг хадгална.
 */
void gr_bfs(Graph *g, int s, int pi[])
{
	pi[s] = -1;
	Queue queue;
	queue.len = 0;
	queue.head = queue.tail = NULL;
	q_push(&queue, s);
	while (queue.len)
	{
		int i, k = queue.head->x;
		q_pop(&queue);
		Elm *temp;
		for (temp = g->adj[k].head; temp != NULL; temp = temp->next)
		{
			int u = temp->x;
			if (!pi[u])
			{
				pi[u] = k;
				q_push(&queue, u);
			}
		}
	}
}

/*
  Замын оройнуудыг хэвлэх функц: `pi` хүснэгтээс `s`, `t` орой хоорондын замын мэдээллийг хэвлэнэ.
  Хамгийн эхний мөрөнд замын уртыг, дараагийн мөрөнд `s` оройгоос эхлэн ямар оройгоор дамжиж
  очиж байгаа оройнуудыг 1 хоосон зайгаар тусгаарлан хэвлэнэ.
  Хэрэв зам байхгүй бол `-1` гэсэн ганц утга хэвлэнэ.
 */
void gr_print_path(int pi[], int s, int t)
{
	Stack st;
	st.len = 0;
	st.top = NULL;
	int u = t;
	if (!pi[u])
		printf("%d\n", -1);
	else
	{
		for (int v = u; v != s; v = pi[v])
			s_push(&st, v);
		s_push(&st, s);
		printf("%d\n", st.len);
		s_print(&st);
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
