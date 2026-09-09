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

For every query, the time complexity is $$\mathcal{O}(\log n \cdot \log A)$$.

The overall time complexity is: $$\mathcal{O}(n \log A + q \log n \cdot \log A)$$.

---

## Sparse Table

\documentclass[11pt,a4paper]{article}
\usepackage[margin=2cm]{geometry}
\usepackage{amsmath,amssymb}
\usepackage[T1]{fontenc}
\usepackage{lmodern}

\setlength{\parindent}{0pt}
\setlength{\parskip}{0.6em}

\begin{document}

\section*{E - Mountain Height Survey}

Time Limit: 2 sec / Memory Limit: 1024 MiB

Score: 433 pts

\subsection*{Problem Statement}

Takahashi works as a mountain guide and manages information about
$N$ mountains in a mountain range. The mountains are numbered from
$1$ to $N$, and the elevation of the $i$-th mountain is $A_i$ meters
($1 \le i \le N$).

Takahashi has received $Q$ queries from tourists.
The $j$-th query ($1 \le j \le Q$) specifies the mountains from
the $L_j$-th to the $R_j$-th, and asks for the highest elevation
among them.

For each query, find the maximum elevation among the mountains
in the specified range.

\subsection*{Constraints}

\begin{itemize}
    \item $1 \le N \le 10^5$
    \item $1 \le Q \le 10^5$
    \item $1 \le A_i \le 10^9 \quad (1 \le i \le N)$
    \item $1 \le L_j \le R_j \le N \quad (1 \le j \le Q)$
    \item All inputs are integers.
\end{itemize}

\subsection*{Input}

Input is given from Standard Input in the following format:
\[
\begin{array}{llll}
N & Q \\
A_1 & A_2 & \cdots & A_N \\
L_1 & R_1 \\
L_2 & R_2 \\
\vdots \\
L_Q & R_Q
\end{array}
\]

\begin{itemize}
    \item The first line contains an integer $N$ representing
    the number of mountains and an integer $Q$ representing
    the number of queries, separated by a space.

    \item The second line contains integers
    $A_1, A_2, \ldots, A_N$ representing the elevations of
    each mountain, separated by spaces.
    \begin{itemize}
        \item $A_i$ represents the elevation (in meters)
        of the $i$-th mountain.
    \end{itemize}

    \item In the following $Q$ lines, the $j$-th line
    ($1 \le j \le Q$, which is the $(2+j)$-th line of
    the entire input) contains the left endpoint $L_j$
    and the right endpoint $R_j$ of the range specified
    by the $j$-th query, separated by a space.
\end{itemize}

\subsection*{Output}

Output $Q$ lines. The $j$-th line ($1 \le j \le Q$)
should contain the answer to the $j$-th query, that is,
the maximum elevation among the mountains from the
$L_j$-th to the $R_j$-th.

\subsection*{Sample Input 1}

\begin{verbatim}
5 3
100 250 180 320 150
1 3
2 5
4 4
\end{verbatim}

\subsection*{Sample Output 1}

\begin{verbatim}
250
320
320
\end{verbatim}

\subsection*{Sample Input 2}

\begin{verbatim}
8 5
1500 2300 1800 3776 2500 1200 2800 1900
1 8
3 6
1 4
5 8
2 2
\end{verbatim}

\subsection*{Sample Output 2}

\begin{verbatim}
3776
3776
3776
2800
2300
\end{verbatim}

\subsection*{Sample Input 3}

\begin{verbatim}
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
\end{verbatim}

\subsection*{Sample Output 3}

\begin{verbatim}
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
\end{verbatim}

\end{document}


---

## Solving problem by using sparse table

