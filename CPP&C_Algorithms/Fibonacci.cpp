#include <iostream>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n;

    // 사용자로부터 피보나치 수열의 길이 입력 받기
    std::cout << "피보나치 수열의 길이를 입력하세요: ";
    std::cin >> n;

    // 피보나치 수열 출력
    std::cout << "피보나치 수열: ";
    for (int i = 0; i < n; ++i) {
        std::cout << fibonacci(i) << " ";
    }

    return 0;
}
