
#include <stdio.h>
#include <stdlib.h>

long long count = 0;


/* Merge two sorted arrays */
int* merge(int *a, int n1, int *b, int n2)
{
    int i = 0;
    int j = 0;
    int k = 0;

    int *c = malloc((n1 + n2) * sizeof(int));

    while(i < n1 && j < n2)
    {
        count++;

        if(a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }

    while(i < n1)
        c[k++] = a[i++];

    while(j < n2)
        c[k++] = b[j++];

    return c;
}


/* Method 1:
   Merge first two, then with third, etc. */
void method1(int **arr, int k, int n)
{
    int *result = arr[0];
    int size = n;

    for(int i = 1; i < k; i++)
    {
        int *temp;

        temp = merge(result, size, arr[i], n);

        if(i > 1)
            free(result);

        result = temp;
        size = size + n;
    }

    free(result);
}


/* Method 2:
   Merge arrays in pairs */
void method2(int **arr, int k, int n)
{
    int number = k;
    int size = n;

    while(number > 1)
    {
        int newNumber = 0;

        for(int i = 0; i < number; i += 2)
        {
            if(i + 1 < number)
            {
                int *temp;

                temp = merge(arr[i], size,
                             arr[i + 1], size);

                free(arr[i]);
                free(arr[i + 1]);

                arr[newNumber] = temp;
                newNumber++;
            }
            else
            {
                arr[newNumber] = arr[i];
                newNumber++;
            }
        }

        number = newNumber;
        size = size * 2;
    }

    free(arr[0]);
}


/* Create sorted arrays */
void createArrays(int **arr, int k, int n)
{
    for(int i = 0; i < k; i++)
    {
        arr[i] = malloc(n * sizeof(int));

        for(int j = 0; j < n; j++)
        {
            arr[i][j] = i * n + j;
        }
    }
}


int main()
{
    int n, k;

    printf("Enter number of elements in each array: ");
    scanf("%d", &n);

    printf("Enter number of arrays: ");
    scanf("%d", &k);

    if(k < 2)
    {
        printf("Number of arrays should be at least 2.\n");
        return 0;
    }


    /* Create two copies of the same input */

    int **a = malloc(k * sizeof(int *));
    int **b = malloc(k * sizeof(int *));

    createArrays(a, k, n);
    createArrays(b, k, n);


    /* Method 1 */

    count = 0;

    method1(a, k, n);

    long long method1_count = count;


    /* Method 2 */

    count = 0;

    method2(b, k, n);

    long long method2_count = count;


    /* Display result */

    printf("\n");
    printf("====================================\n");
    printf("          RESULTS\n");
    printf("====================================\n");

    printf("n = %d\n", n);
    printf("k = %d\n", k);

    printf("\nMethod 1 comparisons = %lld\n",
           method1_count);

    printf("Method 2 comparisons = %lld\n",
           method2_count);

    printf("\nTheoretical complexity:\n");

    printf("Method 1 = Theta(n * k^2)\n");
    printf("Method 2 = Theta(n * k * log k)\n");

    printf("\nMethod 2 is more efficient for large k.\n");


    free(a);
    free(b);

    return 0;
}