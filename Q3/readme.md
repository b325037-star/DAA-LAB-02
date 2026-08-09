Q3. Merging k Sorted Arrays

Suppose there are k sorted arrays, each having n elements.

Total elements:

kn
(a) Method 1 — Merge One by One

The first two arrays are merged, then the result is merged with the third, then with the fourth, and so on.

Cost
Merge array 1 + array 2 → 2n elements → O(n)
Merge result + array 3 → 3n elements → O(n)
Merge result + array 4 → 4n elements → O(n)
...
Final merge → kn elements

Therefore:

T(n,k)=n+2n+3n+⋯+(k−1)n
T(n,k)=n(1+2+3+⋯+(k−1))

Using:

1+2+⋯+(k−1)=

k(k−1)/2
	​
Therefore:

T(n,k)=

nk(k−1)/2
	​


So,

T(n,k)=Θ(nk^2)
	​

Method 1 answer:
Θ(nk^2)
	​

(b) Method 2 — Pairwise Merging

Here, the arrays are merged in pairs.

For example, if:

k=8

Initially:

8 arrays of n
       ↓
4 arrays of 2n
       ↓
2 arrays of 4n
       ↓
1 array of 8n

There are:

log_2 k

levels.

At each level, all kn elements are processed once.

Therefore:

T(n,k)=knlog_2 k

So:

T(n,k)=Θ(nklogk)
	​

Method 2 answer:
Θ(nklogk)
	​

Final Complexity Table
Method	Approach	Worst-case running time
Method 1	Merge arrays one by one	Θ(nk²)
Method 2	Merge arrays pairwise	Θ(nk log k)
Which is better?

For large k:

nklogk<nk
2

Therefore, Method 2 is more efficient.
