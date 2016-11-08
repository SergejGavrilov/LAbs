#include <iostream>
#include <vector>

using namespace std;

vector<int> answer;
int curPos;

bool binary_search(int i) {
    int l = -1;
    int r = answer.size();
    int mid;
    string s;
    while (l < r - 1) {
        mid = (r + l) / 2;
        cout << "1 " << answer[mid] << " " << i << endl;
        cout.flush();
        cin >> s;
        if (s == "YES") {
            l = mid;
        } else {
            r = mid;
        }
    }
    curPos = mid;
    if (s == "YES")
        return true;
    else
        return false;
}


int main() {
    answer.push_back(1);

    int n;
    cin >> n;

    for (int i = 2; i <= n; i++) {

        if (binary_search(i)) {
            answer.insert(answer.begin() + curPos + 1, i);
        } else {
            answer.insert(answer.begin() + curPos, i);
        }

    }
    cout << "0 ";
    for (int i = 1; i <= n; i++) {
        cout << answer[i - 1] << " ";
    }
    return 0;
}