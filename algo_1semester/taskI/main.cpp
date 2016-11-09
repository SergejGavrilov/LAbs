#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef vector<vector<pair<int, int>>> graph;
typedef vector<pair<int, int>>::const_iterator const_graph_iter;

vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<bool> lca_dfs_used;

vector<pair<int, int>> nodes;


void lca_dfs(const graph &g, int v, int h = 1) {
    lca_dfs_used[v] = true;
    lca_h[v] = h;
    lca_dfs_list.push_back(v);
    for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i) {
        if (!lca_dfs_used[(*i).first]) {
            lca_dfs(g, (*i).first, h + 1);
            lca_dfs_list.push_back(v);
        }
    }
}

void lca_build_tree(int i, int l, int r) {
    if (l == r) {
        lca_tree[i] = lca_dfs_list[l];
    } else {
        int m = (l + r) >> 1;
        lca_build_tree(i * 2, l, m);
        lca_build_tree(i * 2 + 1, m + 1, r);
        if (lca_h[lca_tree[i * 2]] < lca_h[lca_tree[i * 2 + 1]]) {
            lca_tree[i] = lca_tree[i * 2];
        } else {
            lca_tree[i] = lca_tree[i * 2 + 1];
        }
    }
}

void lca_prepare(const graph &g, int root) {

    int n = g.size();
    lca_h.resize(n);
    lca_dfs_list.reserve(n * 2);
    lca_dfs_used.assign(n, false);

    lca_dfs(g, root);

    int m = (int) lca_dfs_list.size();
    lca_tree.assign(m * 4 + 1, -1);

    lca_build_tree(1, 0, m - 1);
    lca_first.assign(n, -1);
    for (int i = 0; i < m; i++) {
        int v = lca_dfs_list[i];
        if (lca_first[v] == -1) {
            lca_first[v] = i;
        }
    }
}

int lca_tree_min(int i, int sl, int sr, int l, int r) {
    if (sl == l && sr == r) {
        return lca_tree[i];
    }
    int sm = (sl + sr) >> 1;
    if (r <= sm) {
        return lca_tree_min(i * 2, sl, sm, l, r);
    }
    if (l > sm) {
        return lca_tree_min(i + i + 1, sm + 1, sr, l, r);
    }
    int ans1 = lca_tree_min(i + i, sl, sm, l, sm);
    int ans2 = lca_tree_min(i + i + 1, sm + 1, sr, sm + 1, r);
    return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca(int a, int b) {
    int left = lca_first[a],
            right = lca_first[b];
    if (left > right) swap(left, right);
    return lca_tree_min(1, 0, (int) lca_dfs_list.size() - 1, left, right);
}

int lca_way(vector<vector<int>> matrix, int a, int b) {
    int ans = 0;
    int left = lca_first[a];
    int right = lca_first[b];
    if (left > right) swap(left, right);
    for (int k = left; k != right; k++) {
        ans += matrix[lca_dfs_list[k]][lca_dfs_list[k + 1]];
    }
    return ans;
}


int main() {
    ifstream in;
    ofstream out;
    in.open("tree.in", ios::in);
    out.open("tree.out", ios::out);
    int n;
    in >> n;
    graph g(n);
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    int root = 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        in >> u >> v >> w;
        g[v].push_back(make_pair(u, w));
        matrix[v][u] = w;
        matrix[u][v] = w;
    }
    lca_prepare(g, root);
    int m;
    in >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;
        out << lca_way(matrix, x, y) << endl;
    }
    in.close();
    out.close();
    return 0;
}