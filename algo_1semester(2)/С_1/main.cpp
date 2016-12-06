#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <climits>

#define V 500

using namespace std;
/*
int capacities[501][501];
int flowPassed[501][501];
vector<int> graph[501];
int parentsList[501];
int currentPathCapacity[501];

*/
/*
int capacities[10][10];
int flowPassed[10][10];
vector<int> graph[10];
int parentsList[10];
int currentPathCapacity[10];
*/
int count = 0, n;

vector<int> answer;

int bfs(int *rGraph[], int start, int end, int parent[]) {

    bool visited[n];
    memset(visited, 0, sizeof(visited));
   /* for (int i = 0; i < n; i++)
        visited[i] = false;
*/
    queue<int> q;
    q.push(start);

    visited[start] = true;
    parent[start] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {

            if (visited[v] == false && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[end] == true);
}

void dfs(int *rGraph[], int s, bool visited[]) {
    count++;
    answer.push_back(s + 1);
    visited[s] = true;
    for (int i = 0; i < n; i++)
        if (rGraph[s][i] && !visited[i]) {
            dfs(rGraph, i, visited);

        }
}


void minCut(int *graph[], int s, int t) {
    int u, v;

    int *rGraph[n];
    for (int i = 0; i < n; i++) {
        rGraph[i] = new int[n];
    }
    for (u = 0; u < n; u++) {
        for (v = 0; v < n; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[n];

    while (bfs(rGraph, s, t, parent)) {

        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
    }
    bool visited[n];

    memset(visited, false, sizeof(visited));
   /* for (int i = 0; i < n; i++)
        visited[i] = false;*/
    dfs(rGraph, s, visited);

}


int main() {
    int m;
    /*
    std::ifstream in;
    ofstream out;
    in.open("cut.in", ios_base::in);
    out.open("cut.out", ios_base::out);

    in >> n >> m
     */;
    FILE *file;
    FILE *fout;
    file = fopen("cut.in", "r");
    fout = fopen("cut.out", "w");
    fscanf(file, "%d%d", &n, &m);
    int *graph[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        fscanf(file, "%d%d%d", &a, &b, &c);
        //in >> a >> b >> c;
        a--;
        b--;
        graph[a][b] = c;
        graph[b][a] = c;
    }
    minCut(graph, 0, n - 1);
    //out << count << endl;
    fprintf(fout, "%d\n", count);

    //out << i + 1 << " ";
    for (int i = 0; i < answer.size(); i++)
        fprintf(fout, "%d ", answer[i]);

    return 0;
}