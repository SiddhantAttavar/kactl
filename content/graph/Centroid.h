/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Find centroid decomposition of a tree. Main function to be called is
 * solve(root, root, [](ll v) {}). Process trees formed after decomposition at each step within 
 * process(node)
 * Time: O(N \log N)
 * Status: stress-tested against old HLD
 */
#pragma once

struct Centroid { // 0 based indexing.
	vector<vi> centroid_tree, adj;
	vi par_ct, siz;
	vector<bool> vis;
	Centroid(vector<vector<ll>> _adj) : adj(_adj) {
		centroid_tree.assign(sz(_adj), {});
		siz.assign(sz(_adj), 0);
		vis.assign(sz(_adj), false);
		par_ct.assign(sz(_adj), -1);
	}
	void find_size(ll v, ll par) {
		siz[v] = 1;
		for(auto x : adj[v]) {
			if(x == par || vis[x]) continue;
			find_size(x, v);
			siz[v] += siz[x];
		}
	}
	ll find_centroid(ll v, ll par, ll n_nodes) {
		for(auto x : adj[v]) {
			if(x == par || vis[x]) continue;
			if(siz[x] > n_nodes/2) return find_centroid(x, v, n_nodes); 
		}
		return v;
	}
	ll solve(ll v, ll prev, auto process) {
		find_size(v, prev);
		ll centroid = find_centroid(v, prev, siz[v]);
		process(centroid);
		vis[centroid] = true;
		par_ct[centroid] = prev;
		for(auto x : adj[centroid]) { 
			if (vis[x]) continue;
			centroid_tree[centroid].push_back(solve(x, centroid, process));
		}
		return centroid;
	}
};
