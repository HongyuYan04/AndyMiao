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
