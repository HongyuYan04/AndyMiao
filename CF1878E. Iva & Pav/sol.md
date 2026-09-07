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

For every query, consider binary search.
