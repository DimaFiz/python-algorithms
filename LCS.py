s_1 = input()
s_2 = input()

n = len(s_1)
m = len(s_2)

dp = [[0] * (m + 1) for _ in range(n + 1)]

for i in range(1, n + 1):
    for j in range(1, m + 1):
        if s_1[i - 1] == s_2[j - 1]:
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1] + 1)
        else:
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

ans = []
i = n
j = m

ans = []

while i > 0 and j > 0:
    if s_1[i - 1] == s_2[j - 1]:
        ans.append(s_1[i - 1])
        i -= 1
        j -= 1
    elif dp[i][j - 1] == dp[i][j]:
        j -= 1
    else:
        i -= 1

print("".join(ans[::-1]))
