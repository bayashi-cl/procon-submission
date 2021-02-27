def score(hand):
    s = 0
    for i in range(1, 10):
        s += i * 10 ** hand.count(str(i))
    return s


K = int(input())
T = input()[:4]
A = input()[:4]

deck = [0] + [K] * 9
for t_c, a_c in zip(T, A):
    deck[int(t_c)] -= 1
    deck[int(a_c)] -= 1

t_win = 0
for t in range(1, 10):
    for a in range(1, 10):
        if score(T + str(t)) <= score(A + str(a)):
            continue
        if t == a:
            t_win += deck[t] * (deck[a] - 1)
        else:
            t_win += deck[t] * deck[a]
ans = t_win / (((9 * K) - 8) * (9 * K - 9))
print(ans)
