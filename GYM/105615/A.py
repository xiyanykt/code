x = int(input())
r = 0
w = 0
for y in range(1, 2024):
    if r < (x * y) % 2024:
        w = y
        r = x * y
        r %= 2024
print(w)
