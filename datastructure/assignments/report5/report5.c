#include<stdio.h>
#include<stdlib.h>
#define MAX 7
#define INF 1000000

typedef struct {
	int h[MAX];
	//간선의 집합을 갖고있는 힙구조
	int hSize;
	//힙의 크기
}heap;
// 최소힙에 대한 구조체

typedef heap* heaptr;
//구조체 포인터 선언

void insert_heap(heaptr h, int n)
{
	int i = ++h->hSize;
	//히프의 크기를 하나 증가시킨다.
	while (i > 0 && n < h->h[i / 2])
	//i가 0보다 크고, 가중치의 값이 상위 레벨의 노드보다 작을 경우 교체수행
	{
		h->h[i] = h->h[i / 2];
		i = i / 2;
	}
	h->h[i] = n;
}

int delete_heap_min(heaptr h)
{
	int value = h->h[1];
	//최소힙의 첫번째 노드를 가져온다
	int temp = h->h[h->hSize];
	//가장 마지막의 노드를 가져온다.
	int i = 1, j = 2;

	h->hSize--;
	//힙사이즈를 하나 감소시킨다.
	while (j <= h->hSize)
	{
		if (j < h->hSize && h->h[j] > h->h[j + 1])
			j++;
		//힙사이즈가 2보다 작거나 다음

		if (temp < h->h[j])
			break;
		// 가장 마지막 값의 가중치가 2번째 간선의 가중치보다 작을 경우 중지
		h->h[i] = h->h[j];
		i = j;
		j *= 2;
	}
	h->h[i] = temp;
	return value;
}

void insert_edge_vertex(heaptr h)
{


}

void prim(int g[MAX][MAX], int n)
{

}


int main()
{
	int g[MAX][MAX] = {
		{0, 29, INF, INF, INF, 10, INF},
		{29, 0, 16, INF, INF, INF, 15},
		{INF, 16, 0, 12, INF, INF, INF},
		{INF, INF, 12, 0, 22, INF, 18},
		{INF, INF, INF, 22, 0, 27, 25},
		{10, INF, INF, INF, 27, 0, INF},
		{INF, 15, INF, 18, 25, INF, 0}
	};
	int tree[MAX];

	prim(g, tree);
	return 0;
}
