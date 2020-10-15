#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fun()
{
	clock_t start, end;
	double elapsed;
	start = clock();
	// 측정하고자 하는 코드 블럭
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
}

void calcStatistics() 
{

}

int main() 
{
	caclStatistics(&stats); // 7가지 정렬방법에 대한 항목 개수별 실행시간, 비교회수, 이동회수 산출
	return 0;
}