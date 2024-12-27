#include <stdio.h>
#include <stdlib.h>

int n;
int* rings[4];
int basket[5] = {0};

bool DepthCheck(int top[]) {
    for (int i = 0; i < 4; i++) {
        if (top[i] < n) return true;
    }
    return false;
}

void BasketCheck(int& couples) {
    int color[21] = {0};
    int basket_indices[5] = {0};

    for (int i = 0; i < 5; i++) {
        if (basket[i]) {
            int basket_color = basket[i];
            if (color[basket_color]) {
                basket_indices[color[basket_color]] = i;
                couples++;
            } else {
                color[basket_color] = i + 1;
            }
        }
    }

    for (int i = 1; i <= 20; i++) {
        if (color[i] && basket_indices[color[i]] && color[i] != basket_indices[color[i]]) {
            int index1 = color[i] - 1;
            int index2 = basket_indices[color[i]] - 1;
            basket[index1] = 0;
            basket[index2] = 0;
            color[i] = 0;
        }
    }
}

int BestPile(int top[]) {
    int shortest_search = 5;
    int pickup_pile = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            if (rings[j][i]) {
                int distance = i + 1 - top[j];
                if (basket[rings[j][i]]) distance++;
                if (distance < shortest_search) {
                    shortest_search = distance;
                    pickup_pile = j;
                }
                break;
            }
        }
    }
    
    return pickup_pile;
}

int dfs() {
    int top[4] = {0};
    int couples = 0;

    while (DepthCheck(top)) {
        BasketCheck(couples);

        int pile = BestPile(top);
        if (pile == -1) break;
        
        for (int i = 0; i < 5; i++) {
            if (!basket[i]) {
                basket[i] = rings[pile][top[pile]];
                break;
            }
        }
        rings[pile][top[pile]] = 0;
        top[pile]++;
    }

    return couples;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < 4; i++) {
        rings[i] = (int*)malloc(sizeof(int) * n);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &rings[j][i]); // 여기 수정되어야 함
        }
    }

    printf("%d", dfs());
    
    return 0;
}
