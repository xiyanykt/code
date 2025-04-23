package main

import (
	"bufio"
	"fmt"
	"os"
)

var (
	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
)

type Fenwick struct {
	n int
	a []int
}

func newFenwick(n int) *Fenwick {
	return &Fenwick{
		n : n,
		a : make([]int, n + 1),
	}
}

func (fen *Fenwick) add(p, x int) {
	if p >= 1 && p <= fen.n {
		for i := p; i <= fen.n; i += i & -i {
			fen.a[i] += x
		}
	}
}

func (fen *Fenwick) sum(p int) int {
	res := 0
	if p >= 1 && p <= fen.n {
		for i := p; i >= 1; i -= i & -i {
			res += fen.a[i]
		}
	}
	return res
}

func (fen *Fenwick) rangeQuery(l, r int) int {
	return fen.sum(r) - fen.sum(l - 1)
}

func (fen *Fenwick) find(k int) int {
	x := 0
	c := 0
	for i := 31; i >= 0; i -= 1 {
		x += 1 << i
		if x >= fen.n || c + fen.a[x] >= k {
			x -= 1 << i
		} else {
			c += fen.a[x]
		}
	}
	return x + 1
}

const inf int64 = 1000000000000000000

func main() {
	defer out.Flush()
	
	var n int
	var k int64
	fmt.Fscan(in, &n, &k)

	a := make([]int64, n + 1)
	for i := 1; i <= n; i += 1 {
		fmt.Fscan(in, &a[i])
		a[i] += a[i - 1]
	}

	a[0] = -inf
	
	var res int64
	res = 0

	v = make(map[int]bool)
	var d []int

}