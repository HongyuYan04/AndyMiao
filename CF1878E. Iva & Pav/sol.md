# Observation $1$

If $$L$$ is fixed, $$f(L, R)$$ will **monotonic and non-increasing** as $$R$$ increases.

Proof : As $$R$$ increases, each binary bit of $$f(L, R)$$ will only undergo one of these three changes :

- $$0 \rightarrow 0$$

- $$1 \rightarrow 0$$

- $$1 \rightarrow 1$$

If we sum up each binary bit, then $$f(L, R)$$ will naturally be monotonic and non-increasing.

What we need to do is find the position of the last $$1$$ in the sequence $$111111....1000....0$$.


---

# Observation $2$

For every query, consider **binary search**.

<img width="1446" height="722" alt="image" src="https://github.com/user-attachments/assets/2a89c1d5-7a97-4e7b-8cf4-a732c3828bdb" />

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

For every query, the time complexity is $$\mathcal{O}(\log n \log A)$$.

The overall time complexity is: $$\mathcal{O}(n \log A + q \log n \log A)$$.
