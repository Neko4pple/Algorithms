#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int answer = 0;
vector<vector<vector<vector<bool>>>> dp;
vector<int> dpt;

void result(vector<vector<int>>& d, vector<int>& b, int n, int a) {
    if (n == 0) {
        answer = max(answer, a);
        return;
    }

    for (int i = 0; i < 4; i++) {
        vector<int> dptt = dpt;
        dptt[i]++;
        if (dp[dptt[0]][dptt[1]][dptt[2]][dptt[3]]) continue;
        dp[dptt[0]][dptt[1]][dptt[2]][dptt[3]] = true;

        vector<int> bt = b;
        vector<vector<int>> dt = d;

        if (!dt[i].empty()) {
            int temp = dt[i][0] - 1;
            dt[i].erase(dt[i].begin());
            if (bt[temp] == 1) {
                bt[temp] = 0;
                result(dt, bt, n + 2, a + 1);
            } else {
                bt[temp]++;
                result(dt, bt, n, a);
            }
        }
    }
    answer = max(answer, a);
}

int main() {
    int n;
    cin >> n;
    dpt.assign(4, 0);
    dp.assign(n + 2, vector<vector<vector<bool>>>(n + 2, vector<vector<bool>>(n + 2, vector<bool>(n + 2, false))));
    vector<vector<int>> d(4, vector<int>(n));
    vector<int> b(25, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 4; j++)
            cin >> d[j][i];

    result(d, b, 5, 0);
    cout << answer * 2 << endl;
    return 0;
}
