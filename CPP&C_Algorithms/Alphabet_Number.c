#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 구조체 정의
typedef struct {
    int pos;
    int cost;
} DPNode;

int main() {
    int obsnum;
    scanf("%d", &obsnum);

    // 장애물 배열 동적 할당
    int (*obstacle)[2] = malloc(sizeof(int[obsnum][2]));

    // 장애물 정보 입력
    for (int i = 0; i < obsnum; i++) {
        scanf("%d %d", &obstacle[i][0], &obstacle[i][1]);
    }

    // DP 배열 동적 할당 및 초기화
    DPNode *dp = malloc(sizeof(DPNode));
    dp[0].pos = 0;
    dp[0].cost = 0;

    // DP 연산
    for (int i = 0; i < obsnum; i++) {
        int dp_len = sizeof(dp) / sizeof(dp[0]);
        DPNode *new_dp = malloc(sizeof(DPNode) * dp_len * 2);

        for (int j = 0; j < dp_len; j++) {
            int left_dist = abs(obstacle[i][0] - dp[j].pos);
            int right_dist = abs(obstacle[i][1] - dp[j].pos);
            int new_left_cost = dp[j].cost + left_dist;
            int new_right_cost = dp[j].cost + right_dist;

            new_dp[j * 2].pos = obstacle[i][0];
            new_dp[j * 2].cost = new_left_cost;

            new_dp[j * 2 + 1].pos = obstacle[i][1];
            new_dp[j * 2 + 1].cost = new_right_cost + abs(obstacle[i][1] - obstacle[i][0]);
        }

        free(dp);
        dp = new_dp;
    }

    // 최소 비용 계산
    int min_cost = dp[0].cost;
    for (int i = 1; i < sizeof(dp) / sizeof(dp[0]); i++) {
        if (dp[i].cost < min_cost) {
            min_cost = dp[i].cost;
        }
    }

    // 최종 결과 출력
    int result = min_cost + obsnum + 1;
    printf("%d\n", result);

    // 동적 할당 해제
    free(obstacle);
    free(dp);

    return 0;
}
