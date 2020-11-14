#include<stdio.h>
#include<stdlib.h>
#define MAX 50
#define MAX_V 50
#define INF 1000

typedef struct {
	int u;
	int v;
	// 두개의 정점에 대한 정수형 변수
	int weight;
	// 간선에 갖고 있는 가중치의 값
}edge;
//간선에 대한 구조체

typedef struct {
	edge h[MAX_V];
	//간선의 집합을 갖고있는 힙구조
	int hs;
	//힙의 크기
}heap;
// 최소힙에 대한 구조체

typedef heap* heaptr;
//구조체 포인터 선언

int parent[MAX_V];
int num[MAX_V];


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
	int temp = i;
	//임시 변수 할당
	while (parent[temp] >= 0)
		temp = parent[temp];
	//

	int temp2 = temp;
	int temp3;
	while (parent[temp2] >= 0)
	{
		temp3 = parent[temp2];
		parent[temp2] = temp;
		temp2 = temp3;
	}
	return temp;
}


void insert_heap_min(heaptr h, edge e)
// 히프 삽입 알고리즘
{
	int i = ++h->hs;
	while (i > 0 && e.weight < h->h[i / 2].weight)
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
	insert_heap_min(h, e);
}
edge delete_heap_min(heaptr h)
{
	edge value = h->h[1];
	//최소힙의 첫번째 노드를 가져온다
	edge temp = h->h[h->hs];
	//가장 마지막의 노드를 가져온다.
	int i = 1, j = 2;

	h->hs = h->hs - 1;
	//힙사이즈를 하나 감소시킨다.
	while (j <= h->hs)
	{
		if (j < h->hs && h->h[j].weight > h->h[j + 1].weight)
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

void heap_print(heaptr h)
{
	int i = 1;
	while (i <= h->hs)
	{
		printf("(%d %d) weight:%d\n", h->h[i].u, h->h[i].v, h->h[i].weight);
		i++;
	}
}

void kruskal(int n)
{
	int cnt = 0;
	//간선의 개수에 대한 변수 할당
	heaptr h = (heaptr)malloc(sizeof(heap));
	// 최소 힙 구조를 위한 힙 변수 할당
	h->hs = 0;
	// 힙의 크기를 0으로 설정
	int uset, vset;
	// 정점에 대한 집합 변수 선언
	edge e;
	//간선 구조체 변수 선언
	insert_edge_vertex(h);
	//사용자의 요구에 맞게 간선 삽입
	init_set(n);
	// 집합 초기화

	while (cnt < (n - 1))
	{
		e = delete_heap_min(h);
		//최소힙의 첫번째 원소를 가져온다.
		uset = find_set(e.u);
		vset = find_set(e.v);
		// 각각의 정점으 가져온다
		if (uset != vset)
		//
		{
			printf("(%d.%d)Edge Weight: %d was connected\n", e.u, e.v, e.weight);
			cnt++;
			union_set(uset,vset);
		}
	}
	free(h);
}





int main()
{
	kruskal(7);
	return 0;
}
