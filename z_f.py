s = input()
n = len(s)

ans = [0] * n
l = r = 0
for i in range(1, n):
    ans[i] = max(0, min(r - i, ans[i - l]))
    while ans[i] + i < n and s[ans[i]] == s[i + ans[i]]:
        ans[i] += 1

    if i + ans[i] > r:
        l, r = i, i + ans[i]

print(*ans)
