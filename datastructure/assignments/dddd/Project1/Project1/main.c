#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100001
//최대값 설정

int temp[MAX];

typedef struct {
	int element[MAX];
	int size;
	int cmp;
	int mv;
	double time;
	char sName[30];
}sort;
//하나의 정렬에 대한 구조체 선언

typedef sort* sortptr;
//구조체 포인터 선언

typedef struct {
	sort array[7];
}wh;
//각각의 정렬에 대한 전체 배열 서언

typedef wh* whptr;
//정렬들의 구조체 포인터 선언

typedef struct {
	int hp[MAX];
	int hps;
}heap;
//히프 구조체 선언

typedef heap* heapptr;
//히프 포인터 선언

void init(sortptr s, int size)
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < size; i++)
		s->element[i] = rand() % 1000 + 1;

	s->cmp = 0;
	s->mv = 0;
	s->size = size;
	s->time = 0.0;
}
//정렬을 위한 배열 초기화

void swap(int* x, int* y) 
{
	int temp = 0;
	temp = *x;
	*x = *y;
	*y = temp;
}
//원소간 위치이동을 위한 swap함수

void selection(sortptr s)
{
	int least = 0;
	init(s, s->size);
	for (int i = 0; i < s->size; i++)
	{
		least = i;
		for (int j = i + 1; j < s->size; j++)
		{
			s->cmp++;
			if (s->element[i] > s->element[j])
				least = j;

			if (least != i)
			{
				swap(&s->element[i], &s->element[j]);
				s->mv += 3;
			}
		}
	}
}
//선택정렬 알고리즘

void insert(sortptr s)
{
	init(s, s->size);
	int j = 0, key = 0;
	for (int i = 1; i < s->size; i++)
	{
		key = s->element[i];
		for (j = i - 1; j >= 0; j--)
		{
			s->cmp++;
			s->element[j + 1] = s->element[j];
			s->mv++;
		}

		s->element[j + 1] = key;
	}
}
//삽입정렬 알고리즘


void bubble(sortptr s)
{
	init(s, s->size);
	for (int i = s->size; i >= 0; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			s->cmp++;
			if(s->element[j]>s->element[i+1])
			{
				swap(&s->element[i], &s->element[j]);
				s->mv += 3;
			}
		}
	}
}
//버블정렬 알고리즘

void shell_insert(int element[], int first, int last, int gap, sortptr s)
{
	int key = 0, j = 0;
	for (int i = first + gap; i < last; i = i + gap)
	{
		key = element[i];
		for (j = i - gap;j>first && element[j] > key; j = j - gap) {
			s->cmp++;
			element[j + gap] = element[j];
			s->mv++;
		}
		element[j + gap] = key;
	}
}
//쉘 삽입 알고리즘

void shell(sortptr s)
{
	init(s, s->size);
	for (int gap = s->size / 2; gap > 0; gap = gap / 2)
	{
		if (gap % 2 == 0)
			gap++;
		for (int i = 0; i < gap; i++)
		{
			shell_insert(s->element, 0, s->size, gap, s);
		}
	}
}
//쉘 정렬 알고리즘




void init_heap(heapptr h)
{
	h->hps = 0;
}
//힙 초기화 함수

void insert_heap(heapptr h, int item, sortptr s) 
{
	h->hps = h->hps + 1;
	int i = h->hps;
	while (i > 1 && h->hp[i / 2] > item)
	{
		s->cmp++;
		s->mv++;
		h->hp[i] = h->hp[i / 2];
		i /= 2;
	}
	h->hp[i] = item;
}
//힙 삽입 알고리즘
int delete_heap(heapptr h, sortptr s) 
{
	int item = h->hp[1];
	int val = h->hp[h->hps--];
	int i = 1, j = 2;
	while (j <= h->hps) 
	{
		s->cmp--;
		if (j < h->hps && h->hp[j] > h->hp[j + 1])
			j++;
		if (val > h->hp[j])
			break;

		s->mv++;
		h->hp[i] = h->hp[j];
		i = j;
		j *= 2;
	}
	s->mv++;
	h->hp[i] = val;
	return item;
}
//힙 삭제 알고리즘

void heap_sort(int list[], sortptr s)
{
	heapptr h = (heapptr)malloc(sizeof(heap));
	init_heap(h);
	int j = 0;
	for (int i = 0; i < s->size; i++)
	{
		insert_heap(h, list[i - 1], s);
	}

	int k = h->hps;

	while (k > 0)
	{
		list[j++] = delete_heap(h, s);
		k--;
	}

}
//힙정렬 알고리즘

