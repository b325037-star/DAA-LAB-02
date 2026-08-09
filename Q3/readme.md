# Q3 - Merging k Sorted Arrays

## Aim

To merge k sorted arrays, each containing n elements, into one single
sorted array containing kn elements.

Two different methods are implemented and compared.

## Problem Statement

We are given k sorted arrays, each having n elements.

The total number of elements is:

kn

We need to combine all the arrays into one sorted array.

---

## Method 1 - Sequential Merging

In Method 1, the arrays are merged one by one.

First, the first two arrays are merged. Then the resulting array is
merged with the third array, then with the fourth array, and so on.

For k arrays, the merging work is approximately:

2n + 3n + 4n + ... + kn

Therefore,

T(n,k) = Theta(n * k^2)

### Worst-case Running Time

Theta(n * k^2)

---

## Method 2 - Pairwise Merging

In Method 2, the arrays are merged in pairs.

For example, if k = 8:

8 arrays of n elements
        |
        v
4 arrays of 2n elements
        |
        v
2 arrays of 4n elements
        |
        v
1 array of 8n elements

At every level, all kn elements are processed once.

The number of levels is:

log2(k)

Therefore,

T(n,k) = kn log2(k)

### Worst-case Running Time

Theta(n * k * log k)

---

## Comparison

| Method | Approach | Worst-case Running Time |
|--------|----------|-------------------------|
| Method 1 | Merge arrays one by one | Theta(n * k^2) |
| Method 2 | Merge arrays pairwise | Theta(n * k * log k) |

---

## C Program

The C program implements both methods.

The program:

- Takes n as the number of elements in each array.
- Takes k as the number of sorted arrays.
- Creates sorted arrays.
- Merges the arrays using Method 1.
- Merges the arrays using Method 2.
- Counts the number of comparisons.
- Displays the comparison count for both methods.
- Displays the theoretical time complexity.

---

## Sample Input

Enter number of elements in each array: 100
Enter number of arrays: 8

## Sample Output

====================================
          RESULTS
====================================
n = 100
k = 8

Method 1 comparisons = ...
Method 2 comparisons = ...

Theoretical complexity:
Method 1 = Theta(n * k^2)
Method 2 = Theta(n * k * log k)

Method 2 is more efficient for large k.

The exact number of comparisons depends on the implementation and
input.

---
## Experimental Observation

As the value of k increases:

- Method 1 grows approximately as k^2.
- Method 2 grows approximately as k log k.

Therefore, Method 2 grows more slowly than Method 1.

---

## Conclusion

Method 1 has a worst-case running time of:

Theta(n * k^2)

Method 2 has a worst-case running time of:

Theta(n * k * log k)

Therefore, Method 2 is more efficient than Method 1, especially when
the number of sorted arrays k is large.

The experiment using the C program supports the theoretical analysis.
