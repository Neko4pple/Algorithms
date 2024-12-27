#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// 주사위의 모든 24가지 회전을 생성하는 함수
vector<vector<int>> rotate_dice(const vector<int>& dice) {
    vector<vector<int>> rotations;
    vector<int> a = dice;
    
    // 주사위의 24가지 회전
    for (int i = 0; i < 6; ++i) {
        if (i == 1) swap(a[0], a[1]), swap(a[1], a[5]), swap(a[5], a[4]); // 상하 교체
        if (i == 2) swap(a[0], a[2]), swap(a[2], a[5]), swap(a[5], a[3]); // 상하 교체
        if (i == 3) swap(a[0], a[3]), swap(a[3], a[5]), swap(a[5], a[2]); // 상하 교체
        if (i == 4) swap(a[0], a[4]), swap(a[4], a[5]), swap(a[5], a[1]); // 상하 교체
        if (i == 5) swap(a[0], a[5]), swap(a[5], a[1]), swap(a[1], a[4]); // 상하 교체
        
        for (int j = 0; j < 4; ++j) {
            rotations.push_back(a);
            swap(a[1], a[2]), swap(a[2], a[4]), swap(a[4], a[3]); // 앞면 회전
        }
    }
    return rotations;
}

// 주사위의 정규화된 표현을 반환하는 함수
vector<int> canonical_dice(const vector<int>& dice) {
    auto rotations = rotate_dice(dice);
    return *min_element(rotations.begin(), rotations.end());
}

// 서로 다른 주사위의 수를 세는 함수
int count_unique_dice(const vector<vector<int>>& dices) {
    set<vector<int>> unique_dice;
    for (const auto& dice : dices) {
        unique_dice.insert(canonical_dice(dice));
    }
    return unique_dice.size();
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> dices(n, vector<int>(6));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            cin >> dices[i][j];
        }
    }
    
    cout << count_unique_dice(dices) << endl;
    
    return 0;
}
