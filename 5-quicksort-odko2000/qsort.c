#include "my_qsort.h"

#ifndef CUTOFF
#define CUTOFF 10
#endif

static int init_seed = 0;

static void insertion_sort(int a[], int lo, int hi)
{
        int i, temp, j;
        for (i = lo + 1; i <= hi; i++)
        {
                temp = a[i];
                j = i - 1;
                while (j >= lo && a[j] > temp)
                {
                        a[j + 1] = a[j];
                        j = j - 1;
                }
                a[j + 1] = temp;
        }
}

static void swap(int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

static void random_shuffle(int a[], int lo, int hi)
{
        if (init_seed == 0)
        {
                srand(time(NULL));
                init_seed = 1;
        }
        int i, j;
        for (i = lo; i <= hi; i++)
        {
                j = rand() % (hi - lo) + lo;
                swap(&a[i], &a[j]);
        }
}

static void _single_pivot_qsort(int a[], int lo, int hi)
{
        int i, j, pivot;

        if (hi - lo <= CUTOFF)
        {
                insertion_sort(a, lo, hi);
        }
        if (lo >= hi)
                return;

        pivot = lo;
        i = lo;
        j = hi;

        while (i < j)
        {
                while (a[i] <= a[pivot] && i < hi)
                        i++;
                while (a[j] > a[pivot])
                        j--;
                if (i < j)
                {
                        swap(&a[i], &a[j]);
                }
        }
        swap(&a[pivot], &a[j]);
        _single_pivot_qsort(a, lo, j - 1);
        _single_pivot_qsort(a, j + 1, hi);
}

void single_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _single_pivot_qsort(a, lo, hi);
}

static void _dual_pivot_qsort(int a[], int lo, int hi)
{
        if (hi - lo <= CUTOFF)
        {
                insertion_sort(a, lo, hi);
        }
        if (lo >= hi)
                return;

        if (a[lo] > a[hi])
                swap(&a[lo], &a[hi]);

        int pivot1 = a[lo];
        int pivot2 = a[hi];
        int lt = lo + 1;
        int gt = hi - 1;
        int i = lt;
        while (i <= gt)
        {
                if (a[i] < pivot1)
                {
                        swap(&a[i], &a[lt]);
                        ++lt;
                }
                else if (a[i] >= pivot2)
                {
                        while (a[gt] > pivot2 && i < gt)
                                --gt;
                        swap(&a[i], &a[gt]);
                        --gt;
                        if (a[i] < pivot1)
                        {
                                swap(&a[i], &a[lt]);
                                ++lt;
                        }
                }
                ++i;
        }
        --lt;
        ++gt;
        swap(&a[lo], &a[lt]);
        swap(&a[hi], &a[gt]);

        _dual_pivot_qsort(a, lo, lt - 1);
        _dual_pivot_qsort(a, lt + 1, gt - 1);
        _dual_pivot_qsort(a, gt + 1, hi);
}

void dual_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _dual_pivot_qsort(a, lo, hi);
}
