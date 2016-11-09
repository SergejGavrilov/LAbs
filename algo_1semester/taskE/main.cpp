#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int n, l;
vector < vector<int> > g;
vector<int> tin, tout;
int timer;
vector < vector<int> > up;

void dfs (int v, int p = 0) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i=1; i<=l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (to != p)
            dfs (to, v);
    }
    tout[v] = ++timer;
}

bool upper (int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
    if (upper (a, b))  return a;
    if (upper (b, a))  return b;
    for (int i=l; i>=0; --i)
        if (! upper (up[a][i], b))
            a = up[a][i];
    return up[a][0];
}



int main() {
 /*   ifstream in;
    ofstream out;
    in.open("dynamic.in", ios::in);
    out.open("dynamic.out", ios::out);
*/


    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);

    while (true) {
        int n;
  //      in >> n;
        scanf("%d", &n);
        if (n == 0) break;
        graph g;
        int root = 0;
        int m;
        g.resize(n);
        for (int i = 1; i <= n - 1; i++) {
            int x, y;
         //   in >> x >> y;
            scanf("%d %d", &x, &y);
            g[x - 1].push_back(y - 1);
        }
        //lca_prepare(g, root);
      //  in >> m;
        tin.resize (n),  tout.resize (n),  up.resize (n);
        l = 1;
        while ((1<<l) <= n)  ++l;
        for (int i=0; i<n; ++i)  up[i].resize (l+1);
        dfs (0);

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            char t;
            int x, y;
            scanf(" %c", &t);
            //in >> t;
            if (t == '?') { //find LCA
               // in >> x >> y;
                scanf("%d %d", &x, &y);
                x--, y--;
                int a = lca(x, y);
                if (root == 0) {
                    printf("%d\n", ++a);
 //                   out << a + 1 << endl;
                } else {
                    int b = lca(x, root);
                    int c = lca(y, root);
                    //Choose node with the deepsest level
                    if (lca_h[a] > lca_h[b]) {
                        if (lca_h[a] > lca_h[c]) {
                          //  out << a + 1 << endl;
                            printf("%d\n", ++a);
                        } else {
                            printf("%d\n", ++c);
                            //out << c + 1 << endl;
                        }
                    } else {
                        if (lca_h[b] > lca_h[c]) {
                            printf("%d\n", ++b);
                           // out << b + 1 << endl;
                        } else {
                            printf("%d\n", ++c);
                           // out << c + 1 << endl;
                        }
                    }
                }
            } else { //change root
               // in >> x;
                scanf("%d", &x);
                root = --x;
            }
        }
        g.clear();
        lca_h.clear();
        lca_dfs_list.clear();
        lca_tree.clear();
        lca_dfs_used.clear();
        lca_first.clear();
    }

    fclose(stdin);
    fclose(stdout);
   /* in.close();
    out.close();*/
    return 0;
}