#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 10001
//�ִ밪 ����

typedef struct {
	int a[max];
	int size;
	int cmp;
	int mv;
	double time;
	char sName[30];
}sort;
//�ϳ��� ���Ŀ� ���� ����ü ����

typedef sort* sortptr;
//����ü ������ ����

typedef struct {
	sort array[7];
}wh;
//������ ���Ŀ� ���� ��ü �迭 ����

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
//������ ���� �迭 �ʱ�ȭ

int fun()
{
	clock_t start, end;
	double elapsed;
	start = clock();
	// �����ϰ��� �ϴ� �ڵ� ��
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
//�������� �˰���

void calcStatistics() 
{
	for (int i = 0; i <7 ; i++)
}

int main() 
{
	//whptr w = (whptr)malloc(sizeof(wh));

	//caclStatistics(&stats); // 7���� ���Ĺ���� ���� �׸� ������ ����ð�, ��ȸ��, �̵�ȸ�� ����
	return 0;
}