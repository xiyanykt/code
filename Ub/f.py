def solve():
    import sys
    input = sys.stdin.read
    data = input().split()
    idx = 0

    t = int(data[idx])
    idx += 1

    # 预处理前 10 个 Fibonacci 数列
    fib = [0] * 11
    fib[1] = 1
    fib[2] = 2
    for i in range(3, 11):
        fib[i] = fib[i - 1] + fib[i - 2]

    # 预处理每个 Fibonacci cube 的体积（边长的立方）
    cube_vol = [0] + [fib[i] ** 3 for i in range(1, 11)]

    result = []
    for _ in range(t):
        n = int(data[idx])
        m = int(data[idx + 1])
        idx += 2

        total_volume = sum(cube_vol[1:n+1])
        max_fib_side = fib[n]

        res = []
        for _ in range(m):
            w = int(data[idx])
            l = int(data[idx + 1])
            h = int(data[idx + 2])
            idx += 3

            min_side = min(w, l, h)
            box_volume = w * l * h

            if min_side >= max_fib_side and box_volume >= total_volume:
                res.append('1')
            else:
                res.append('0')

        result.append(''.join(res))

    print('\n'.join(result))
solve()