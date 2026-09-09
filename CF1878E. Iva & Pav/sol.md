# Observation $1$

If $$L$$ is fixed, $$f(L, R)$$ will **monotonic and non-increasing** as $$R$$ increases.

Proof : As $$R$$ increases, each binary bit of $$f(L, R)$$ will only undergo one of these three changes :

- $$0 \rightarrow 0$$

- $$1 \rightarrow 0$$

- $$1 \rightarrow 1$$

Since all values are non-negative, clearing bits cannot increase the value. 

Thus, for a fixed $$L$$, $$f(L, R)$$ is non-increasing as $$R$$ increases.

---

# Observation $2$

For every query, consider **binary search**.

<img width="1446" height="722" alt="image" src="https://github.com/user-attachments/assets/2a89c1d5-7a97-4e7b-8cf4-a732c3828bdb" />

Assume that the answer must lie within the range $$[L, R]$$.

Then we check whether $$f(L, mid)$$ is greater than or equal to $$k$$.

If $$f(L, mid) \ge k$$, the answer will be within this range : $$[mid, n]$$, then we need update : $$L \rightarrow mid$$.

If $$f(L, mid) < k$$, the answer will be within this range : $$[L, mid - 1]$$, then we need update :  $$R \rightarrow mid - 1$$.

---

# Observation $3$

To solve for $$f(L, R)$$, we need to design an efficient computational method.

Two methods can be considered here: 

- consider the result of each binary bit separately and then combine them bit by bit

- use a sparse table for calculation.

--- 

# Calculate bit-by-bit

Consider a two-dimensional array like this :

```cpp
int pre[MAXN][LOGA];
```

The meaning of $$pre_{i, j}$$ is : how many elements in $$a_{1 \sim i}$$ have a j-th binary bit that is $$1$$.

For the calculation of $$f(L, R)$$, consider the following code :

```cpp
int calc(int l, int r) {
    int res = 0;
    for (int bit = 0; bit < LOGA; bit++) {
        if (pre[r][bit] - pre[l - 1][bit] == r - l + 1) {
            res |= 1 << bit;
        }
    }
    return res;
}
```

The time complexity of the function is $$\mathcal{O}(\log A)$$, $$A$$ means $$\max(a_i)$$.

For the preprocessing of the pre array, consider using a method similar to **prefix sums**.

```cpp
void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < LOGA; j++) {
            pre[i][j] = pre[i - 1][j];
            if ((a[i] >> j) & 1) {
                pre[i][j]++;
            }
        }
    }
}
```

The time complexity of preprocessing is $$\mathcal{O}(n \log A)$$.

For every query, the time complexity is $$\mathcal{O}(\log n \cdot \log A)$$.

The overall time complexity is: $$\mathcal{O}(n \log A + q \log n \cdot \log A)$$.

---

# Sparse Table

## [E - Mountain Height Survey](https://atcoder.jp/contests/awc0005/tasks/awc0005_e)

- **Time Limit:** 2 sec
- **Memory Limit:** 1024 MiB
- **Score:** 433 pts

### Problem Statement

Takahashi works as a mountain guide and manages information about $N$ mountains in a mountain range. The mountains are numbered from $1$ to $N$, and the elevation of the $i$-th mountain is $A_i$ meters ($1 \le i \le N$).

Takahashi has received $Q$ queries from tourists. The $j$-th query ($1 \le j \le Q$) specifies the mountains from the $L_j$-th to the $R_j$-th, and asks for the highest elevation among them.

For each query, find the maximum elevation among the mountains in the specified range.

### Constraints

- $1 \le N \le 10^5$
- $1 \le Q \le 10^5$
- $1 \le A_i \le 10^9$ ($1 \le i \le N$)
- $1 \le L_j \le R_j \le N$ ($1 \le j \le Q$)
- All inputs are integers.

### Input

Input is given from Standard Input in the following format:

```text
N Q
A[1] A[2] ... A[N]
L[1] R[1]
L[2] R[2]
...
L[Q] R[Q]
```

- The first line contains an integer $N$ representing the number of mountains and an integer $Q$ representing the number of queries, separated by a space.
- The second line contains integers $A_1, A_2, \ldots, A_N$ representing the elevations of each mountain, separated by spaces. Here, $A_i$ represents the elevation (in meters) of the $i$-th mountain.
- In the following $Q$ lines, the $j$-th line ($1 \le j \le Q$, which is the $(2+j)$-th line of the entire input) contains the left endpoint $L_j$ and the right endpoint $R_j$ of the range specified by the $j$-th query, separated by a space.

