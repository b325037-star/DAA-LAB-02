
#include <stdio.h>
#include <stdlib.h>

long long count1 = 0;
long long count2 = 0;

/* Normal merge */
void merge(int a[], int l, int m, int r)
{
    int i = l;
    int j = m + 1;
    int k = 0;

    int n = r - l + 1;
    int *temp = malloc(n * sizeof(int));

    while(i <= m && j <= r)
    {
        count1++;

        if(a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= m)
        temp[k++] = a[i++];

    while(j <= r)
        temp[k++] = a[j++];

    for(i = 0; i < n; i++)
        a[l + i] = temp[i];

    free(temp);
}


/* Normal merge sort */
void mergeSort(int a[], int l, int r)
{
    if(l >= r)
        return;

    int m = (l + r) / 2;

    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);

    merge(a, l, m, r);
}


/* Three way merge */
void merge3(int a[], int l, int m1, int m2, int r)
{
    int i = l;
    int j = m1 + 1;
    int k = m2 + 1;
    int p = 0;

    int n = r - l + 1;
    int *temp = malloc(n * sizeof(int));

    while(i <= m1 || j <= m2 || k <= r)
    {
        int x;

        if(i <= m1 &&
           (j > m2 || a[i] <= a[j]) &&
           (k > r || a[i] <= a[k]))
        {
            x = a[i++];
        }
        else if(j <= m2 &&
                (k > r || a[j] <= a[k]))
        {
            x = a[j++];
        }
        else
        {
            x = a[k++];
        }

        temp[p++] = x;
        count2++;
    }

    for(i = 0; i < n; i++)
        a[l + i] = temp[i];

    free(temp);
}


/* Modified merge sort */
void mergeSort3(int a[], int l, int r)
{
    if(l >= r)
        return;

    int n = r - l + 1;

    int m1 = l + n / 3 - 1;
    int m2 = l + 2 * n / 3 - 1;

    if(m1 < l)
    {
        return;
    }

    mergeSort3(a, l, m1);
    mergeSort3(a, m1 + 1, m2);
    mergeSort3(a, m2 + 1, r);

    merge3(a, l, m1, m2, r);
}


/* Put some values in array */
void makeArray(int a[], int n)
{
    for(int i = 0; i < n; i++)
        a[i] = n - i;
}


int main()
{
    FILE *fp;

    fp = fopen("merge_data.csv", "w");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    fprintf(fp, "n,MergeSort,ModifiedMergeSort\n");

    printf("n\tMerge Sort\tModified Merge Sort\n");
    printf("-----------------------------------------------\n");

    for(int n = 30; n <= 1500; n += 30)
    {
        int *a = malloc(n * sizeof(int));
        int *b = malloc(n * sizeof(int));

        makeArray(a, n);
        makeArray(b, n);

        count1 = 0;
        count2 = 0;

        mergeSort(a, 0, n - 1);
        mergeSort3(b, 0, n - 1);

        printf("%d\t%lld\t\t%lld\n",
               n, count1, count2);

        fprintf(fp, "%d,%lld,%lld\n",
                n, count1, count2);

        free(a);
        free(b);
    }

    fclose(fp);

    printf("\nData saved in merge_data.csv\n");
    printf("\nWorst-case running time:\n");
    printf("Normal Merge Sort       = Theta(n log n)\n");
    printf("Modified Merge Sort     = Theta(n log n)\n");

    return 0;
}