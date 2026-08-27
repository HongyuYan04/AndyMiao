# CF2042C. Competitive Fishing

You want Bob's score to exceed Alice's score by at least $$k$$ points. What is the minimum number of groups ($$m$$) you have to split the fishes into?  If it is impossible, you should report that.

Let $$F$$ represent Bob's score minus Alice's score.

Then, consider one operation's contribution to enhance $$F$$ : 

<img width="1403" height="668" alt="image" src="https://github.com/user-attachments/assets/03be9f57-274c-4cd4-b6ee-0c5f52586b2d" />

Increasing the number of groups each time is equivalent to placing a barrier between two fish.

If we place a barrier between the $$i$$-th fish and the $$(i + 1)$$-th fish, it will only affect the group numbers of fish $$i + 1 \sim n$$.
