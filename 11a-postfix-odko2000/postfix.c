#include "DS.h"

int is_space(int x)
{
	switch (x)
	{
	case ' ':
	case '\t':
	case '\n':
	case '\r':
	case '\f':
	case '\v':
	case '\0':
		return 1;
	default:
		return 0;
	}
	return 0;
}

int convert_to_int(const char s[])
{
	int len = strlen(s);
	int t = 0, i;
	for (i = 0; i < len; i++)
		t = t * 10 + s[i] - '0';
	return t;
}

void tokenize(const char s[], List *p_list)
{
	char tmp[EQUATION_LENGTH];
	int i, j, k, len;
	j = 0;
	struct Token x;
	len = strlen(s);
	for (i = 0; i <= len; i++)
	{
		if ('0' <= s[i] && s[i] <= '9')
		{
			tmp[j] = s[i];
			j++;
		}
		else
		{
			if (j != 0)
			{
				tmp[j] = '\0';
				j = 0;
				k = convert_to_int(tmp);
				x.flag = 1;
				x.val = k;
				l_push_back(p_list, x);
			}
			if (is_space(s[i]))
				continue;
			x.flag = 0;
			x.op = s[i];
			l_push_back(p_list, x);
		}
	}

	// l_print(p_list);
}

void convert_to_postfix(List *p_token, List *p_post)
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->len = 0;
	s->top = NULL;
	TokenElm *p = p_token->head;
	while (p != NULL)
	{
		if (p->x.flag == 0)
		{
			int op = p->x.op;
			if (s->len == 0 || op == 40)
				s_push(s, op);
			else
			{
				if (op == ')')
				{
					while (s->top->x != 40)
					{
						Token token;
						token.flag = 0;
						token.op = s->top->x;
						s_pop(s);
						l_push_back(p_post, token);
					};
					s_pop(s);
				}
				else
				{
					if (op == '+' || op == '-')
					{
						while (s->len > 0 && s->top->x != 40)
						{
							Token token;
							token.flag = 0;
							token.op = s->top->x;
							s_pop(s);
							l_push_back(p_post, token);
						}
						s_push(s, op);
					}
					else
					{
						if (s->top->x == '*' || s->top->x == '/' || s->top->x == '%')
						{
							Token token;
							token.flag = 0;
							token.op = s->top->x;
							s_pop(s);
							l_push_back(p_post, token);
						}
						s_push(s, op);
					}
				}
			}
		}
		else
			l_push_back(p_post, p->x);
		p = p->next;
	}
	while (s->len)
	{
		Token token;
		token.flag = 0;
		token.op = s->top->x;
		s_pop(s);
		l_push_back(p_post, token);
	}
}

int solve(List *p_post)
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->len = 0;
	s->top = NULL;
	int a, b, res = 0;
	TokenElm *p = p_post->head;

	while (p != NULL)
	{
		if (p->x.flag)
		{
			s_push(s, p->x.val);
		}
		else
		{
			a = s->top->x;
			s_pop(s);
			b = s->top->x;
			s_pop(s);
			if (p->x.op == '+')
				res = b + a;
			else if (p->x.op == '-')
				res = b - a;
			else if (p->x.op == '*')
				res = b * a;
			else if (p->x.op == '/')
				res = b / a;
			else if (p->x.op == '%')
				res = b % a;
			s_push(s, res);
		}
		p = p->next;
	}
	return res;
}
