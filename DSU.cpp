class DSU {
public:
	int n;
	vector<int>parent;
	vector<int>sz;
	int root(int node) {
		if (parent[node] == node)return node;
		return parent[node] = root(parent[node]);//path compression optimization
	}
	DSU(int n) {
		this->n = n;
		parent.resize(n + 1);
		sz.resize(n + 1);
		for (int i = 1; i <= n ; ++i) {
			parent[i] = i;
			sz[i] = 1;
		}
	}
	int find(int v) {
		return root(v);
	}
	void unionn(int u , int v) {
		int ru = root(u);
		int rv = root(v);
		if (ru == rv)return;
		if (sz[ru] > sz[rv]) {//Union by size optimization
			swap(ru, rv);
		}
		parent[ru] = rv;
		sz[rv] += sz[ru];
	}
};
