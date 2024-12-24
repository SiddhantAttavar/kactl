/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Find centroid decomposition of a tree. Main function to be called is
 * solve(root, root). Process trees formed after decomposition at each step within 
 * process(node)
 * Time: O(N \log N)
 * Status: stress-tested against old HLD
 */
#pragma once

vector<vi> adj; vi siz;
vector<bool> vis;
void find_size(int v, int p) {
	siz[v] = 1;
	for(auto nx : adj[v]) if(nx != p && !vis[nx]) {
		find_size(nx, v);
		siz[v] += siz[nx];
	}
}
int centroid(int v, int p, int n) {
	for(auto nx : adj[v]) if(nx != p && !vis[nx] && siz[nx] > n
			/2) {
		return centroid(nx, v, n);
	}
	return v;
}
void process(int v) {}
void solve(int v, int p) {
	find_size(v, p);
	int c = centroid(v, p, siz[v]);
	process(c);
	vis[c] = true;
	for(auto nx : adj[c]) if(!vis[nx]) solve(nx, c);
}
