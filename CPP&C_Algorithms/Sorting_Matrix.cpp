#include <iostream>

using namespace std;

// 두 변수의 값을 바꾸는 함수
void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

// 내림차순으로 정렬하는 함수
void sort(int array[], int array_size) {
    for (int a = 0; a < array_size; a++) {
        for (int i = 0; i < array_size - 1; i++) {
            if (array[a] > array[i]) {
                swap(array[a], array[i]);
            }
        }
    }
}

int main() {
    int A[] = {4, 2, 3, 1, 5};
    int A_size = 5;
    sort(A, A_size);

    // 정렬된 배열 출력
    cout << "내림차순으로 정렬된 배열: ";
    for (int i = 0; i < A_size; i++) {
        cout << A[i] << " ";
    }

    cout << endl;
    return 0;
}
