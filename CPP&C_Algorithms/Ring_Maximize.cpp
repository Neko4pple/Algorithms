#include <stdio.h>
#include <stdbool.h>

#define MAX_COLORS 25
#define MAX_N 35
#define MAX_BASKET_SIZE 5

struct Basket {
    int colors[MAX_COLORS + 1]; // 각 색깔의 반지 개수
    int num_rings; // 바구니에 들어있는 반지 개수
};

int max(int a, int b) {
    return a > b ? a : b;
}

bool is_pocket_full(struct Basket basket) {
    return basket.num_rings == MAX_BASKET_SIZE;
}

int dfs(struct Basket basket, int rings[4][MAX_N], int idx, int n, int memo[MAX_N]) {
    if (idx == n || is_pocket_full(basket)) return 0;
    if (memo[idx] != -1) return memo[idx];

    int max_rings = 0;
    for (int i = 0; i < 4; i++) {
        int color = rings[i][idx];
        if (basket.colors[color] < 2) {
            basket.colors[color]++;
            basket.num_rings++;
            max_rings = max(max_rings, 1 + dfs(basket, rings, idx, n, memo));
            basket.colors[color]--; // 백트래킹
            basket.num_rings--;
        } else {
            basket.colors[color] -= 2;
            max_rings = max(max_rings, dfs(basket, rings, idx + 1, n, memo));
            basket.colors[color] += 2; // 백트래킹
        }
    }

    memo[idx] = max_rings;
    return max_rings;
}

int main() {
    int n;
    scanf("%d", &n);

    int rings[4][MAX_N];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &rings[i][j]);
        }
    }

    struct Basket basket = { {0}, 0 };
    int memo[MAX_N]; // 메모이제이션을 위한 배열 초기화
    for (int i = 0; i < MAX_N; i++) {
        memo[i] = -1;
    }

    int result = dfs(basket, rings, 0, n, memo);
    printf("%d\n", result);

    return 0;
}
