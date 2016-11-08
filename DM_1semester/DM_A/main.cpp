#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int n;

vector<vector<int>> a;

deque<int> queue;
/*
void revese(int i, int j) {
    int temp = i + (j - i + 1) / 2 + 1;
    for (int k = i; k <= temp; k++) {
        int t = queue[k];
        queue[k] = queue[j - (k - i)];
        queue[j - (k - i)] = t;
    }
}
void move() {
   // int res = queue.front();
    for (int i = 0; i < queue.size() - 1; i++) {
        queue[i] = queue[i + 1];
    }
    queue.pop_back();
    //return res;
}
*/
void findHamiltonCycle() {
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        queue.push_back(i);
    }
    for (int k = 0; k < n * (n - 1); k++) {
        if (!a[queue[0]][queue[1]]) {
            int i = 2;
            cur = 0;
            while (!a[queue[0]][queue[i]] || !a[queue[1]][queue[i + 1]]) {
                i++;
            }
            reverse(queue.begin() + 1, queue.begin() + i + 1);
        } else {
            cur++;
            if (cur > n) {
                break;
            }
        }
        queue.push_back(queue[0]);
        queue.pop_front();
        //move();
    }
}

int main() {
    ifstream in;
    ofstream out;
    in.open("fullham.in", ios::in);
    out.open("fullham.out", ios::out);

    in >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            a[i].push_back(0);
        }
    }
    char t;
    /*in >> t;
    in >> t;
*/
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i - 1; j++) {
            in >> t;
            //int q= t - '0';
            a[j][i] = t - '0';
            a[i][j] = t - '0';
        }
        //in >> t;
    }
    findHamiltonCycle();
    for (int i = 0; i < queue.size(); i++) {
        out << queue[i] << " ";
    }
    in.close();
    out.close();
    return 0;
}