/**
 * Author: Simon Lindholm
 * Date: 2015-02-24
 * License: CC0
 * Source: Wikipedia, tinyKACTL
 * Description: Finding cut vertices and cut edges.
 * Status: Tested on Kattis and SPOJ, and stress-tested
 */
#pragma once

int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph
vector<bool> visited;
vector<int> tin, low;
int timer;
void dfs(int v, int p = -1) {
	visited[v] = true;
	tin[v] = low[v] = timer++;
	int children=0; // CUT VERTICE
		for (int to : adj[v]) {
			if (to == p) continue;
			if (visited[to]) {
				low[v] = min(low[v], tin[to]);
			} else {
				dfs(to, v);
				low[v] = min(low[v], low[to]);
				if (low[to] > tin[v]) // CUT EDGE
					IS_BRIDGE(v, to);
			}
		}
	if(p == -1 && children > 1) // CUT VERTICE
		IS_CUTPOINT(v);
}
void find_cutpoints() { // CUT VERTICE
	timer = 0;
	visited.assign(n, false);
	tin.assign(n, -1);
	low.assign(n, -1);
	for (int i = 0; i < n; ++i) {
		if (!visited[i])
			dfs (i);
	}
}
void find_bridges() { // CUT EDGE
	timer = 0;
	visited.assign(n, false);
	tin.assign(n, -1);
	low.assign(n, -1);
	for (int i = 0; i < n; ++i) {
		if (!visited[i])
			dfs(i);
	}
}
