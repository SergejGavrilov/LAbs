#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<char> used;
vector<vector<int>> g;
vector<int> mt;

int n, m, k, count = 0;

bool try_kuhn(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}



int main() {
    std::ifstream in;
    ofstream out;
    in.open("matching.in", ios_base::in);
    out.open("matching.out", ios_base::out);

    in >> n >> m >> k;
    g.resize(n);
    mt.assign(m, -1);
    for (int i = 0; i < k; i++) {
        int a, b;
        in >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
    }
    for (int i = 0; i < n; i++) {
        used.assign(n, false);
        if (try_kuhn(i))
            count++;
    }
    out << count;
    return 0;
}