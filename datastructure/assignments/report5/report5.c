#include<stdio.h>
#include<stdlib.h>

#define MAX 7
#define INF 1000L

typedef struct
{
		int val;
		int loc;
}dis;
//거리비용에대한 구조체 (값과 위치)

typedef struct {
	dis h[MAX];
	//distance의 값을 갖고있는 힙구조
	int hSize;
	//힙의 크기
}heap;
// 최소힙에 대한 구조체

typedef heap* heaptr;
//구조체 포인터 선언

int visited = {0};
//방문여부에 대한 배열 변수 선언

void insert_heap(heaptr h, int val, int loc)
{
	int i = ++h->hSize;
	//히프의 크기를 하나 증가시킨다.

	if(val == 0) return;

	while (i > 0 && val < h->h[i/2].val)
	//i가 0보다 크고, 가중치의 값이 상위 레벨의 노드보다 작을 경우 교체수행
	{
		h->h[i].val = h->h[i/2].val;
		h->h[i].loc = h->h[i/2].val;
		i = i / 2;
	}
	h->h[i].val = val;
	h->h[i].loc = loc;
}

int* prim(int g[MAX][MAX], int tree[MAX])
//배열을 반환하는 prim 알고리즘
{
	//최소힙 생성을 위한 힙 동적 선언
	heaptr h = (heaptr)malloc(sizeof(heap));

	int i, u, v, result;

	for(int inLoc = 0; inLoc< MAX; inLoc++)
	{
			int inVal = g[0][inLoc];
			insert_heap(h,inVal,inLoc);
	}

	for (i = 0; i < MAX; i++)
	  {
	    // 리턴된 정점 번호를 u에 저장한다. u는 최소거리를 가지는 정점. 손으로 썻을 때 선택하는 효과를 가져온다.
	    result = h[i]->val;
			u = h[i]->loc;

			// 최소거리를 갖는 정점의 정보(u)를 알아냈으니 해당 정점을 선택됨을 표시한다.
	    visited[u] = TRUE;

			tree[u] = result;

	    // 만약 경로가 없다면 함수를 종료한다. 정상적인 신장트리의 정보가 들어왔다면 실행될 일은 없을 것이다.
	    if (h[u]->val == INF) return;

			//새롭게 발견한 정보를 저장.
	    for (int v = 0; v < n; v++)
	    {
	      // 선택된 u 정점을 기준으로 정점(u)과 연결되어 있는 정점까지의 거리를 각각 비교한다.
	      if (g[u][v] != INF)  // 정점 u와 연결이 되어있고
	      {

	        if (visited[v] == 0 && g[u][v] < h[v]->val)
						//값을 갱신
	          h[v]->val = g[u][v];
	        // 우리가 만든 그래프의 경로값들은 전부 100이하의 값이기 때문에 새롭게 발견되는 정점이 있다면
	        // 우선 등록되고 그 후 더 짧은 거리가 등장하면 갱신되는 형태로 이 프로그램은 작동한다.
	      }
	    }
	  }
		free(h);
}


void print(int tree[MAX])
{
	for(int i = 0; i< MAX-1; i++)
		printf("%d - ", &tree[i]);

	printf("%d", &tree[MAX-1]);
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
