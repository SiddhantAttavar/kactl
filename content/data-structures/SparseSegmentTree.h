/**
 * Author: Simon Lindholm
 * Date: 2015-02-24
 * License: CC0
 * Source: Wikipedia, tinyKACTL
 * Description: Sparse/Persistent Segment Tree. Use with BumpAllocator if there’s
 * MLE/TLE issues
 * Time: $O(\log N)$
 * Status: Tested on Kattis and SPOJ, and stress-tested
 */
#pragma once

struct Node {
	int x;
	Node *l, *r;
	Node(int _x) : x(_x), l(nullptr), r(nullptr) {}
	Node(Node* _l, Node* _r) : l(_l), r(_r) {
		x = 0;
		if(l) x += l->x;
		if(r) x += r->x;
	}
	Node(Node *v) : x(v->x), l(v->l), r(v->r) {}
};
Node* root[N];
Node* build(int l, int r) {
	if(l == r) return new Node(arr[l]);
	int m = (l + r)/2;
	return new Node(build(l, m), build(m + 1, r));
}
Node* update(Node* node, int l, int r, int pos, int val) {
	if(l == r) return new Node(val);
	int m = (l + r)/2;
	if(pos <= m) return new Node(update(node->l, l, m, pos, val),
			node->r);
	return new Node(node->l, update(node->r, m + 1, r, pos, val))
		;
}
int query(Node* node, int l, int r, int ql, int qr) {
	if(qr < l || ql > r) return 0;
	if(ql <= l && qr >= r) return node->x;
	int m = (l + r)/2;
	return query(node->l, l, m, ql, qr) + query(node->r, m + 1, r, ql, qr);
}
