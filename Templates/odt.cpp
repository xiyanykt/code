struct Node {
    int l, r;
    mutable int c;

    Node(int l = 0, int r = 0, int c = 0): l{l}, r{r}, c{c} {}
    friend std::strong_ordering operator<=>(Node lsh, Node rsh) {
        return lsh.l <=>rsh.l;
    }
};

std::set<Node>odt;

auto split(int p) {
    auto it = odt.lower_bound(Node(p, 0, 0));
    if (it != odt.end() && it->l == p) {
        return it;
    }
    assert(it != odt.begin());
    --it;
    int l = it->l, r = it->r;
    auto c = it->c;
    odt.erase(it);
    odt.insert(Node(l, p - 1, c));
    return odt.insert(Node(p, r, c)).first;
}