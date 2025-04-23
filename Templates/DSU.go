type DSU struct {
	par []int
	siz []int
}

func newDSU(n int) *DSU {
	p := make([]int, n + 1)
	s := make([]int, n + 1)
	for i := 1; i <= n; i++ {
		p[i] = i
		s[i] = 1
	}
	return &DSU{p, s}
}

func (dsu *DSU) find(x int) int {
	for x != dsu.par[x] {
		dsu.par[x] = dsu.par[dsu.par[x]]
		x = dsu.par[x]
	}
	return x
}

func (dsu *DSU) same(x int, y int) bool {
	return dsu.find(x) == dsu.find(y)
}

func (dsu *DSU) size(x int) int {
	return dsu.siz[dsu.find(x)]
}

func (dsu *DSU) merge(x int, y int) bool {
	fx := dsu.find(x)
	fy := dsu.find(y)

	if fx == fy {
		return false
	}

	if dsu.siz[fx] < dsu.siz[fy] {
		fx, fy = fy, fx
	}

	dsu.siz[fx] += dsu.siz[fy]
	dsu.par[fy] = fx
	return true
}