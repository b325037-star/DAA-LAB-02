
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Normal merge */
void merge(int a[], int low, int mid, int high)
{
    
    int i = low;
    int j = mid + 1;
    int k = 0;

    int n = high - low + 1;
    int *temp = malloc(n * sizeof(int));

    while(i <= mid && j <= high)
    {
        if(a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= mid)
        temp[k++] = a[i++];

    while(j <= high)
        temp[k++] = a[j++];

    for(i = 0; i < n; i++)
        a[low + i] = temp[i];

    free(temp);
}


/* Normal merge sort */
void mergeSort(int a[], int low, int high)
{
    if(low >= high)
        return;

    int mid = (low + high) / 2;

    mergeSort(a, low, mid);
    mergeSort(a, mid + 1, high);

    merge(a, low, mid, high);
}


/* Three-way merge */
void mergeThree(int a[], int low, int mid1, int mid2, int high)
{
    int i = low;
    int j = mid1 + 1;
    int k = mid2 + 1;
    int p = 0;

    int n = high - low + 1;
    int *temp = malloc(n * sizeof(int));

    while(i <= mid1 || j <= mid2 || k <= high)
    {
        if(i <= mid1 &&
           (j > mid2 || a[i] <= a[j]) &&
           (k > high || a[i] <= a[k]))
        {
            temp[p++] = a[i++];
        }
        else if(j <= mid2 &&
                (k > high || a[j] <= a[k]))
        {
            temp[p++] = a[j++];
        }
        else
        {
            temp[p++] = a[k++];
        }
    }

    for(i = 0; i < n; i++)
        a[low + i] = temp[i];

    free(temp);
}


/* Modified three-way merge sort */
void mergeSortThree(int a[], int low, int high)
{
    
    if(low >= high)
        return;

    int n = high - low + 1;

    int mid1 = low + n / 3 - 1;
    int mid2 = low + 2 * n / 3 - 1;

    /* For very small arrays */
    if(mid1 < low)
        return;

    mergeSortThree(a, low, mid1);
    mergeSortThree(a, mid1 + 1, mid2);
    mergeSortThree(a, mid2 + 1, high);

    mergeThree(a, low, mid1, mid2, high);
}

   int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    int *b = malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    printf("\nOriginal Array:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);


    /* Normal Merge Sort */
    clock_t start = clock();

    mergeSort(a, 0, n - 1);

    clock_t end = clock();

    double time1 = (double)(end - start) / CLOCKS_PER_SEC;


    /* Modified 3-Way Merge Sort */
    start = clock();

    mergeSortThree(b, 0, n - 1);

    end = clock();

    double time2 = (double)(end - start) / CLOCKS_PER_SEC;


    /* Print sorted arrays */

    printf("\n\nSorted using Normal Merge Sort:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);


    printf("\n\nSorted using Modified 3-Way Merge Sort:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", b[i]);


    /* Print time */

    printf("\n\nExecution Time:\n");

    printf("Normal Merge Sort       = %f seconds\n", time1);

    printf("Modified 3-Way Merge Sort = %f seconds\n", time2);


    free(a);
    free(b);

    return 0;
}