#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct TreeNode* TreeNodePtr;

//Ʈ������ ����ü ����
typedef struct TreeNode
{
	int weight;
	TreeNodePtr left_child;
	TreeNodePtr right_child;
}TreeNode;

//����Ÿ���� �Ӽ� ����ü ����
typedef struct {
	TreeNodePtr ptree;
	int key;
}element;

//����Ÿ�� ����ü ����
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

typedef HeapType* HeapTypePtr;

//���� ���� �Լ�
HeapTypePtr create() {
	return (HeapTypePtr)malloc(sizeof(HeapType));
}
//���� �ʱ�ȭ �Լ�
void init(HeapTypePtr h)
{
	h->heap_size = 0;
}

//���� ���� �Լ�
void insert_min_heap(HeapTypePtr h, element item)
{
	//������ ũ�⸦ ���� ���� i
	int i;
	i = ++(h->heap_size);

	//�θ������� �񱳹ݺ���
	while ((i != 1) && (item.key < h ->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	//���ο� ���带 �ش� ��ġ�� ����
	h->heap[i] = item;
}

//�������� �Լ�
element delete_min_heap(HeapTypePtr h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		//���� ������ �ڽĳ��� �� �� ���� �ڽ� ���带 ã�´�
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key)
			break;
		//�Ѵܰ� �Ʒ��� �̵�����
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;

}

//����Ʈ�� ���� �Լ�
TreeNodePtr make_tree(TreeNodePtr left, TreeNodePtr right)
{
	//���� ���� ����
	TreeNodePtr node = (TreeNodePtr)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "�޸��� ����\n");
		exit(1);
	}
	//������ �� �ڽ� �߰�
	node->left_child = left;
	node->right_child = right;

	//���� ��ȯ
	return node;
}

//����Ʈ�� ���� �Լ�
void destroy_tree(TreeNodePtr root)
{
	if (root == NULL)
		return;
	destroy_tree(root->left_child);
	destroy_tree(root->right_child);
	//�Ҵ��� �����Ͽ� ����
	free(root);
}

//huff������ �о��鿩 freq���Ϸ� �����ϴ� �Լ�
void rw_huff() {
	//������ �о����� �迭�� �󵵸� �����ϱ� ���� �迭 ����
	char line[100];
	int freq[30] = {0 };
	char buf[10];
	char sentence[10];
	//huff.txt���� ����
	FILE *fp = fopen("huff.txt", "r");

	//���� �������� ���� �߻� �� ǥ��
	if (fp == EOF)
	{
		printf("file is not open");
		exit(1);
	}
	//���ڿ��� �迭�� �����Ѵ�
	fgets(line, sizeof(line), fp);
	//Ȯ���� ���� ����
	printf("%s\n", line);

	//���ڿ��� ���̸�ŭ �ݺ��� �����Ͽ� �󵵼��� ī��Ʈ�� ������Ų��.
	for (int i = 0; i < strlen(line); i++)
	{
		//Ư�������� ���� ������ ī��Ʈ�� ������Ų��.
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
	//�б� ������ ���¸� �����Ѵ�.
	fclose(fp);

	//���������� �ٽ� ������ ����
	fp = fopen("freq.txt", "w");

	//�ݺ����� �����Ͽ� freq.txt���Ͽ� �󵵼��� ���� ���� �ۼ�
	for (int j = 0; j < 30; j++) {
		//Ư�������� ���� ������ �ۼ�
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
			//�󵵼��� 0�� ���ڸ� ���� �� �̿��� ���ĺ��� �ؽ�Ʈ ���Ͽ� �߰�
			if (freq[j] == 0)
				continue;
			char cnt = (char)(97 + j);
			fprintf(fp, "%c %d\n", cnt, freq[j]);
		}
	}
	//���� ����
	fclose(fp);
}

//freq������ �о��鿩 huff-tree�� �����ϴ� �Լ�
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

	//freq.txt���� ����
	FILE* fp = fopen("freq.txt", "r");

	//���� �������� ���� �߻� �� ǥ��
	if (fp == EOF)
	{
		printf("file is not open");
		exit(1);
	}

	while (fgets(line, sizeof(line), fp) != NULL)
	{
		cnt1++;
	}
	num = (int)malloc(sizeof(int) * cnt1);

	//������ ó����ġ�� �̵�
	fseek(fp, 0, SEEK_SET);

	//���ڿ��� ���ڿ��� �迭�� �����Ѵ�
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

//Ʈ���� �̿��Ͽ� ������ �ڵ带 txt���Ͽ� �����ϴ� �Լ�
void huff_code() {

}

//������ �ڵ尡 ���� �ؽ�Ʈ���ϰ� ���� �޼����� ���ڵ��ϴ� �Լ�
void encoding(){
}

//���ڵ��� �޼����� ���ڵ��Ͽ� ���� ���·� �ٲٴ� �Լ�
void decoding(){
}

//�ش� ������ �����ϴ� �Լ�
void seq_print() {
}

int main()
{
	rw_huff();
	huff_tr();
	return 0;
}
