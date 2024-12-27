#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Conference_Room {
    int W; // tables in a row
    int H; // number of rows

public:
    virtual void Two_D_Array(int W, int H) = 0; // 2D array 구현 함수(virtual)
};

class One_Cell {
    int M; // 가로길이
    int N; // 세로길이

public:
    virtual void One_Cell_default(int M, int N, const vector<vector<int>>& source) = 0;
};

class Filler : public One_Cell, public Conference_Room {
public:
    virtual void One_Cell_default(int Q, int W, const vector<vector<int>>& source) override {
        vector<vector<int>> cell(Q, vector<int>(W, 0)); // 2D 벡터로 One_Cell의 배열 생성

        // Two_D_Array 배열을 One_Cell_default 배열로 복사
        for (int i = 0; i < Q; ++i) {
            for (int j = 0; j < W; ++j) {
                cell[i][j] = source[i][j];
            }
        }

        // 복사된 배열을 사용하여 필요한 작업 수행
    }

    virtual void Two_D_Array(int O, int P) override {
        vector<vector<int>> conf(O, vector<int>(P, 0)); // 2D 벡터로 Conference_Room의 배열 생성

        // Two_D_Array 배열을 채우는 작업 수행

        // One_Cell_default 호출
        One_Cell_default(O, P, conf);
    }
};

int main() {
    int W, H, M, N;

    cout << "Enter number of rows, tables in a row, vertical length, and horizontal length: ";
    cin >> H >> W >> N >> M;

    Filler filler;
    filler.Two_D_Array(W, H); // WxH 크기의 Two_D_Array 호출

    return 0;
}
