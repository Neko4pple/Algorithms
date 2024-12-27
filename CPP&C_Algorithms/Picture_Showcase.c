#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    char type;
    int order;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x)
        return p1->x - p2->x;
    else
        return p1->type - p2->type;
}

int main() {
    int n;
    scanf("%d", &n);

    Point *points = (Point *)malloc(sizeof(Point) * n * 2);
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        points[2 * i].x = l;
        points[2 * i].type = 'L';
        points[2 * i].order = i;
        points[2 * i + 1].x = r + 1;
        points[2 * i + 1].type = 'R';
        points[2 * i + 1].order = i;
    }

    qsort(points, n * 2, sizeof(Point), compare);

    int *poped = (int *)calloc(n, sizeof(int));
    int *counted = (int *)calloc(n, sizeof(int));
    int sol = 0;

    int hq_size = 0;
    int *hq = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n * 2; i++) {
        int x = points[i].x;
        char type = points[i].type;
        int order = points[i].order;

        if (type == 'L') {
            hq[hq_size++] = -order;
            for (int j = hq_size - 1; j > 0 && hq[j] < hq[j - 1]; j--) {
                int temp = hq[j];
                hq[j] = hq[j - 1];
                hq[j - 1] = temp;
            }
        } else if (type == 'R') {
            poped[order] = 1;
        }

        if (i == n * 2 - 1 || x != points[i + 1].x) {
            while (hq_size > 0) {
                int top = -hq[0];
                if (!poped[top]) {
                    break;
                }
                for (int j = 0; j < hq_size - 1; j++) {
                    hq[j] = hq[j + 1];
                }
                hq_size--;
            }

            int top = -hq[0];
            if (!counted[top] && !poped[top]) {
                sol++;
                counted[top] = 1;
            }
        }
    }

    printf("%d\n", sol);

    free(points);
    free(poped);
    free(counted);
    free(hq);

    return 0;
}
