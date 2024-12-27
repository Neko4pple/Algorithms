#include <stdio.h>

#define MAX_COLORS 25
#define MAX_HEIGHT 35

int main() {
    int n;
    int piles[4][MAX_COLORS + 1] = {0}; // 각 더미에 있는 반지의 개수를 색깔별로 저장하는 배열
    int basket[MAX_COLORS + 1] = {0}; // 바구니에 있는 반지의 개수를 색깔별로 저장하는 배열
    int count = 0; // 주머니에 옮긴 반지의 개수

    // 더미의 높이 입력
    scanf("%d", &n);

    // 반지의 색상 입력과 동시에 색깔별 개수 카운트
    for (int i = 0; i < n; i++) {
        int color1, color2, color3, color4;
        scanf("%d %d %d %d", &color1, &color2, &color3, &color4);
        piles[0][color1]++;
        piles[1][color2]++;
        piles[2][color3]++;
        piles[3][color4]++;
    }

    // 모든 반지를 옮길 때까지 반복
    while (1) {
        int max_pair = 0; // 옮길 수 있는 최대 반지 쌍의 개수
        int max_pile = -1; // 가장 많은 반지 쌍을 갖고 있는 더미의 인덱스

        // 각 더미에 대해 가장 많은 반지 쌍을 가진 더미 찾기
        for (int i = 0; i < 4; i++) {
            int pairs = 0;
            // 각 색상에 대해 반지 쌍의 개수 세기
            for (int j = 1; j <= MAX_COLORS; j++) {
                int pair = piles[i][j] / 2;
                pairs += pair;
            }
            // 가장 많은 반지 쌍을 가진 더미 저장
            if (pairs > max_pair) {
                max_pair = pairs;
                max_pile = i;
            }
        }

        // 만약 더 이상 반지를 옮길 수 없으면 종료
        if (max_pair == 0)
            break;

        // 주머니에 반지를 옮기기
        for (int j = 1; j <= MAX_COLORS; j++) {
            int pair = piles[max_pile][j] / 2;
            basket[j] += pair;
            piles[max_pile][j] -= pair * 2;
        }

        count += max_pair; // 주머니에 옮긴 반지의 개수 업데이트
    }

    // 주머니에 옮긴 반지의 개수 출력
    printf("%d\n", count);

    return 0;
}
