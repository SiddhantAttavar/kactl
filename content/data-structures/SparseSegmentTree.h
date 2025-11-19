/**
 * Author: Simon Lindholm
 * Date: 2015-02-24
 * License: CC0
 * Source: Wikipedia, tinyKACTL
 * Description: Sparse/Persistent Segment Tree. Possible MLE/TLE issues. 
 * Provide approx q = num of queries + updates to improve time per operation
 * Time: $O(\log N)$
 * Status: Tested on Kattis and SPOJ, and stress-tested
 */
#pragma once

template<typename T, int SZ> struct SparseSegmentTree {
	vector<pair<int, int>> tree;
	vector<T> seg; T id; int n;
	T (*cmb) (T, T);
	SparseSegmentTree(T _id, T _cmb(T, T), int q = 0):id(_id),
		cmb(_cmb),n(1),tree({{-1, -1}}),seg({{id}}) {
		int k = 2 * q * __lg(SZ);
		tree.reserve(k); seg.reserve(k);
	}
	void add(int c, int l, int r) {
		if (tree[c].first != -1 or l == r) return;
		tree[c] = {n, n + 1}; n += 2;
		tree.push_back({-1, -1}); tree.push_back({-1, -1});
		seg.push_back(id); seg.push_back(id);
	}
	T query(int l, int r, int s=0, int e=SZ-1, int c=0) {
		if (l > e || r < s) return id;
		if (l <= s && r >= e) return seg[c];
		int mid = (s + e) / 2; add(c, s, e);
		return cmb(query(l,r, s, mid, tree[c].first),
			query(l, r, mid + 1, e, tree[c].second));
	}
	void upd(int i, T x, int s=0, int e=SZ-1, int c=0) {
		if (s > i || e < i) return;
		if (s == e) {seg[c] = x; return;}
		int mid = (s + e) / 2; add(c, s, e);
		upd(i, x, s, mid, tree[c].first);
		upd(i, x, mid + 1, e, tree[c].second);
		seg[c] = cmb(seg[tree[c].first], seg[tree[c].second]);
	}
};
