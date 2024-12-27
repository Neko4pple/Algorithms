#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

// 전역 변수 선언
int answer = 0;             // 최종 결과
bool**** piles;             // 4차원 배열 포인터. 메모리에 특정 링이 있는지 여부를 저장
int *endpos[4];             // 링 배열의 각 포인터가 끝을 나타내는 포인터 배열

// 결과 계산 함수
void result(int** rings, int basket[], int remaining_rings, int couples, int piles_temporary[]) {
    int piles_copy_temporary[4];        // 임시 저장소
    int updated_basket[25];             // 갱신된 바구니
    int *updated_rings[4];              // 갱신된 링 배열
    
    if (remaining_rings == 0) {         // 모든 링을 처리했을 때
        answer = max(answer, couples);  // 결과 업데이트
        return;
    } else {
        remaining_rings = remaining_rings - 1;   // 남은 링 감소
    }
    for (int i = 0; i < 4; i++) {
        memcpy(piles_copy_temporary, piles_temporary, sizeof(piles_copy_temporary));  // 임시 저장소 복사
        piles_copy_temporary[i] += 1;      // 해당 위치의 링 쌓기
        if (piles[piles_copy_temporary[0]][piles_copy_temporary[1]][piles_copy_temporary[2]][piles_copy_temporary[3]]) {
            continue;       // 이미 해당 위치에 링이 있는 경우 건너뜀
        } else {
            piles[piles_copy_temporary[0]][piles_copy_temporary[1]][piles_copy_temporary[2]][piles_copy_temporary[3]] = true;
        }
        memcpy(updated_basket, basket, sizeof(updated_basket));   // 바구니 갱신
        
        updated_rings[0] = rings[0];
        updated_rings[1] = rings[1];
        updated_rings[2] = rings[2];
        updated_rings[3] = rings[3];
        if (!(updated_rings[i] == endpos[i])) {
            int ring_color = updated_rings[i][0] - 1;
            updated_rings[i]++;
            if (updated_basket[ring_color] == 1) {
                updated_basket[ring_color] = 0;
                result(updated_rings, updated_basket, remaining_rings + 2, couples + 1, piles_copy_temporary);
            } else {
                updated_basket[ring_color] += 1;
                result(updated_rings, updated_basket, remaining_rings, couples, piles_copy_temporary);
            }
        }
    }
    answer = max(answer, couples);      // 최종 결과 업데이트
}

int main() {
    int n;
    int piles_temporary[4] = {0};       // 링이 쌓인 피라미드 위치 임시 저장 배열
    int basket[25] = {0};               // 각 색깔의 링 개수를 나타내는 바구니
    int *rings[4];                      // 4가지 색깔의 링 배열
    
    scanf("%d", &n);                    // 링의 개수 입력
    
    // 메모리 할당
    piles = (bool****)malloc(sizeof(bool***) * (n + 2));
    for (int i = 0; i <= (n + 1); i++) {
        piles[i] = (bool***)malloc(sizeof(bool**) * (n + 2));
        for (int j = 0; j <= (n + 1); j++) {
            piles[i][j] = (bool**)malloc(sizeof(bool*) * (n + 2));
            for (int k = 0; k <= (n + 1); k++) {
                piles[i][j][k] = (bool*)malloc(sizeof(bool) * (n + 2));
                for (int l = 0; l <= (n + 1); l++) {
                    piles[i][j][k][l] = false;
                }
            }
        }
    }
    
    // 링 입력
    for (int i = 0; i < 4; i++) {
        rings[i] = (int*)malloc(sizeof(int) * n);
        endpos[i] = &rings[i][n];
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &rings[0][i], &rings[1][i], &rings[2][i], &rings[3][i]);
    }
    
    // 결과 계산
    result(rings, basket, 5, 0, piles_temporary);
    
    printf("%d", answer * 2);          // 결과 출력
    
    return 0;
}
