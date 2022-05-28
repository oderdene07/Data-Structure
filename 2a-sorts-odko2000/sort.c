#include "sort.h"
void read(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
            scanf("%d", &a[i]);
}

void print(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void insertion_sort(int a[], int n)
{ 
    int i, j, temp;

    for(i = 1; i < n; i++){
		temp = a[i];
		for(j = i - 1; j >= 0 && a[j] > temp; j--){
			a[j + 1] = a[j];
			a[j] = temp; 
		}
    }
}

void selection_sort(int a[], int n)
{
	int i, k, j, temp;
	
	for(i = 0; i < n; i++){
		k = i;
		for(j = i + 1; j < n; j++){
			if(a[j] < a[k]){
				k = j;
			}
		}
		temp = a[i];
		a[i] = a[k];
		a[k] = temp;
	}  
}

void bubble_sort(int a[], int n)
{
	int i, j, temp;
	
	for(i = n ; i > 0; i--){
		for (j = 0; j < i - 1; j++){
			if(a[j] > a[j + 1]){
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}
