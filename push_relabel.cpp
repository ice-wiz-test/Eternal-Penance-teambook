#include <bits/stdc++.h>
using namespace std;

struct max_flow_relabel {
	// MAX-FLOW-RELABEL algorithm, Runtime - O(N^2sqrt(M) + NM) (N^3)
	// requires namespace std and include bits/stdc++.h, no defines;
	// tested on - https://open.kattis.com/problems/maxflow; time spent - 0.95 seconds.
private:
	int32_t sz = 0;
	bool has_calced_ans = false;
	int32_t slvS = -1;
	int32_t slvT = -1;
	int64_t FLOW_INF = 1e18;
	vector<vector<int64_t>> cap;
	vector<vector<int64_t>> flow;
	vector<int64_t> h;
	vector<int64_t> exc;
	queue<int64_t> q;
	void push(int32_t u, int32_t v) {
		int64_t max_give = min(exc[u], cap[u][v] - flow[u][v]);
		flow[u][v] += max_give;
		flow[v][u] -= max_give;
		exc[u] -= max_give;
		exc[v] += max_give;
	}
	void relabel(int u) {
		int64_t cd = FLOW_INF;
		for (int j = 0; j < sz; ++j) {
			if (cap[u][j] - flow[u][j] > 0) {
				cd = min(cd, h[j]);
			}
		}
		if (cd < FLOW_INF) {
			h[u] = cd + 1;
		}
	}
	vector<int64_t> find_max_height_vertices(int32_t s, int32_t t) {
		vector<int64_t> mheight;
		for (int32_t i = 0; i < sz; ++i) {
			if (i == s || i == t || exc[i] == 0) continue;
			if (!mheight.empty() && h[mheight.back()] < h[i]) mheight.clear();
			if (mheight.empty() || h[mheight.back()] == h[i]) mheight.push_back(i);
		}
		return mheight;
	}
public:
	max_flow_relabel() {}
	int64_t max_flow(int s, int t) { // main function; calculates maximum flow between s and t
		h[s] = sz;
		exc[s] = FLOW_INF;
		for (int i = 0; i < sz; ++i) {
			if (i != s) {
				push(s, i);
			}
		}
		vector<int64_t> curr;
		while (true) {
			curr = find_max_height_vertices(s, t);
			if (curr.empty()) break;
			for (int32_t current_vert : curr) {
				bool psh = false;
				for (int32_t j = 0; j < sz && exc[current_vert] != 0; ++j) {
					if (cap[current_vert][j] - flow[current_vert][j] > 0 && h[current_vert] == h[j] + 1) {
						push(current_vert, j);
						psh = true;
					}
				}
				if (!psh) {
					relabel(current_vert);
					break;
				}
			}
		}
		int64_t ans = 0;
		for (int32_t j = 0; j < sz; ++j) {
			ans += flow[j][t];
		}
		has_calced_ans = true;
		slvS = s;
		slvT = t;
		return ans;
	}
	vector<pair<pair<int32_t, int32_t>, int64_t>> flow_edges(int S, int T) { // gets all the non-empty flow edges between s and t
		vector<pair<pair<int32_t, int32_t>, int64_t>> ret;
		if (!has_calced_ans || slvS != S || slvT != T) max_flow(S, T);
		for (int j = 0; j < sz; ++j) {
			for (int k = 0; k < sz; ++k) {
				if (flow[j][k] > 0) ret.push_back({ {j, k}, flow[j][k] });
			}
		}
		return ret;
	}
	void init(int SZ) { // has to be called before all functions; resizes the graph
		sz = SZ;
		cap.assign(SZ, vector<int64_t>(SZ, 0));
		flow.assign(SZ, vector<int64_t>(SZ, 0));
		exc.assign(SZ, 0);
		h.assign(SZ, 0);
	}
	void add_edge(int32_t u, int32_t v, int64_t CAP) { // adds an edge between u and v with capacity CAP
		cap[u][v] += CAP;
		has_calced_ans = false;
	}
};