#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647 // 최대 정수
#define MAX_VERTICES 7  // 정점의 수
#define INF 1000    // 무한대 (연결이 없는 경우)

int weight[MAX_VERTICES][MAX_VERTICES] = {
  {0,7,INF,INF,3,10,INF},
  {7,0,4,10,2,6,INF},
  {INF,4,0,2,INF,INF,INF},
  {INF,10,2,0,11,9,4},
  {3,2,INF,11,0,INF,5},
  {10,6,INF,9,INF,0,INF},
  {INF,INF,INF,4,5,INF,0}
};
/* Dijkstra 변수*/
int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int route[MAX_VERTICES];
int select(int distance[], int n, int found[]) {
    int min;
    int min_pos;
    min = INT_MAX;
    min_pos = -1;
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && found[i] == 0) {
            min = distance[i];
            min_pos = i;
        }
    }
    return min_pos;
}

void Shortest_Path(int start, int n) {
    // Dijkstra 알고리즘으로 최단 경로를 구한다.
    // 시작 정점으로부터 그래프 내의 모든 정점에 대한 최단 경로를 구합니다.

    for (int i = 0; i < n; i++)
    {
        distance[i] = weight[start][i]; // 시작 정점에서 다른 정점으로 향하는 가중치를 기준으로 초기화합니다.
        found[i] = 0;
    }
        found[start] = 1;
    for (int i = 0; i < n - 1; i++) {
        int u = select(distance, n, found);
        // 최단 경로가 발견되지 않고, 시작 정점과의 거리가 가장 짧은 정점을 반환합니다.
        found[u] = 1; // 해당 정점을 그래프에 포합합니다.

        printf("%d is added to the Graph\n\n", u);
        route[i+1] = u;

        for (int j = 0; j < n; j++) {
            if (found[j] == 0) {
                if (distance[u] + weight[u][j] < distance[j]) {
                    // 시작 정점에서 j로 바로 가는게 빠를지, u를 경유해서 가는게 빠를지 판단 합니다.
                    printf("Before_distance update via[%d]: distance[%d] = %d\n", u, j, distance[j]);
                    distance[j] = distance[u] + weight[u][j];
                    printf("After_distance update via[%d]: distance[%d] = %d\n\n", u, j, distance[j]);
                }
            }
        }
    }
}

int main(void) {
    Shortest_Path(0, MAX_VERTICES);
    for(int i = 0; i< MAX_VERTICES; i++){
      printf("%d ", route[i]);
    }
      printf("\n");

      return 0;
}
