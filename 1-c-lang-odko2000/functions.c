#include "myinclude.h"

void read(int A[], int n)
{
        int i;
        for (i = 0; i < n; i++)
                scanf("%d", &A[i]);
}

void print(int A[], int n)
{
        int i;
        for (i = 0; i < n; i++)
                printf("%d ", A[i]);
        printf("\n");
}

int max(int A[], int n)
{
        int i, biggest = A[0];
        for (i = 0; i < n; i++)
        {
                if (A[i] > biggest)
                {
                        biggest = A[i];
                }
        }
        return biggest;
}

int min(int A[], int n)
{
        int i, smallest = A[0];
        for (i = 0; i < n; i++)
        {
                if (A[i] < smallest)
                {
                        smallest = A[i];
                }
        }
        return smallest;
}

void copy(int A[], int n, int B[])
{
        int i;
        for (i = 0; i < n; i++)
        {
                B[i] = A[i];
        }
}

int find(int A[], int n, int x)
{
        int i, index;
        for (i = 0; i < n; i++)
        {
                if (A[i] == x)
                {
                        index = i;
                        break;
                }
                else
                {
                        index = -1;
                }
        }
        return index;
}

int make_set(int A[], int n, int B[])
{
        int i, j, k = 0, temp;

        for (i = 1; i < n; i++)
        {
                temp = A[i];
                j = i - 1;

                while (j >= 0 && A[j] > temp)
                {
                        A[j + 1] = A[j];
                        j = j - 1;
                }
                A[j + 1] = temp;
        }

        for (i = 0; i < n; i++)
        {
                if (A[i] != A[i + 1])
                {
                        B[k] = A[i];
                        k++;
                }
        }
        return k;
}

int union_set(int A[], int n, int B[], int m)
{
        int i, j, k, l, temp, Merged[300];

        k = n + m;

        for (i = 0; i < n; i++)
        {
                Merged[i] = A[i];
        }
        for (l = 0, j = n; j < k && l < m; j++, l++)
        {
                Merged[j] = B[l];
        }

        for (i = 1; i < k; i++)
        {
                j = i;
                while (j > 0 && Merged[j - 1] > Merged[j])
                {
                        temp = Merged[j];
                        Merged[j] = Merged[j - 1];
                        Merged[j - 1] = temp;
                        j--;
                }
        }

        int p = 0;
        for (i = 0; i < k; i++)
        {
                if (Merged[i] != Merged[i + 1])
                {
                        A[p] = Merged[i];
                        p++;
                }
        }

        return p;
}

int intersection_set(int A[], int n, int B[], int m, int C[])
{
        int i, j, k = 0;
        for (i = 0; i < n; i++)
        {
                for (j = 0; j < m; j++)
                {
                        if (A[i] == B[j])
                        {
                                C[k] = A[i];
                                k++;
                        }
                }
        }
        return k;
}