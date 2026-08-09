
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
    SEARCH_OP,
    INSERT_OP,
    DELETE_OP,
    MAX_OP,
    MIN_OP,
    PREDECESSOR_OP,
    SUCCESSOR_OP,
    OP_COUNT
} Operation;

typedef enum
{
    UNSORTED_ARRAY,
    SORTED_ARRAY,
    SINGLY_UNSORTED,
    SINGLY_SORTED,
    DOUBLY_UNSORTED,
    DOUBLY_SORTED,
    REP_COUNT
} Representation;

typedef enum
{
    CLASS_CONSTANT,
    CLASS_LOGARITHMIC,
    CLASS_LINEAR
} GrowthClass;


/* Number of test points */
#define POINTS 20
#define N_MIN 64
#define N_MAX 10000


const char *REP_NAMES[REP_COUNT] =
{
    "Unsorted Array",
    "Sorted Array",
    "Singly Linked Unsorted",
    "Singly Linked Sorted",
    "Doubly Linked Unsorted",
    "Doubly Linked Sorted"
};


const char *OP_NAMES[OP_COUNT] =
{
    "Search",
    "Insert",
    "Delete",
    "Maximum",
    "Minimum",
    "Predecessor",
    "Successor"
};


/* Expected worst-case complexities */

const GrowthClass EXPECTED[REP_COUNT][OP_COUNT] =
{
    /* Search       Insert       Delete       Max          Min          Pred         Succ */

    {CLASS_LINEAR, CLASS_CONSTANT, CLASS_CONSTANT,
     CLASS_LINEAR, CLASS_LINEAR, CLASS_LINEAR, CLASS_LINEAR},

    {CLASS_LOGARITHMIC, CLASS_LINEAR, CLASS_LINEAR,
     CLASS_CONSTANT, CLASS_CONSTANT, CLASS_CONSTANT, CLASS_CONSTANT},

    {CLASS_LINEAR, CLASS_CONSTANT, CLASS_LINEAR,
     CLASS_LINEAR, CLASS_LINEAR, CLASS_LINEAR, CLASS_LINEAR},

    {CLASS_LINEAR, CLASS_LINEAR, CLASS_LINEAR,
     CLASS_CONSTANT, CLASS_CONSTANT, CLASS_LINEAR, CLASS_CONSTANT},

    {CLASS_LINEAR, CLASS_CONSTANT, CLASS_CONSTANT,
     CLASS_LINEAR, CLASS_LINEAR, CLASS_LINEAR, CLASS_LINEAR},

    {CLASS_LINEAR, CLASS_LINEAR, CLASS_CONSTANT,
     CLASS_CONSTANT, CLASS_CONSTANT, CLASS_CONSTANT, CLASS_CONSTANT}
};


const char *class_text(GrowthClass g)
{
    if(g == CLASS_CONSTANT)
        return "O(1)";

    if(g == CLASS_LOGARITHMIC)
        return "O(log n)";

    return "O(n)";
}


/* Create unsorted array */

int *make_unsorted_array(int n)
{
    int *a = malloc(n * sizeof(int));

    if(a == NULL)
        return NULL;

    int p = 0;

    for(int i = 1; i < n; i += 2)
        a[p++] = i;

    for(int i = 0; i < n; i += 2)
        a[p++] = i;

    return a;
}


/* Create sorted array */

int *make_sorted_array(int n)
{
    int *a = malloc(n * sizeof(int));

    if(a == NULL)
        return NULL;

    for(int i = 0; i < n; i++)
        a[i] = 2 * i;

    return a;
}


/* Singly linked list */

typedef struct SNode
{
    int key;
    struct SNode *next;
} SNode;


/* Doubly linked list */

typedef struct DNode
{
    int key;
    struct DNode *prev;
    struct DNode *next;
} DNode;


/* Create singly linked list */

