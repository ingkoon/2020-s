#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct TreeNode* TreeNodePtr;

//트리노드 구조체 생성
typedef struct TreeNode 
{
	int weight;
	TreeNodePtr left_child;
	TreeNodePtr right_child;
};

//히프타입의 속성 구조체 생성
typedef struct {
	TreeNodePtr ptree;
	int key;
}element;

//히프타입 구조체 생성
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

typedef HeapType* HeapTypePtr;

//히프 생성 함수
HeapTypePtr create() {
	return (HeapTypePtr)malloc(sizeof(HeapType));
}
//히프 초기화 함수
void init(HeapTypePtr h)
{
	h->heap_size = 0;
}

//히프 삽입 함수
void insert_min_heap(HeapTypePtr h, element item) 
{
	//히프의 크기를 담을 변수 i
	int i;
	i = ++(h->heap_size);

	//부모노드와 비교반복문
	while ((i != 1) && (item.key < h ->heap[i / 2].key)) 
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	//새로운 노드를 해당 위치에 삽입
	h->heap[i] = item;
}

//히프삭제 함수
element element_delete_min_heap(HeapTypePtr h) 
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		//현재 노드의 자식노드 중 더 작은 자식 노드를 찾는다
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key)
			break;
		//한단계 아래로 이동과정
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;

}

//이진트리 생성 함수
TreeNodePtr make_tree(TreeNodePtr left, TreeNodePtr right) 
{
	//동적 노드 생성
	TreeNodePtr node = (TreeNodePtr)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "메모리 에러\n");
		exit(1);
	}
	//노드의 두 자식 추가
	node->left_child = left;
	node->right_child = right;

	//노드 반환
	return node;
}

//huff파일을 읽어들여 freq파일로 출력하는 함수
void rw_huff() {
	//파일을 읽어들일 배열과 빈도를 저장하기 위한 배열 선언
	char line[100];
	int freq[30] = {0 };
	char buf[10];
	char sentence[10];
	//huff.txt파일 열기
	FILE *fp = fopen("huff.txt", "r");
	
	//여는 과정에서 에러 발생 시 표현
	if (fp == EOF) 
	{
		printf("file is not open");
		exit(1);
	}
	//문자열을 배열에 저장한다
	fgets(line, sizeof(line), fp);
	//확인을 위하 출력
	printf("%s\n", line);

	//문자열의 길이만큼 반복을 수행하여 빈도수의 카운트를 증가시킨다.
	for (int i = 0; i < strlen(line); i++)
	{
		//특수문자의 경우 별도로 카운트를 증가시킨다.
		if (line[i] == '-') {
			freq[26]++;
		}
		else if (line[i] == '.') {
			freq[27]++;
		}
		else if (line[i] == '!') {
			freq[28]++;
		}
		else if (line[i] == '+') {
			freq[29]++;
		}
		else if (line[i] >= 'a' && line[i] <= 'z') {
			int k = (int)line[i] - 97;
			freq[k]++;
		}
	}
	//읽기 모드의 상태를 종료한다.
	fclose(fp);

	//쓰기모드로 다시 파일을 연다
	fp = fopen("freq.txt", "w");

	//반복문을 수행하여 freq.txt파일에 빈도수에 대한 문장 작성
	for (int j = 0; j < 30; j++) {
		//특수문자의 경우 별도로 작성
		if (j == 26) {
			fprintf(fp, "- %d\n", freq[26]);
		}
		else if (j == 27) {
			fprintf(fp, ". %d\n", freq[27]);
		}
		else if (j == 28) {
			fprintf(fp, "! %d\n", freq[28]);
		}
		else if (j == 29) {
			fprintf(fp, "+ %d", freq[29]);
		}
		else {
			//빈도수가 0인 문자를 배제 후 이외의 알파벳을 텍스트 파일에 추가
			if (freq[j] == 0)
				continue;
			char cnt = (char)(97 + j);
			fprintf(fp, "%c %d\n", cnt, freq[j]);
		}	
	}
	//파일 종료
	fclose(fp);
}

//freq파일을 읽어들여 huff-tree를 구성하는 함수
void huff_tr() {
	char line[100];
	int freq[30] = { 0 };
	char buf[10];
	char sentence[10];
	//freq.txt파일 열기
	FILE* fp = fopen("freq.txt", "r");

	//여는 과정에서 에러 발생 시 표현
	if (fp == EOF)
	{
		printf("file is not open");
		exit(1);
	}
	//문자열을 배열에 저장한다
	fgets(line, sizeof(line), fp);
	//확인을 위한 출력
	printf(line);

}

//트리를 이용하여 허프만 코드를 txt파일에 출력하는 함수
void huff_code() {

}

//허프만 코드가 담긴 텍스트파일과 최초 메세지를 인코딩하는 함수
void encoding(){
}

//인코딩된 메세지를 디코딩하여 원래 형태로 바꾸는 함수
void decoding(){
}

//해당 과정을 출력하는 함수
void seq_print() {
}

int main()
{
	rw_huff();
	huff_tr();
	return 0;
}