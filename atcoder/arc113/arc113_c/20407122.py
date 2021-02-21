from collections import defaultdict

s = list(input())
char_num = defaultdict(int)
ans = 0
for i in range(len(s) - 1, 0, -1):
    if s[i] == s[i - 1]:
        right = sum(char_num.values())
        ans += right - char_num[s[i]]
        for c in char_num:
            char_num[c] = 0
        char_num[s[i]] = right
    char_num[s[i]] += 1

print(ans)