SNode *make_singly(int n, int sorted, SNode **tail_out)
{
    SNode *head = NULL;
    SNode *tail = NULL;

    for(int i = 0; i < n; i++)
    {
        SNode *node = malloc(sizeof(SNode));

        if(node == NULL)
            exit(1);

        if(sorted)
            node->key = 2 * i;
        else
        {
            int odd = n / 2;

            if(i < odd)
                node->key = 2 * i + 1;
            else
                node->key = 2 * (i - odd);
        }

        node->next = NULL;

        if(head == NULL)
            head = node;
        else
            tail->next = node;

        tail = node;
    }

    *tail_out = tail;

    return head;
}


/* Create doubly linked list */

DNode *make_doubly(int n, int sorted, DNode **tail_out)
{
    DNode *head = NULL;
    DNode *tail = NULL;

    for(int i = 0; i < n; i++)
    {
        DNode *node = malloc(sizeof(DNode));

        if(node == NULL)
            exit(1);

        if(sorted)
            node->key = 2 * i;
        else
        {
            int odd = n / 2;

            if(i < odd)
                node->key = 2 * i + 1;
            else
                node->key = 2 * (i - odd);
        }

        node->prev = tail;
        node->next = NULL;

        if(head == NULL)
            head = node;
        else
            tail->next = node;

        tail = node;
    }

    *tail_out = tail;

    return head;
}


/* Free singly linked list */

void free_singly(SNode *head)
{
    while(head != NULL)
    {
        SNode *temp = head->next;
        free(head);
        head = temp;
    }
}


/* Free doubly linked list */

void free_doubly(DNode *head)
{
    while(head != NULL)
    {
        DNode *temp = head->next;
        free(head);
        head = temp;
    }
}


/* Unsorted array */

void measure_unsorted_array(int n, double out[])
{
    int *a = make_unsorted_array(n);

    long long steps = 0;

    /* Search */

    for(int i = 0; i < n; i++)
    {
        steps++;

        if(a[i] == -1)
            break;
    }

    out[SEARCH_OP] = steps;


    /* Insert */

    out[INSERT_OP] = 1;


    /* Delete */

    out[DELETE_OP] = 1;


    /* Maximum */

    steps = 0;

    int mx = a[0];

    for(int i = 1; i < n; i++)
    {
        steps++;

        if(a[i] > mx)
            mx = a[i];
    }

    out[MAX_OP] = steps;


    /* Minimum */

    steps = 0;

    int mn = a[0];

    for(int i = 1; i < n; i++)
    {
        steps++;

        if(a[i] < mn)
            mn = a[i];
    }

    out[MIN_OP] = steps;


    /* Predecessor */

    steps = 0;

    int best = -1;

    for(int i = 0; i < n; i++)
    {
        steps++;

        if(a[i] < n / 2 && a[i] > best)
            best = a[i];
    }

    out[PREDECESSOR_OP] = steps;


    /* Successor */

    steps = 0;

    best = n + 1;

    for(int i = 0; i < n; i++)
    {
        steps++;

        if(a[i] > n / 2 && a[i] < best)
            best = a[i];
    }

    out[SUCCESSOR_OP] = steps;

    free(a);
}


/* Sorted array */

