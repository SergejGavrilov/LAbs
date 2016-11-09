#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef vector<vector<int>> graph;
typedef vector<int>::const_iterator const_graph_iter;

vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<bool> lca_dfs_used;

int n;

void lca_dfs(const graph &g, int v, int h = 1) {
    lca_dfs_used[v] = true;
    lca_h[v] = h;
    lca_dfs_list.push_back(v);
    for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i) {
        if (!lca_dfs_used[*i]) {
            lca_dfs(g, *i, h + 1);
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

    lca_h.assign(n, 0);
    lca_dfs_list.resize(0);
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

int main() {
    ifstream in;
    ofstream out;
    in.open("ancestor.in ", ios::in);
    out.open("ancestor.out", ios::out);

    in >> n;
    graph g;
    int root;
    int m;
    g.assign(n, vector<int>(0));

    for (int i = 0; i < n; i++) {
        int x;
        in >> x;
        if (x == 0)
            root = i;
        else
            g[x - 1].push_back(i - 1);
    }
    lca_prepare(g, root);
    in >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        in >> a >> b;
        if (lca(--a, --b) == --a) {
            out << 1 << endl;
        } else {
            out << 0 << endl;
        }
    }
    in.close();
    out.close();
    return 0;
}