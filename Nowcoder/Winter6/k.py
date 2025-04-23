T = int(input())
for _ in range(T):
    x, y = map(int, input().split()) 
    if (y - 2 * x - 1) % 4 == 0:
        print("YES")
    else:
        print("NO")
