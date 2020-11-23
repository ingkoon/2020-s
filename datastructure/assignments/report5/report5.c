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

int delete_heap_min(heaptr h)
{
	int value = h->h[1].val;
	//최소힙의 첫번째 노드를 가져온다
	int temp = h->h[h->hSize].val;
	int tempLoc = h->h[h->hSize].loc;
	//가장 마지막의 노드를 가져온다.
	int i = 1, j = 2;

	h->hSize--;
	//힙사이즈를 하나 감소시킨다.
	while (j <= h->hSize)
	{
		if (j < h->hSize && h->h[j].val > h->h[j + 1].val)
			j++;
		//힙사이즈가 2보다 작거나 다음

		if (temp < h->h[j].val)
			break;
		// 가장 마지막 값의 가중치가 2번째 간선의 가중치보다 작을 경우 중지
		h->h[i] = h->h[j];
		i = j;
		j *= 2;
	}
	h->h[i].val = temp;
	return value;
}



int get_min_vertex(int n) {
	int v;

	// 아직까지 방문하지 않은 node를 앞 순서부터 찾아낸다.
	for (int i = 0; i < n; i++) {
		if (visited[i] == 0) {
			v = i;
			break;
		}
	}

	// 앞에서 찾아낸 v 인덱스의 node보다 dist[]가 짧은 게 있다면?
	// 위 아래 for문을 합치면, 섬처럼 갇혀 있는 node에 대한 탐색이 불가능하다.
	// 1-2-3과 4로 이루어진 그래프는 4의 dist[]가 항상 INF이므로.

	for (int i = 0; i < n; i++) {
		if (visited[i] == false && (dist[i] < dist[v])) {
			v = i;
		}
	}
	return v;
}

int* prim(int g[MAX][MAX], int tree[MAX])
//배열을 반환하는 prim 알고리즘
{
	//최소힙 생성을 위한 힙 동적 선언
	heaptr h = (heaptr)malloc(sizeof(heap));

	int i, u, v;

	  for (u = 0; u < n; u++)  // dist배열과 selected배열의 정보를 초기화
	  {
	    dist[u] = INF;
	    selected[u] = FALSE;
	  }

	  dist[s] = 0;  // 시작정점과 시작정점간의 거리는 0이다. 자기자신을 순환하는 경로는 없다고 가정한다.

	  for (i = 0; i < n; i++)
	  {
	    // 리턴된 정점 번호를 u에 저장한다. u는 최소거리를 가지는 정점. 손으로 썻을 때 선택하는 효과를 가져온다.
	    u = get_min_vertex(n);
	    visited[u] = TRUE; // 최소거리를 갖는 정점의 정보(u)를 알아냈으니 해당 정점을 선택했다고 표시한다.

	    // 만약 경로가 없다면 함수를 종료한다. 정상적인 신장트리의 정보가 들어왔다면 실행될 일은 없을 것이다.
	    if (dist[u] == INF) return;


	    for (int v = 0; v < n; v++)  // 이 과정은 우리가 새롭게 발견한 정보를 저장하는 과정이다.
	    // 직접적인 경로가 발견되어 INF 에서 상수거리로 바뀌는 과정과
	    // 기존의 상수거리보다 더 짧은 거리가 발견되 그 정보를 갱신하는 과정이 포함되어 있다.
	    {
	      // 선택된 u 정점을 기준으로 정점(u)과 연결되어 있는 정점까지의 거리를 각각 비교한다.
	      if (g[u][v] != INF)  // 정점 u와 연결이 되어있고
	      {
	        // 아직 선택되지 않았으며 해당 변(g[u][v])의 길이가 기존의 dist[v] 값보다 작다면
	        if (selected[v] == 0 && g[u][v] < dist[v])
	          h[v]->val = g[u][v]; // dist[v]의 값을 갱신해준다.

	        // 새롭게 발견되는 정점들이 초반에 저장될 수 있는 건 INF를 1000으로 설정해줬기 때문이다.
	        // 우리가 만든 그래프의 경로값들은 전부 100이하의 값이기 때문에 새롭게 발견되는 정점이 있다면
	        // 우선 등록되고 그 후 더 짧은 거리가 등장하면 갱신되는 형태로 이 프로그램은 작동한다.
	      }
	    }
	  }
		free(h);
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
