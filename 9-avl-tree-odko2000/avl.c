#include "DS.h"

int max(int a, int b)
{
        return (a > b) ? a : b;
}
Elm *newNode(int x)
{
        Elm *p = (Elm *)malloc(sizeof(Elm));
        p->x = x;
        p->height = p->len = 1;
        p->L = p->R = NULL;
        return p;
}
int size(Elm *p)
{
        if (p == NULL)
                return 0;
        else
                return (size(p->L) + 1 + size(p->R));
}
int height(Elm *p)
{
        if (p == NULL)
                return 0;
        return p->height;
}
int checkProperty(Elm *p)
{
        if (p == NULL)
                return 0;
        return height(p->L) - height(p->R);
}

Elm *rightRotate(Elm *y)
{
        Elm *x = y->L;
        Elm *T2 = x->R;

        x->R = y;
        y->L = T2;

        y->height = max(height(y->L), height(y->R)) + 1;
        x->height = max(height(x->L), height(x->R)) + 1;

        x->len = size(x);
        y->len = size(y);

        return x;
}

Elm *leftRotate(Elm *x)
{
        Elm *y = x->R;
        Elm *T2 = y->L;

        y->L = x;
        x->R = T2;

        x->height = max(height(x->L), height(x->R)) + 1;
        y->height = max(height(y->L), height(y->R)) + 1;

        x->len = size(x);
        y->len = size(y);

        return y;
}
Elm *insert(Elm *p, int x)
{
        if (p == NULL)
                return newNode(x);

        if (x < p->x)
                p->L = insert(p->L, x);

        else if (x > p->x)
                p->R = insert(p->R, x);

        else
                return p;

        p->height = 1 + max(height(p->L), height(p->R));
        p->len++;

        int property = checkProperty(p);

        //LL case
        if (property > 1 && x < p->L->x)
                return rightRotate(p);

        //LR case
        if (property > 1 && x > p->L->x)
        {
                p->L = leftRotate(p->L);
                return rightRotate(p);
        }

        //RR case
        if (property < -1 && x > p->R->x)
                return leftRotate(p);

        //RL case
        if (property < -1 && x < p->R->x)
        {
                p->R = rightRotate(p->R);
                return leftRotate(p);
        }
        return p;
}

void avl_put(AVL *ptree, int x)
{
        if (ptree->root == NULL)
        {
                ptree->root = newNode(x);
                return;
        }
        ptree->root = insert(ptree->root, x);
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

Elm *avl_get(const AVL *ptree, int x)
{
        if (ptree->root == NULL)
                return NULL;
        get(ptree->root, x);
}

Elm *del(Elm *p, int x)
{
        if (p == NULL)
                return p;

        if (x < p->x)
                p->L = del(p->L, x);

        else if (x > p->x)
                p->R = del(p->R, x);

        else
        {
                Elm *temp;
                if (p->L == NULL)
                {
                        temp = p->R;
                        return temp;
                }
                else if (p->R == NULL)
                {
                        temp = p->L;
                        return temp;
                }

                temp = p->R;
                while (temp->L != NULL)
                        temp = temp->L;

                p->x = temp->x;

                p->R = del(p->R, temp->x);
        }

        p->height = 1 + max(height(p->L), height(p->R));
        p->len--;

        if (p == NULL)
                return p;

        int property = checkProperty(p);

        if (property > 1 && checkProperty(p->L) >= 0)
                return rightRotate(p);

        if (property > 1 && checkProperty(p->L) < 0)
        {
                p->L = leftRotate(p->L);
                return rightRotate(p);
        }

        if (property < -1 && checkProperty(p->R) <= 0)
                return leftRotate(p);

        if (property < -1 && checkProperty(p->R) > 0)
        {
                p->R = rightRotate(p->R);
                return leftRotate(p);
        }

        return p;
}

void avl_del(AVL *ptree, int x)
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
        p->len = size(p);
        return p;
}

int avl_delMin(AVL *ptree)
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
void avl_inorder(const AVL *ptree)
{
        inorder(ptree->root);
}
int avl_size(const AVL *ptree, int x)
{
        Elm *p = avl_get(ptree, x);
        return p == NULL ? -1 : p->len;
}

int avl_height(const AVL *ptree, int x)
{
        Elm *p = avl_get(ptree, x);
        return p == NULL ? -1 : p->height;
}
