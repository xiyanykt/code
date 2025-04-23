#include<bits/stdc++.h>

using i64 = int64_t;

struct Node {
	Node * son[2] = {nullptr, nullptr};
	Node * par = nullptr;
	bool rev = false;
	int siz = 1;

};

void reverse(Node * t) {
	if (t != nullptr) {
		std::swap(t->son[0], t->son[1]);
		t->rev ^= 1;
	}
}

void push(Node * t) {
	if (t->rev) {
		reverse(t->son[0]);
		reverse(t->son[1]);
		t->rev ^= 1;
	}
}

void plus(Node * t) {
	t->siz = (t->son[0] == nullptr ? 0 : t->son[0]->siz) + (t->son[1] == nullptr ? 0 : t->son[1]->siz) + 1;
}

bool isRoot(Node * t) {
	return t->par == nullptr or (t->par->son[0] != t and t->par->son[1] != t);
}

int pos(Node * t) {
	return t->par->son[1] == t;
}

void update(Node * t) {
	if (not isRoot(t)) {
		update(t->par);
	}
	push(t);
}

void rotate(Node * t) {
	Node * q = t->par;
	int x = !pos(t);
	q->son[!x] = t->son[x];
	if (t->son[x] != nullptr) {
		t->son[x]->par = q;
	}
	t->par = q->par;
	if (not isRoot(q)) {
		q->par->son[pos(q)] = t;
	}
	t->son[x] = q;
	q->par = t;
	plus(q);
}

void Splay(Node * t) {
	update(t);
	while (not isRoot(t)) {
		if (not isRoot(t->par)) {
			rotate((pos(t) == pos(t->par)) ? t->par : t);
		}
		rotate(t);
	}
	plus(t);
}

void access(Node * t) {
	for (Node * i = t, *q = nullptr; i != nullptr; q = i, i = i->par) {
		Splay(i);
		i->son[1] = q;
		plus(i);
	}
	Splay(t);
}

void makeRoot(Node * t) {
	access(t);
	reverse(t);
}

void link(Node * x, Node * y) {
	makeRoot(x);
	x->par = y;
}

void Split(Node * x, Node * y) {
	makeRoot(x);
	access(y);
}

void cut(Node * x, Node * y) {
	Split(x, y);
	x->par = y->son[0] = nullptr;
	plus(y);
}

int dist(Node * x, Node * y) {
	Split(x, y);
	assert(y != nullptr);
	return y->siz - 1;
}

void dfs(Node * t) {
	if (t == nullptr) {
		return;
	}
	push(t);
	dfs(t->son[0]);
	std::cerr << "!" << "\n";
	dfs(t->son[1]);
}