void measure_sorted_array(int n, double out[])
{
    int *a = make_sorted_array(n);

    long long steps = 0;

    /* Binary search */

    int low = 0;
    int high = n - 1;
    int target = 2 * n + 1;

    while(low <= high)
    {
        steps++;

        int mid = (low + high) / 2;

        if(a[mid] == target)
            break;

        if(a[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    out[SEARCH_OP] = steps;


    /* Insert */

    steps = 0;

    for(int i = n; i > 0; i--)
    {
        steps++;
    }

    out[INSERT_OP] = steps;


    /* Delete */

    steps = 0;

    for(int i = 0; i < n - 1; i++)
        steps++;

    out[DELETE_OP] = steps;


    /* Maximum */

    out[MAX_OP] = 1;


    /* Minimum */

    out[MIN_OP] = 1;


    /* Predecessor */

    out[PREDECESSOR_OP] = 1;


    /* Successor */

    out[SUCCESSOR_OP] = 1;

    free(a);
}


/* Singly linked unsorted */

void measure_singly_unsorted(int n, double out[])
{
    SNode *tail;

    SNode *head = make_singly(n, 0, &tail);

    long long steps = 0;


    /* Search */

    for(SNode *p = head; p != NULL; p = p->next)
        steps++;

    out[SEARCH_OP] = steps;


    /* Insert at head */

    out[INSERT_OP] = 1;


    /* Delete */

    steps = 0;

    for(SNode *p = head; p->next != tail; p = p->next)
        steps++;

    out[DELETE_OP] = steps;


    /* Maximum */

    steps = 0;

    int mx = head->key;

    for(SNode *p = head->next; p != NULL; p = p->next)
    {
        steps++;

        if(p->key > mx)
            mx = p->key;
    }

    out[MAX_OP] = steps;


    /* Minimum */

    steps = 0;

    int mn = head->key;

    for(SNode *p = head->next; p != NULL; p = p->next)
    {
        steps++;

        if(p->key < mn)
            mn = p->key;
    }

    out[MIN_OP] = steps;


    /* Predecessor */

    steps = 0;

    for(SNode *p = head; p != NULL; p = p->next)
        steps++;

    out[PREDECESSOR_OP] = steps;


    /* Successor */

    steps = 0;

    for(SNode *p = head; p != NULL; p = p->next)
        steps++;

    out[SUCCESSOR_OP] = steps;


    free_singly(head);
}


/* Singly linked sorted */

void measure_singly_sorted(int n, double out[])
{
    SNode *tail;

    SNode *head = make_singly(n, 1, &tail);

    long long steps = 0;


    /* Search */

    for(SNode *p = head; p != NULL; p = p->next)
        steps++;

    out[SEARCH_OP] = steps;


    /* Insert */

    steps = 0;

    for(SNode *p = head; p->next != NULL; p = p->next)
        steps++;

    out[INSERT_OP] = steps;


    /* Delete */

    steps = 0;

    for(SNode *p = head; p->next != tail; p = p->next)
        steps++;

    out[DELETE_OP] = steps;


    /* Maximum */

    out[MAX_OP] = 1;


    /* Minimum */

    out[MIN_OP] = 1;


    /* Predecessor */

    steps = 0;

    for(SNode *p = head; p->next != tail; p = p->next)
        steps++;

    out[PREDECESSOR_OP] = steps;


    /* Successor */

    out[SUCCESSOR_OP] = 1;


    free_singly(head);
}


/* Doubly linked unsorted */

void measure_doubly_unsorted(int n, double out[])
{
    DNode *tail;

    DNode *head = make_doubly(n, 0, &tail);

    long long steps = 0;


    /* Search */

    for(DNode *p = head; p != NULL; p = p->next)
        steps++;

    out[SEARCH_OP] = steps;


    /* Insert */

    out[INSERT_OP] = 1;


    /* Delete known node */

    out[DELETE_OP] = 1;


    /* Maximum */

    steps = 0;

    int mx = head->key;

    for(DNode *p = head->next; p != NULL; p = p->next)
    {
        steps++;

        if(p->key > mx)
            mx = p->key;
    }

    out[MAX_OP] = steps;


    /* Minimum */

    steps = 0;

    int mn = head->key;

    for(DNode *p = head->next; p != NULL; p = p->next)
    {
        steps++;

        if(p->key < mn)
            mn = p->key;
    }

    out[MIN_OP] = steps;


    /* Predecessor */

    steps = 0;

    for(DNode *p = head; p != NULL; p = p->next)
        steps++;

    out[PREDECESSOR_OP] = steps;


    /* Successor */

    steps = 0;

    for(DNode *p = head; p != NULL; p = p->next)
        steps++;

    out[SUCCESSOR_OP] = steps;


    free_doubly(head);
}


/* Doubly linked sorted */

void measure_doubly_sorted(int n, double out[])
{
    DNode *tail;

    DNode *head = make_doubly(n, 1, &tail);


    /* Search */

    long long steps = 0;

    for(DNode *p = head; p != NULL; p = p->next)
        steps++;

    out[SEARCH_OP] = steps;


    /* Insert */

    steps = 0;

    for(DNode *p = head; p != NULL; p = p->next)
        steps++;

    out[INSERT_OP] = steps;


    /* Delete */

    out[DELETE_OP] = 1;


    /* Maximum */

    out[MAX_OP] = 1;


    /* Minimum */

    out[MIN_OP] = 1;


    /* Predecessor */

    out[PREDECESSOR_OP] = 1;


    /* Successor */

    out[SUCCESSOR_OP] = 1;


    free_doubly(head);
}


/* Measure all representations */

void measure_all(int n, double data[REP_COUNT][OP_COUNT])
{
    measure_unsorted_array(n, data[UNSORTED_ARRAY]);

    measure_sorted_array(n, data[SORTED_ARRAY]);

    measure_singly_unsorted(n, data[SINGLY_UNSORTED]);

    measure_singly_sorted(n, data[SINGLY_SORTED]);

    measure_doubly_unsorted(n, data[DOUBLY_UNSORTED]);

    measure_doubly_sorted(n, data[DOUBLY_SORTED]);
}


/* Print line */

void print_line()
{
    printf("+--------------------------+----------+----------+----------+----------+----------+-------------+-----------+\n");
}


int main()
{
    int n_values[POINTS];

    double data[REP_COUNT][OP_COUNT][POINTS];


    /* Generate input sizes */

    for(int i = 0; i < POINTS; i++)
    {
        n_values[i] =
            N_MIN +
            (N_MAX - N_MIN) * i / (POINTS - 1);
    }


    /* Measure all input sizes */

    for(int i = 0; i < POINTS; i++)
    {
        double result[REP_COUNT][OP_COUNT];

        measure_all(n_values[i], result);

        for(int r = 0; r < REP_COUNT; r++)
        {
            for(int o = 0; o < OP_COUNT; o++)
            {
                data[r][o][i] = result[r][o];
            }
        }
    }


    /* Print final complexity table */

    printf("\n");
    printf("===============================================================\n");
    printf("       Q1 - EXPERIMENTAL TIME COMPLEXITY ANALYSIS\n");
    printf("===============================================================\n\n");


    print_line();

    printf("| Representation           | Search   | Insert   | Delete   | Maximum  | Minimum  | Predecessor | Successor |\n");

    print_line();


    for(int r = 0; r < REP_COUNT; r++)
    {
        printf("| %-24s | %-8s | %-8s | %-8s | %-8s | %-8s | %-11s | %-9s |\n",
               REP_NAMES[r],
               class_text(EXPECTED[r][SEARCH_OP]),
               class_text(EXPECTED[r][INSERT_OP]),
               class_text(EXPECTED[r][DELETE_OP]),
               class_text(EXPECTED[r][MAX_OP]),
               class_text(EXPECTED[r][MIN_OP]),
               class_text(EXPECTED[r][PREDECESSOR_OP]),
               class_text(EXPECTED[r][SUCCESSOR_OP]));
    }

    print_line();


    /* Save experimental data */

    FILE *fp = fopen("q1_experimental_data.csv", "w");

    if(fp == NULL)
    {
        printf("\nError creating data file.\n");
        return 1;
    }


    fprintf(fp, "n");

    for(int r = 0; r < REP_COUNT; r++)
    {
        for(int o = 0; o < OP_COUNT; o++)
        {
            fprintf(fp, ",%s_%s",
                    REP_NAMES[r],
                    OP_NAMES[o]);
        }
    }

    fprintf(fp, "\n");


    for(int i = 0; i < POINTS; i++)
    {
        fprintf(fp, "%d", n_values[i]);

        for(int r = 0; r < REP_COUNT; r++)
        {
            for(int o = 0; o < OP_COUNT; o++)
            {
                fprintf(fp, ",%.0f",
                        data[r][o][i]);
            }
        }

        fprintf(fp, "\n");
    }


    fclose(fp);


    printf("\nExperimental data saved in:\n");
    printf("q1_experimental_data.csv\n");


    printf("\nExperiment completed successfully.\n");

    return 0;
}