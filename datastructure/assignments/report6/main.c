#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647
// 최대 정수
#define MAX 7
// 정점의 수
#define INF 1000
// 연결이 없는 경우에 대한 무한 수

//가중치 배열 초기화
int weight[MAX][MAX] = {
  {0,7,INF,INF,3,10,INF},
  {7,0,4,10,2,6,INF},
  {INF,4,0,2,INF,INF,INF},
  {INF,10,2,0,11,9,4},
  {3,2,INF,11,0,INF,5},
  {10,6,INF,9,INF,0,INF},
  {INF,INF,INF,4,5,INF,0}
};

//최소거리 갱신을 위한 배열 선언
int dst[MAX] = {0};
//방문 여부를 체크하기 위한 배열 선언
int found[MAX] = {0};
//정점의 배열 선언
int route[MAX] = {0};

// 최소가중치를 통한 정점선택 함수
int select(int n) {
    int min;
    int min_pos;
    min = INT_MAX;
    min_pos = -1;
    for (int i = 0; i < n; i++) {
        if (dst[i] < min && found[i] == 0) {
            min = dst[i];
            min_pos = i;
        }
    }
    return min_pos;
}

void Shortest_Path(int start, int n) {
    // Dijkstra 알고리즘으로 최단 경로를 구한다.
    // 그래프 내에 존재하는 모든 경로의 최단 경로를 구한다.

    //그래프에 속한 각 정점에 대하여
    for (int i = 0; i < n; i++)
    {
        // 최초의 가중치 초기화
        dst[i] = weight[start][i];
        found[i] = 0;
    }
        found[start] = 1;

    int cnt = 0;
    printf("Start is 0\n");
    //모든 정점이 포함되지 않을 때 까지
    while (cnt != n-1) {
        int u = select(n);
        // 최단 경로가 발견되지 않고, 시작 정점과의 거리가 가장 짧은 정점을 반환
        found[u] = 1; // 해당 정점을 그래프에 포합.

        printf("%d add to array\n", u);
        route[cnt+1] = u;

        // v에 인접하고 s에 속하지 않는 정점에 대하여
        for (int j = 0; j < n; j++)
        {
            if (found[j] == 0)
            {
                if (dst[u] + weight[u][j] < dst[j])
                {
                    dst[j] = dst[u] + weight[u][j];
                }
            }
        }
        cnt++;
    }
}

int main(void) {
    Shortest_Path(0, MAX);

    for(int i = 0; i< MAX; i++){
      printf("%d ", route[i]);
    }
    //정점을 순서대로 출력
      printf("\n");

      return 0;
}