void merge(int element[], int low, int mid, int high, sortptr s) 
{
	int b1 = low;
	int e1 = mid;
	
	int b2 = mid + 1;
	int e2 = high;

	int index = low;

	while (b1 <= e1 && b2 <= e2) 
	{
		s->cmp++;
		s->mv++;
		if (element[b1] <= element[b2])
			temp[index++] = element[b1++];
		else
			temp[index++] = element[b2++];

	}

	if (b2 > e2)
	{
		for (int i = b2; i < e2; i++)
			temp[index++] = element[i];
	}
	else 
	{
		for (int i = b1; i < e1; i++)
			temp[index++] = element[i];
	}
	for (int i = b1; i < e2; i++)
		element[i] = temp[i];
}
//합병 알고리즘

void merge_sort(int element[], int low, int high, sortptr s)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;

		merge_sort(element, low, mid, s);
		merge_sort(element, mid+1, high, s);
		merge(element, low, mid, high, s);
	}
}
//합병정렬 알고리즘

int partition(int element[], int left, int right, sortptr s)
{
	int pivot = element[left];
	int low = left;
	int high = right + 1;

	do {
		do { low++;  s->cmp += 1; } while (low <= right && element[low] < pivot);
		do { high--; s->cmp += 1; } while (high >= left && element[high] > pivot);

		if (low < high)
		{
			swap(&element[low], &element[high]);
			s->mv += 1;
		}
	} while (low < high);
	swap(&element[left], &element[high]);
	s->mv += 1;
	return high;
}

void quick(int element[], int left, int right, sortptr s)
{
	if (left < right)
	{
		int pivot = partition(element, left, right, s);
		quick(element, left, pivot - 1, s);
		quick(element, pivot + 1, right, s);
	}
}
//퀵정렬 알고리즘

void fun(whptr w, int n)
{
	clock_t start, end;
	double elapsed;
	start = clock();

	switch (n)
	{
	case 1:
	{
		selection(&w->array[0]);
		end = clock();
		strcpy(w->array[0].sName, "선택 정렬");	
		elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
		w->array[0].time = elapsed;
	}
	case 2:
	{
		insert(&w->array[1]);
		end = clock();
		strcpy(w->array[1].sName, "삽입 정렬");
		elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
		w->array[1].time = elapsed;
	}
	case 3:
	{
		bubble(&w->array[2]);
		end = clock();
		strcpy(w->array[2].sName, "버블 정렬");
		elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
		w->array[2].time = elapsed;
	}
	case 4:
	{
		shell(&w->array[3]);
		end = clock();
		strcpy(w->array[3].sName, "쉘  정렬");
		elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
		w->array[3].time = elapsed;
	}
	case 5:
	{
		heap_sort(w->array[4].element, &w->array[4]);
		end = clock();
		strcpy(w->array[4].sName, "히프 정렬");
		elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
		w->array[4].time = elapsed;
	}
	case 6:
	{
		merge_sort(w->array[5].element, 0, w->array[5].size-1, &w->array[5]);
		end = clock();
		strcpy(w->array[5].sName, "합병 정렬");
		elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
		w->array[5].time = elapsed;
	}
	case 7:
	{
		quick(w->array[6].element, 0, w->array[6].size-1, &w->array[6]);
		end = clock();
		strcpy(w->array[6].sName, "퀵  정렬");
		elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
		w->array[6].time = elapsed;
	}
	default:
		break;
	}
}
//각각의 경우에 대한 switch문 처리

void caclStatistics(whptr w, int n)
{
	for (int i = 0; i < 7; i++)
	{
		init(&w->array[i], 2000 * n);
		fun(w, i);
	}
}
//계산 함수

void cmSortsByTable(whptr w)
{
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("구분			소요 시간	비교 횟수	이동 횟수\n");
	for (int i = 0; i < 7; i++)
	{

		printf("%s		%0.2lf		%d		%d \n",
			w->array[i].sName, w->array[i].time, w->array[i].cmp, w->array[i].mv);

	}
	printf("-------------------------------------------------------------------------------------------------------\n");
}

int main()
{
	whptr w = (whptr)malloc(sizeof(wh));
	for (int i = 1; i < 6; i++)
	{
		caclStatistics(w,i);
		cmSortsByTable(w);
	}
	free(w);
	return 0;
}