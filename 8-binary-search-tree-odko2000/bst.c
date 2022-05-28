#include "DS.h"

Elm *newNode(int x)
{
        Elm *p = (Elm *)malloc(sizeof(Elm));
        p->x = x;
        p->height = p->len = 1;
        p->L = p->R = NULL;
        return p;
}

void insert(Elm *p, int x)
{
        if (p == NULL)
        {
                p = (Elm *)malloc(sizeof(Elm));
                p->x = x;
                p->L = p->R = NULL;
        }
        if (p->x > x)
        {
                if (p->L == NULL)
                {
                        p->L = newNode(x);
                }
                else
                        insert(p->L, x);
        }
        else
        {
                if (p->R == NULL)
                {
                        p->R = newNode(x);
                }
                else
                        insert(p->R, x);
        }

        int lc = p->L == NULL ? 1 : p->L->height + 1;
        int rc = p->R == NULL ? 1 : p->R->height + 1;
        p->height = lc > rc ? lc : rc;
        p->len++;
}

void bs_put(BST *ptree, int x)
{
        if (ptree->root == NULL)
        {
                ptree->root = newNode(x);
                return;
        }
        insert(ptree->root, x);
}

Elm *get(Elm *p, int x)
{
        if (p == NULL || x == p->x)
                return p;
        if (x > p->x)
                return get(p->R, x);
        else
                return get(p->L, x);
}

Elm *bs_get(const BST *ptree, int x)
{
        get(ptree->root, x);
}

Elm *del(Elm *p, int x)
{
        Elm *temp_Elm;
        if (p == NULL)
                return p;

        if (x < p->x)
                p->L = del(p->L, x);

        else if (x > p->x)
                p->R = del(p->R, x);
        else
        {
                if (p->L == NULL)
                {
                        temp_Elm = p->R;
                        return temp_Elm;
                }
                else if (p->R == NULL)
                {
                        temp_Elm = p->L;
                        return temp_Elm;
                }
                temp_Elm = p->R;
                while (temp_Elm->L != NULL)
                        temp_Elm = temp_Elm->L;

                p->x = temp_Elm->x;
                p->R = del(p->R, p->x);
        }
        int lc = p->L == NULL ? 1 : p->L->height + 1;
        int rc = p->R == NULL ? 1 : p->R->height + 1;
        p->height = lc > rc ? lc : rc;
        p->len--;
        return p;
}

void bs_del(BST *ptree, int x)
{
        ptree->root = del(ptree->root, x);
}

int min(Elm *p)
{
        Elm *temp = p;
        while (temp->L != NULL)
        {
                temp = temp->L;
        }
        return temp->x;
}

Elm *delMin(Elm *p)
{
        if (p->L == NULL)
                return p->R;
        p->L = delMin(p->L);
        p->len--;
        return p;
}

int bs_delMin(BST *ptree)
{
        int temp = min(ptree->root);
        ptree->root = delMin(ptree->root);
        return temp;
}

void inorder(Elm *p)
{
        if (p == NULL)
                return;
        inorder(p->L);
        printf("%d %d %d\n", p->x, p->len, p->height);
        inorder(p->R);
}
void bs_inorder(const BST *ptree)
{
        inorder(ptree->root);
}

int low(Elm *p, int x)
{
        if (p == NULL)
                return 0;
        if (p->x > x)
                return low(p->L, x);
        int left = p->L == NULL ? 1 : p->L->len + 1;
        return left + low(p->R, x);
}

int bs_rank(const BST *ptree, int x)
{
        if (ptree->root != NULL)
                return low(ptree->root, x);
}

int bs_size(const BST *ptree, int x)
{
        Elm *p = bs_get(ptree, x);
        return p == NULL ? -1 : p->len;
}

Elm *floor_Elm(Elm *p, int x)
{
        if (p == NULL)
                return NULL;
        if (p->x > x)
                return floor_Elm(p->L, x);
        else if (p->x == x)
                return p;
        else
        {
                Elm *temp = floor_Elm(p->R, x);
                if (temp == NULL)
                        return p;
                else
                        return temp;
        }
}

Elm *bs_floor(const BST *ptree, int x)
{
        if (ptree->root == NULL)
                return NULL;
        else
                return floor_Elm(ptree->root, x);
}
Elm *ceiling(Elm *p, int x)
{
        if (p == NULL)
                return NULL;
        if (p->x < x)
                return ceiling(p->R, x);
        else if (p->x == x)
                return p;
        else
        {
                Elm *temp = ceiling(p->L, x);
                if (temp == NULL)
                        return p;
                else
                        return temp;
        }
}

Elm *bs_ceiling(const BST *ptree, int x)
{
        if (ptree->root == NULL)
                return NULL;
        else
                return ceiling(ptree->root, x);
}

int bs_height(const BST *ptree, int x)
{
        Elm *p = bs_get(ptree, x);
        return p == NULL ? -1 : p->height;
}
