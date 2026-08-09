# Merge Sort vs Modified 3-Way Merge Sort

## Aim

To compare the normal Merge Sort with the modified 3-way Merge Sort
and study their worst-case time complexity and order of growth.

## Algorithms Used

1. Normal Merge Sort
2. Modified 3-Way Merge Sort

## Time Complexity

### Normal Merge Sort

Recurrence:

T(n) = 2T(n/2) + O(n)

Worst-case complexity:

O(n log n)

### Modified 3-Way Merge Sort

Recurrence:

T(n) = 3T(n/3) + O(n)

Worst-case complexity:

O(n log n)

Therefore, both algorithms have the same asymptotic
worst-case time complexity.

## Program

The C program:

- Takes the number of elements as input.
- Takes the array elements as input.
- Sorts the array using normal Merge Sort.
- Sorts the same array using modified 3-way Merge Sort.
- Displays the sorted arrays.
- Measures and displays the execution time of both algorithms.
- Generates data for plotting the order of growth.

## Output

The program displays:

- Original array
- Sorted array using normal Merge Sort
- Sorted array using modified 3-way Merge Sort
- Execution time of both algorithms

## Graph

The graph compares the order of growth of the two algorithms.

Both algorithms show approximately n log n growth.

## Conclusion

Normal Merge Sort and Modified 3-Way Merge Sort have the same
asymptotic worst-case complexity:

O(n log n)

Although their execution times may differ, their order of growth
remains the same.
