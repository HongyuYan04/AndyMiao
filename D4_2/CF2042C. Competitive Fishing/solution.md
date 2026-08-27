# CF2042C. Competitive Fishing

You want Bob's score to exceed Alice's score by at least $$k$$ points. What is the minimum number of groups ($$m$$) you have to split the fishes into?  If it is impossible, you should report that.

Let $$F$$ represent Bob's score minus Alice's score.

Then, consider one operation's contribution to enhance $$F$$ : 

<img width="1403" height="668" alt="image" src="https://github.com/user-attachments/assets/03be9f57-274c-4cd4-b6ee-0c5f52586b2d" />

Increasing the number of groups each time is equivalent to placing a barrier between two fish.

If we place a barrier between the $$i$$-th fish and the $$(i + 1)$$-th fish, it will only affect the group numbers of fish $$i + 1 \sim n$$.

The result is that the group number for each fish from the $$(i + 1)$$-th fish to the $$n$$-th fish increases by $$1$$, and correspondingly, Bob's score increases by $$X$$, Alice's score increases by $$Y$$.

- $$X$$ represents the number of '1' characters in range $$\displaystyle S_{i \sim n - 1}$$.

- $$Y$$ represents the number of '0' characters in range $$\displaystyle S_{i \sim n - 1}$$.

And, such an operation will increase $$F$$ by $$X - Y$$.

If we want to know whether dividing into $$T$$ groups can meet the requirements, then, **greedily**, we must put the baffle in the $$T - 1$$ gaps with the largest $$X - Y$$. If a baffle is placed elsewhere, then using this baffle to fill these $$T - 1$$ gaps will **not result in a disadvantage** in contribution to $$F$$.

Consider sorting in descending order of $$\displaystyle X - Y$$, then selecting each prefix sequentially, and then determining whether the requirements are met.

The contribution of placing a baffle at each position can be optimized in terms of time complexity using something like a suffix sum.

The time complexity is $$\displaystyle \mathcal{O}(\sigma n \log \sum n)$$.
