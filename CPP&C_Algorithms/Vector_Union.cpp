#include <iostream>
#include <vector>

using namespace std;

// 벡터 출력 함수
void printVector(const vector<int>& vec) {
    cout << "{ ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << "}";
}

// 벡터에 원소가 있는지 확인하는 함수
bool contains(const vector<int>& vec, int num) {
    for (int element : vec) {
        if (element == num) {
            return true;
        }
    }
    return false;
}

// 벡터 합집합 계산 함수
vector<int> calculateUnion(const vector<int>& vec1, const vector<int>& vec2, const vector<int>& vec3) {
    // 중복을 허용하지 않는 set을 사용하여 합집합 계산
    vector<int> result;
    for (int num : vec1) {
        result.push_back(num);
    }
    for (int num : vec2) {
        if (!contains(result, num)) {
            result.push_back(num);
        }
    }
    for (int num : vec3) {
        if (!contains(result, num)) {
            result.push_back(num);
        }
    }
    return result;
}

int main() {
    // 3개의 벡터 수열 입력
    vector<int> vector1, vector2, vector3;
    int num;

    cout << "Input vectors..." << endl;

    // 첫 번째 벡터 입력
    cout << "첫 번째 벡터 원소 입력 (띄어쓰기로 구분, 입력이 끝나면 엔터): ";
    while (cin >> num) {
        vector1.push_back(num);
        if (cin.get() == '\n') break;  // 엔터를 입력하면 루프 탈출
    }

    // 두 번째 벡터 입력
    cout << "두 번째 벡터 원소 입력 (띄어쓰기로 구분, 입력이 끝나면 엔터): ";
    while (cin >> num) {
        vector2.push_back(num);
        if (cin.get() == '\n') break;  // 엔터를 입력하면 루프 탈출
    }

    // 세 번째 벡터 입력
    cout << "세 번째 벡터 원소 입력 (띄어쓰기로 구분, 입력이 끝나면 엔터): ";
    while (cin >> num) {
        vector3.push_back(num);
        if (cin.get() == '\n') break;  // 엔터를 입력하면 루프 탈출
    }

    // 합집합 계산
    vector<int> result = calculateUnion(vector1, vector2, vector3);

    // 결과 출력
    cout << "Union set of input vectors: ";
    printVector(result);

    return 0;
}
