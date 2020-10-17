#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 10001
//최대값 설정

typedef struct {
	int a[max];
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

typedef wh* whptr

typedef struct {
	int hp[max];
	int hps;
}heap;


void init(sortptr s, int size)
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < size; i++) 
		s->a[i] = rand() % 1000 + 1;

	s->cmp = 0;
	s->mv = 0;
	s->size = size;
	s->time = 0.0;
}
//정렬을 위한 배열 초기화

int fun()
{
	clock_t start, end;
	double elapsed;
	start = clock();
	// 측정하고자 하는 코드 블럭
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
}


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
			if (s->a[i] > s->a[j];)
				least = j;	
		}
		if (least != i) 
		{
			swap(s->a[i], s->a[j]);
			s->mv += 3;
		}
	}
}
//선택정렬 알고리즘

void calcStatistics() 
{
	for (int i = 0; i <7 ; i++)
}

int main() 
{
	//whptr w = (whptr)malloc(sizeof(wh));

	//caclStatistics(&stats); // 7가지 정렬방법에 대한 항목 개수별 실행시간, 비교회수, 이동회수 산출
	return 0;
}