#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fun()
{
	clock_t start, end;
	double elapsed;
	start = clock();
	// �����ϰ��� �ϴ� �ڵ� ��
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
}

void calcStatistics() 
{

}

int main() 
{
	caclStatistics(&stats); // 7���� ���Ĺ���� ���� �׸� ������ ����ð�, ��ȸ��, �̵�ȸ�� ����
	return 0;
}