### Output

Output $Q$ lines. The $j$-th line ($1 \le j \le Q$) should contain the answer to the $j$-th query, that is, the maximum elevation among the mountains from the $L_j$-th to the $R_j$-th.

### Sample Input 1

```text
5 3
100 250 180 320 150
1 3
2 5
4 4
```

### Sample Output 1

```text
250
320
320
```

### Sample Input 2

```text
8 5
1500 2300 1800 3776 2500 1200 2800 1900
1 8
3 6
1 4
5 8
2 2
```

### Sample Output 2

```text
3776
3776
3776
2800
2300
```

### Sample Input 3

```text
15 10
500 1200 800 3500 2200 1800 4200 900 3100 2700 1500 4800 2000 3300 1100
1 15
1 7
7 12
10 15
3 5
6 10
12 12
1 1
8 14
5 9
```

### Sample Output 3

```text
4800
4200
4800
4800
3500
4200
4800
500
4800
4200
```

---

The aforementioned problem can be solved using a **Sparse Table**. 

The time complexity for preprocessing is $$\mathcal{O}(N \log N)$$, and the time complexity for each range maximum/minimum values query is $$\mathcal{O}(1)$$.

- The range minimum/maximum query problem is commonly represented by the abbreviation RMQ.

Consider a two-dimensional array like this :

```cpp
int f[MAXN][LOGN];
```

The meaning of $$f_{i, j}$$ is : $$\displaystyle \max(A_i, A_{i + 1}, \cdots, A_{i + 2^j - 1})$$.

Firstly, $$f_{i, 0} = a_i$$.

If $$j \ne 0$$, $$f_{i, j} = \max(f_{i, j - 1}, f_{i + 2^{j - 1}, j - 1})$$

The time complexity for preprocessing is $$\mathcal{O}(N \log N)$$.

```cpp
void init() {
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i];
    }
    /*

        Note that when constructing the sparse table,
        you must first iterate through the interval lengths;
        this is because information about longer intervals is updated using information from shorter intervals.

    */
    for (int j = 1; (1 << j) <= n; j++) { // !!!
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
}
```

For the query, here we consider splitting the length of the query interval into binary form, 

and then merging the $$\mathcal{O}(\log n)$$ intervals to calculate the answer.

This processing method has a time complexity of $$\mathcal{O}(\log n)$$ for answering each query.

```cpp
int query(int L, int R) {
    int res = -INF;
    int len = R - L + 1;
    for (int i = 0; len != 0; i++) {
        if (len % 2) {
            res = max(res, f[L][i]);
            L += 1 << i;
        }
        len /= 2;
    }
    return res;
}
```

A more efficient solution is: 

Find two intervals of length $$\mathcal \lfloor \log_2 (R - L + 1) \rfloor$$, and merge them to obtain the answer.

Specifically, suppose $$k$$ is equal to $$\mathcal \lfloor \log_2 (R - L + 1) \rfloor$$, 

then the first interval is : an interval starting with $$L$$ and having a length of $$2^k$$. 

The second interval is: an interval ending with $$R$$ and having a length of $$2^k$$.

<img width="1431" height="638" alt="image" src="https://github.com/user-attachments/assets/3b721eaa-9851-467d-86d5-db19ebff127d" />

The lengths of these two intervals are both no more than $$R - L + 1$$, but when they are concatenated, the result will definitely be greater than $$R - L + 1$$.

This method has a time complexity of $$\mathcal{O}(1)$$ for answering each query.

The operation must be associative and idempotent: $$x \circ x = x$$. 

This ensures that overlapping elements do not affect the outcome.

For example, $$\max(X, X, Y) = \max(X, Y)$$.

Common operations that satisfy the requirement of repeatable contribution include: 

- range maximum value

- range minimum value

- range greatest common divisor

- range bitwise AND

- range bitwise OR.


```cpp
int query(int L, int R) {
    int k = std::__lg(R - L + 1);
    return std::max(f[L][k], f[R - (1 << k) + 1][k]);
}
```

For [this problem](https://codeforces.com/contest/1878/problem/E), replace $$\max$$ with bitwise AND.

```cpp
int a[N], f[N][LOGN];

void init() {
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i];
    }

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = f[i][j - 1] & f[i + (1 << (j - 1))][j - 1];
        }
    }
}

int query(int L, int R) {
    int k = std::__lg(R - L + 1);
    return f[L][k] & f[R - (1 << k) + 1][k];
}
```
