#include "sort.h"

#define CUTOFF 10

int nereer(const Student *a, const Student *b)
{
  if (strcmp(a->name, b->name) < 0)
    return 1;
  else if (strcmp(a->name, b->name) == 0)
    return 0;
  else
    return -1;
}

int nasaar(const Student *a, const Student *b)
{
  if (a->age < b->age)
    return 1;
  else if (a->age == b->age)
    return 0;
  else
    return -1;
}

int golchoor(const Student *a, const Student *b)
{
  if (a->gpa < b->gpa)
    return 1;
  else if (a->gpa == b->gpa)
    return 0;
  else
    return -1;
}

void insertion_sort(Student a[],
                    int lo, int hi,
                    int (*less)(const Student *, const Student *))
{
  int i, j;
  Student temp;
  for (i = lo; i <= hi; i++)
  {
    j = i;
    while (j > lo && less(a + j - 1, a + j) < 0)
    {
      temp = a[j - 1];
      a[j - 1] = a[j];
      a[j] = temp;
      j--;
    }
  }
}

void merge(Student a[],
           Student aux[],
           int lo,
           int mid,
           int hi,
           int (*less)(const Student *, const Student *))
{
  int k;
  for (k = lo; k <= hi; k++)
  {
    aux[k] = a[k];
  }
  int i = lo, j = mid + 1;
  for (k = lo; k <= hi; k++)
  {
    if (i > mid)
      a[k] = aux[j++];
    else if (j > hi)
      a[k] = aux[i++];
    else if (less(aux + j, aux + i) > 0)
      a[k] = aux[j++];
    else
      a[k] = aux[i++];
  }
}

void mergesort(Student a[],
               Student aux[],
               int lo,
               int hi,
               int (*less)(const Student *, const Student *))
{
  if (hi - lo <= CUTOFF)
    insertion_sort(a, lo, hi, less);
  if (hi <= lo)
  {
    return;
  }
  int mid = lo + (hi - lo) / 2;
  mergesort(a, aux, lo, mid, less);
  mergesort(a, aux, mid + 1, hi, less);
  merge(a, aux, lo, mid, hi, less);
}