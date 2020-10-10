#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct TreeNode* TreeNodePtr;

//트리노드 생성 구조체
typedef struct TreeNode
{
	int weight;
	TreeNodePtr left_child;
	TreeNodePtr right_child;
}TreeNode;

//힙요소 구조체
typedef struct {
	TreeNodePtr ptree;
	int key;
}element;

//힘타입 구조체
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

typedef HeapType* HeapTypePtr;

//힙 생성 함수
HeapTypePtr create() {
	return (HeapTypePtr)malloc(sizeof(HeapType));
}
//힙 초기화 함수
void init(HeapTypePtr h)
{
	h->heap_size = 0;
}

//최소힙 삽입 함수
void insert_min_heap(HeapTypePtr h, element item)
{
	//힙 크기 할당
	int i;
	i = ++(h->heap_size);

	//반복문을 통해 힙의 높이 감소
	while ((i != 1) && (item.key < h ->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	//힙의 위치 변경
	h->heap[i] = item;
}

//최소힙 삭제 함수
element delete_min_heap(HeapTypePtr h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		//반복문을 통한 탐색
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key)
			break;
		//힙의 위치를 변경
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;

}

//트리 생성함수
TreeNodePtr make_tree(TreeNodePtr left, TreeNodePtr right)
{
	//트리포인터 노드를 동적 할당
	TreeNodePtr node = (TreeNodePtr)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "에러 발생\n");
		exit(1);
	}
	//각각의 오른, 왼 자식들을 할당
	node->left_child = left;
	node->right_child = right;

	//노드 반환
	return node;
}

//트리 파괴 함수
void destroy_tree(TreeNodePtr root)
{
	if (root == NULL)
		return;
	destroy_tree(root->left_child);
	destroy_tree(root->right_child);
	//할당 해제
	free(root);
}

//huff.txt 파일에서 freq.txt파일로 추출하는 함수
void rw_huff() {
	//문자열 저장을 위한 배열과 빈도수 저장을 위한 배열 선언
	char line[100];
	int freq[30] = {0 };

	//huff.txt 읽기모드로 열기
	FILE *fp = fopen("huff.txt", "r");

	//에러발생시에 대한 예외처리
	if (fp == EOF)
	{
		printf("file is not open");
		exit(1);
	}
	//문자열을 받아온다.
	fgets(line, sizeof(line), fp);
	//문자열을 출력한다.
	printf("%s\n", line);

	//반복문을 통해서 문자들을 걸러 빈도수배열을 채워나간다.
	for (int i = 0; i < strlen(line); i++)
	{
		//특수문자에 대한 예외는 별도로 처리
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
	//파일 닫기
	fclose(fp);

	//쓰기모드로 파일 open
	fp = fopen("freq.txt", "w");

	//반복문을 통해 각각의 빈도수를 적어내려간다.
	for (int j = 0; j < 30; j++) {
		//특수문자를 처리하기 위한 if 문
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
			//일반 문자에 대한 처리
			if (freq[j] == 0)
				continue;
			char cnt = (char)(97 + j);
			fprintf(fp, "%c %d\n", cnt, freq[j]);
		}
	}
	//쓰기모드 파일 close
	fclose(fp);
}

//freq.txt파일을 통해 huff-tree생성
void huff_tr() {
	char line[10];
	int i;
	int cnt1 = 0, cnt2 = 0;
	char alp[21];
	int* num;

	TreeNodePtr node, x;
	HeapTypePtr heap;

	element e, e1, e2;

	heap = create();
	init(heap);

	//freq.txt열기
	FILE* fp = fopen("freq.txt", "r");

	//에러발생시에 대한 예외처리
	if (fp == EOF)
	{
		printf("file is not open");
		exit(1);
	}

	while (fgets(line, sizeof(line), fp) != NULL)
		cnt1++;

	num = (int)malloc(sizeof(int) * cnt1);

	//텍스트파일의 커서 위치를 다시 처음으로
	fseek(fp, 0, SEEK_SET);

	//한줄씩 문장을 읽어들여 알파벳 배열및 빈도수 배열에 저장
	while (fgets(line, sizeof(line), fp) != NULL) {
		printf(line);
		alp[cnt2] = line[0];

		if (line[3] != NULL) {
			char a[2] = { line[2], line[3] };
			num[cnt2] = atoi(a);
		}
		else if (line[3] == NULL)
			num[cnt2] = line[2] - '0';

		cnt2++;
	}

	//트리 생성 후 히프 삽입
	for (i = 0; i < cnt2; i++) {
		node = make_tree(NULL, NULL);
		e.key = node->weight = num[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}

	for (i = 1; i < cnt2; i++) {
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);

		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		insert_min_heap(heap, e);
	}

	e = delete_min_heap(heap);
	destroy_tree(e.ptree);

	free(heap);
}

//허프만 코드 생성 함수
void huff_code() {

}

//문장 인코딩 함수
void encoding(){
}

//문장 디코딩 함수
void decoding(){
}

int main()
{
	rw_huff();
	huff_tr();
	return 0;
}
