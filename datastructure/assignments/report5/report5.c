#include<stdio.h>
#include<stdlib.h>
#define MAX 50
#define INF 1000000

typedef struct {
	int u;
	int v;
	// 두개의 정점에 대한 정수형 변수
	int weight;
	// 간선에 갖고 있는 가중치의 값
}edge;
//간선에 대한 구조체

typedef struct {
	edge h[MAX];
	//간선의 집합을 갖고있는 힙구조
	int hSize;
	//힙의 크기
}heap;
// 최소힙에 대한 구조체

typedef heap* heaptr;
//구조체 포인터 선언

int parent[MAX];
int num[MAX];

void init_set(int size)
{
	for (int i = 0; i < size; i++)
	{
		parent[i] = -1;
		num[i] = 1;
	}
}


int find_set(int i)
{
	// 사이클 여부 확인
	int temp = i;
	//임시 변수 할당
	while (parent[temp] >= 0)
		temp = parent[temp];

	/*int temp2 = temp;
	int temp3;
	while (parent[temp2] >= 0)
	{
		temp3 = parent[temp2];
		parent[temp2] = temp;
		temp2 = temp3;
	}*/
	return temp;
}


void insert_min_heap(heaptr h, edge e)
// 최소 히프 삽입 알고리즘
{
	int i = ++h->hSize;
	//히프의 크기를 하나 증가시킨다.
	while (i > 0 && e.weight < h->h[i / 2].weight)
		//i가 0보다 크고, 가중치의 값이 상위 레벨의 노드보다 작을 경우 교체수행
	{
		h->h[i] = h->h[i / 2];
		i = i / 2;
	}
	h->h[i] = e;
}

void insert_heap(heaptr h, int u, int v, int weight)
{
	edge e;
	e.u = u;
	e.v = v;
	e.weight = weight;
	insert_min_heap(h, e);
}
edge delete_heap_min(heaptr h)
{
	edge value = h->h[1];
	//최소힙의 첫번째 노드를 가져온다
	edge temp = h->h[h->hSize];
	//가장 마지막의 노드를 가져온다.
	int i = 1, j = 2;

	h->hSize--;
	//힙사이즈를 하나 감소시킨다.
	while (j <= h->hSize)
	{
		if (j < h->hSize && h->h[j].weight > h->h[j + 1].weight)
			j++;
		//힙사이즈가 2보다 작거나 다음

		if (temp.weight < h->h[j].weight) break;
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
	/*
		insert_heap(h, 0, 1, 29);
		insert_heap(h, 1, 2, 16);
		insert_heap(h, 1, 6, 15);
		insert_heap(h, 2, 3, 12);
		insert_heap(h, 3, 4, 22);
		insert_heap(h, 3, 6, 18);
		insert_heap(h, 4, 5, 27);
		insert_heap(h, 4, 6, 25);
		insert_heap(h, 0, 5, 10);
		*/

	insert_heap(h, 0, 1, 10);
	insert_heap(h, 0, 3, 6);
	insert_heap(h, 0, 7, 1);
	insert_heap(h, 1, 2, 4);
	insert_heap(h, 1, 5, 2);
	insert_heap(h, 2, 3, 11);
	insert_heap(h, 2, 5, 7);
	insert_heap(h, 3, 7, 3);
	insert_heap(h, 4, 5, 5);
	insert_heap(h, 4, 7, 8);
	insert_heap(h, 5, 6, 9);
	insert_heap(h, 6, 7, 12);

}

void union_set(int s1, int s2) {
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

void kruskal(int n)
{
	int cnt = 0;
	//간선의 개수에 대한 변수 할당
	heaptr h = (heaptr)malloc(sizeof(heap));
	// 최소 힙 구조를 위한 힙 변수 할당
	h->hSize = 0;
	// 힙의 크기를 0으로 설정
	int uset, vset;
	// 정점에 대한 집합 변수 선언
	edge e;
	//간선 구조체 변수 선언
	insert_edge_vertex(h);
	//사용자의 요구에 맞게 간선 삽입
	init_set(n);

	while (cnt < (n - 1))
	{
		e = delete_heap_min(h);
		//최소힙의 첫번째 원소를 가져온다.
		uset = find_set(e.u);
		vset = find_set(e.v);
		// 각각의 정점을 가져온다
		if (uset != vset)
		{
			printf("%d to %d Edge Weight: %d was selected.\n", e.u, e.v, e.weight);
			cnt++;
			union_set(uset, vset);
		}
	}
	free(h);

}

int main()
{
	int graph[7][7] = {
		{0, 29, INF, INF, INF, 10, INF},
		{29, 0, 16, INF, INF, INF, 15},
		{INF, 16, 0, 12, INF, INF, INF},
		{INF, INF, 12, 0, 22, INF, 18},
		{INF, INF, INF, 22, 0, 27, 25},
		{10, INF, INF, INF, 27, 0, INF},
		{INF, 15, INF, 18, 25, INF, 0}
	};
	kruskal(7);
	prim();
	return 0;
}
