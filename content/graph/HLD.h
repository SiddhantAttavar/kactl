/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template <typename T, typename U, bool VALS_EDGES, int SZ> struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, rt, pos;
	LazySeg<T, U, SZ> tree;
	T ID; U ID2; T (*cmb)(T, T); void (*push)(int,int,int,T*,U*);
	HLD(vector<vi> adj_, T id, U id2, T _cmb(T, T), void _push(int,int,int,vector<T>&,vector<U>&))
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1),rt(N),
		pos(N),ID(id),cmb(_cmb),tree(id,id2,_cmb,_push){ dfsSz(0); dfsHld(0); }
	void dfsSz(int v) {
		for (int& u : adj[v]) {
			adj[u].erase(find(all(adj[u]), v));
			par[u] = v;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (;; v = par[rt[v]]) {
			if (pos[u] > pos[v]) swap(u, v);
			if (rt[u] == rt[v]) break;
			op(pos[rt[v]], pos[v]);
		}
		op(pos[u] + VALS_EDGES, pos[v]);
	}
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree.upd(l, r, val); });
	}
	T queryPath(int u, int v) { // Modify depending on problem
		T res = ID;
		process(u, v, [&](int l, int r) {res = cmb(res, tree.query(l, r));});
		return res;
	}
	T querySubtree(int v) { // modifySubtree is similar
		return tree.query(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1);
	}
};
