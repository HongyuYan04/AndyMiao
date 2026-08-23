# Editorial

## 1. Key Observation

Every gram of cheese has the same weight: exactly one gram. The only difference is its deliciousness.

For cheese type $i$:

- each gram contributes $A_i$ deliciousness;
- at most $B_i$ grams are available.

Therefore, whenever we still have space on the pizza, it is always optimal to use an available gram with the largest possible value of $A_i$.

This immediately suggests the following greedy strategy:

1. Sort all cheese types in descending order of deliciousness per gram, $A_i$.
2. Process them in that order.
3. For each type, take as many grams as possible, but never exceed the remaining capacity.
4. Stop when the total amount reaches $W$ grams or when all cheese has been considered.

## 2. Algorithm

Store every cheese type as a pair $(A_i,B_i)$ and sort the pairs so that

$$
A_1 \ge A_2 \ge \cdots \ge A_N.
$$

Let `remaining` be the number of additional grams that can still be placed on the pizza. Initially,

$$
\text{remaining}=W.
$$

When processing cheese type $i$, take

$$
x_i=\min(B_i,\text{remaining})
$$

grams. Its contribution to the answer is

$$
A_i\cdot x_i.
$$

Then update

$$
\text{remaining}\leftarrow\text{remaining}-x_i.
$$

If `remaining` becomes zero, the pizza is full and we can stop.

Notice that the statement says **at most** $W$ grams. If the total amount of available cheese is less than $W$, we simply take all of it.

## 3. Proof of Correctness

We prove that the algorithm produces the maximum possible total deliciousness.

### Lemma

Suppose cheese type $p$ has a larger deliciousness per gram than cheese type $q$:

$$
A_p>A_q.
$$

If a feasible solution uses one gram of type $q$ while an unused gram of type $p$ is still available, replacing that gram of type $q$ with one gram of type $p$ does not violate the weight limit and strictly increases the total deliciousness.

### Proof

Both pieces weigh exactly one gram, so the total weight remains unchanged after the replacement. The change in deliciousness is

$$
A_p-A_q>0.
$$

Thus, the new solution is feasible and has a strictly larger total deliciousness. Therefore, the original solution could not have been optimal. $\square$

### Theorem

Taking cheese in descending order of $A_i$ and taking as much as possible from each type is optimal.

### Proof

Consider any optimal solution. If it differs from the greedy solution, let type $p$ be the first cheese type in descending order of $A_i$ for which the optimal solution takes fewer grams than the greedy solution.

There are two possibilities:

1. The optimal solution uses less than $W$ grams in total. Then it can add another available gram of type $p$, increasing the total deliciousness, which contradicts optimality.
2. The optimal solution already uses $W$ grams. Since it takes fewer grams of type $p$ than the greedy solution, it must use at least one gram of some later type $q$ with $A_q\le A_p$. Replacing that gram of type $q$ with one gram of type $p$ never decreases the deliciousness, by the lemma.

By repeatedly applying this exchange, we can transform an optimal solution into the greedy solution without decreasing its total deliciousness. Hence the greedy solution is also optimal. $\square$

## 4. Example Walkthrough

For the first sample:

```text
N = 3, W = 5
(A, B) = (3, 1), (4, 2), (2, 3)
```

After sorting by $A$ in descending order:

```text
(4, 2), (3, 1), (2, 3)
```

We take:

- $2$ grams with value $4$ per gram;
- $1$ gram with value $3$ per gram;
- $2$ grams with value $2$ per gram.

The total weight is

$$
2+1+2=5,
$$

and the total deliciousness is

$$
2\cdot4+1\cdot3+2\cdot2=15.
$$

## 5. Complexity Analysis

Sorting the $N$ cheese types takes

$$
O(N\log N)
$$

time. The greedy scan takes $O(N)$ time.

Therefore, the total time complexity is

$$
O(N\log N),
$$

and the extra space complexity is

$$
O(N).
$$

## 6. Integer Type

The answer can be much larger than a 32-bit integer. For example, both $A_i$ and the total number of selected grams can be large, so the result can be on the order of $10^{17}$.

Therefore, all quantities involved in multiplication and accumulation should be stored in `long long`.

## 7. C++17 Implementation

```cpp
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long w;
    cin >> n >> w;

    vector<pair<long long, long long>> cheese(n);
    for (auto &[deliciousness, amount] : cheese) {
        cin >> deliciousness >> amount;
    }

    sort(cheese.begin(), cheese.end(),
         [](const auto &lhs, const auto &rhs) {
             return lhs.first > rhs.first;
         });

    long long answer = 0;
    long long remaining = w;

    for (const auto &[deliciousness, amount] : cheese) {
        if (remaining == 0) break;

        long long take = min(amount, remaining);
        answer += deliciousness * take;
        remaining -= take;
    }

    cout << answer << '\n';
    return 0;
}
```

## 8. Common Mistakes

1. **Sorting in ascending order.**  
   We must process cheese with the greatest deliciousness per gram first.

2. **Taking all $B_i$ grams without checking the remaining capacity.**  
   The correct amount is `min(B_i, remaining)`.

3. **Using `int` for the answer.**  
   The multiplication $A_i\cdot B_i$ and the accumulated answer require `long long`.

4. **Assuming that exactly $W$ grams must be used.**  
   The pizza may contain fewer than $W$ grams if there is not enough cheese in total.
