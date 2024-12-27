#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int answer = 0;
bool**** piles;
int *endpos[4];

void result(int** rings, int basket[], int remaining_rings, int couples, int piles_temporary[]) {
	int piles_copy_temporary[4];
	int updated_basket[25];
	int *updated_rings[4];
	
	if (remaining_rings == 0) {
		answer = max(answer, couples);
		return;
	} else {
		remaining_rings = remaining_rings - 1;
	}
	for (int i = 0; i < 4; i++) {
		// 각줄의 반지를 번갈아가면서 하나씩 뺴보면서 확인
		memcpy(piles_copy_temporary, piles_temporary, sizeof(piles_copy_temporary));
		piles_copy_temporary[i] += 1;
		if (piles[piles_copy_temporary[0]][piles_copy_temporary[1]][piles_copy_temporary[2]][piles_copy_temporary[3]]) {
			// piles에 이미 확인한 경우일 경우 재귀를 진행하지 않음
			continue;
		} else {
			// piles에 없을 경우 추가
			piles[piles_copy_temporary[0]][piles_copy_temporary[1]][piles_copy_temporary[2]][piles_copy_temporary[3]] = true;
		}
		memcpy(updated_basket, basket, sizeof(updated_basket));
		
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
	answer = max(answer, couples);
}

int main() {
	int n;
	int piles_temporary[4] = {0};
	int basket[25] = {0};
	int *rings[4];
	
	scanf("%d", &n);
	
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
	
	for (int i = 0; i < 4; i++) {
		rings[i] = (int*)malloc(sizeof(int) * n);
		endpos[i] = &rings[i][n];
	}
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &rings[0][i], &rings[1][i], &rings[2][i], &rings[3][i]);
	}
	
	result(rings, basket, 5, 0, piles_temporary);
	
	printf("%d", answer * 2);

	return 0;
}