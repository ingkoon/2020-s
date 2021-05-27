#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647
// �ִ� ����
#define MAX 13
// ������ ��
#define INF 1000
// ������ ���� ��쿡 ���� ���� ��

//����ġ �迭 �ʱ�ȭ
int weight[MAX][MAX] = {
  {0,7,INF,INF,3,10,INF},
  {7,0,4,10,2,6,INF},
  {INF,4,0,2,INF,INF,INF},
  {INF,10,2,0,11,9,4},
  {3,2,INF,11,0,INF,5},
  {10,6,INF,9,INF,0,INF},
  {INF,INF,INF,4,5,INF,0}
};

//�ּҰŸ� ������ ���� �迭 ����
int dst[MAX] = { 0 };
//�湮 ���θ� üũ�ϱ� ���� �迭 ����
int found[MAX] = { 0 };
//������ �迭 ����
int route[MAX] = { 0 };

// �ּҰ���ġ�� ���� �������� �Լ�
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
    // Dijkstra �˰������� �ִ� ��θ� ���Ѵ�.
    // �׷��� ���� �����ϴ� ��� ����� �ִ� ��θ� ���Ѵ�.

    //�׷����� ���� �� ������ ���Ͽ�
    for (int i = 0; i < n; i++)
    {
        // ������ ����ġ �ʱ�ȭ
        dst[i] = weight[start][i];
        found[i] = 0;
    }
    found[start] = 1;

    int cnt = 0;
    printf("Start is ");
    //��� ������ ���Ե��� ���� �� ����
    while (cnt != n - 1) {
        int u = select(n);
        // �ִ� ��ΰ� �߰ߵ��� �ʰ�, ���� �������� �Ÿ��� ���� ª�� ������ ��ȯ
        found[u] = 1; // �ش� ������ �׷����� ����.

        printf("%d add to array\n", u);
        route[cnt + 1] = u;

        // v�� �����ϰ� s�� ������ �ʴ� ������ ���Ͽ�
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

    for (int i = 0; i < MAX; i++) {
        printf("%d ", route[i]);
    }
    //������ ������� ���
    printf("\n");

    return 0;
}