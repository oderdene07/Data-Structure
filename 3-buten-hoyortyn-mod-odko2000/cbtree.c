#include "DS.h"

void cb_push(CBTree *p, int x)
{
        p->cb_arr[p->cb_len] = x;
        p->cb_len++;
}

int cb_left(const CBTree *p, int idx)
{
        if (2 * idx + 1 >= p->cb_len)
                return -1;
        else
                return 2 * idx + 1;
}

int cb_right(const CBTree *p, int idx)
{
        if (2 * idx + 2 >= p->cb_len)
                return -1;
        else
                return 2 * idx + 2;
}

int cb_search(const CBTree *p, int x)
{
        int i, count = 0;
        for (i = 0; i < p->cb_len; i++)
        {
                count = 0;
                if (p->cb_arr[i] == x)
                {
                        return i;
                        count++;
                }
        }
        if (count == 0)
                return -1;
}

void cb_ancestors(const CBTree *p, int idx)
{
        while (idx < p->cb_len && idx > 0)
        {
                printf("%d\n", p->cb_arr[(idx - 1) / 2]);
                idx = (idx - 1) / 2;
        }
}

int cb_height(const CBTree *p)
{
        int i = 0;
        int count = 0;
        while (i < p->cb_len)
        {
                i = 2 * i + 1;
                count++;
        }
        return count;
}

int cb_sibling(const CBTree *p, int idx)
{
        if (idx == p->cb_len - 1 && idx % 2 == 1)
        {
                return -1;
        }
        else
        {
                if (idx < p->cb_len && idx > 0)
                {
                        if (idx % 2 == 1)
                                return idx + 1;
                        else
                                return idx - 1;
                }
                else
                        return -1;
        }
}

void cb_preorder(const CBTree *p, int idx)
{
        if (idx < p->cb_len)
        {
                printf("%d\n", p->cb_arr[idx]);
                cb_preorder(p, 2 * idx + 1);
                cb_preorder(p, 2 * idx + 2);
        }
}

void cb_inorder(const CBTree *p, int idx)
{
        if (idx < p->cb_len)
        {
                cb_inorder(p, 2 * idx + 1);
                printf("%d\n", p->cb_arr[idx]);
                cb_inorder(p, 2 * idx + 2);
        }
}

void cb_postorder(const CBTree *p, int idx)
{
        if (idx < p->cb_len)
        {
                cb_postorder(p, 2 * idx + 1);
                cb_postorder(p, 2 * idx + 2);
                printf("%d\n", p->cb_arr[idx]);
        }
}

void cb_leaves(const CBTree *p, int idx)
{
        if (idx < p->cb_len)
        {
                if (2 * idx + 1 >= p->cb_len)
                {
                        printf("%d\n", p->cb_arr[idx]);
                }
                cb_leaves(p, 2 * idx + 1);
                cb_leaves(p, 2 * idx + 2);
        }
}

void cb_descendants(const CBTree *p, int idx)
{
        if (idx < p->cb_len)
        {
                cb_preorder(p, 2 * idx + 1);
                cb_preorder(p, 2 * idx + 2);
        }
}

int cb_size(const CBTree *p)
{
        return p->cb_len;
}

int cb_level(const CBTree *p, int x)
{
        int i = cb_search(p, x);
        int count = 0;
        if (i == -1)
        {
                return -1;
        }
        else
        {
                while (i > 0)
                {
                        if (i % 2 == 0)
                        {
                                i = i / 2 - 1;
                                count++;
                        }
                        else
                        {
                                i = i / 2;
                                count++;
                        }
                }
                return count;
        }
}