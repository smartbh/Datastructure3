#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

/*
번호			수학점수
134				65
125				95
145				55
128				50
129				60
124				55
135				70
147				85
115				90
144				80
*/


//데이터 타입
typedef struct element {
	int id;	//학생번호	이진탐색트리에서의 키
	int math;	//수학점수
}element;

//노드의 구조
typedef struct TreeNode {
	element student;
	struct TreeNode *left, *right;
}TreeNode;


//키값 비교 함수
//e1.key > e2.key = 1
//e1.key == e2.key = 0
//e1.key < e2.key = -1
int compareKey(element e1, element e2) {
	if (e1.id > e2.id)
		return 1;
	else if (e1.id == e2.id)
		return 0;
	else
		return -1;
}

//이진 탐색 트리 출력 함수
void display(TreeNode *p) {
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%d", p->student.id);
		display(p->right);
		printf(")");
	}
}


//이진탐색트리 탐색함수(반복)
TreeNode *search(TreeNode *root, element key)	//키값은 student의 id
{
	TreeNode *p = root;
	while (p != NULL) {
		switch (compareKey(key, p->student)) {
		case -1:	//key < p->student.id
			p = p->left;
			break;
		case 0:
			return p;
		case 1:
			p = p->right;
			break;
		}
	}

	return p; //탐색에 실패했을 경우
}

//이진 트리 삽입 함수
//key(id)를 이진 탑색 트리 root에 삽입한다.
//key가 이미 root안에 있으면 삽입되지 않는다.

int count_Tree = 0;//트리 개수

void insertNode(TreeNode **root, element key) {
	count_Tree++;//일단 트리개수 1개 증가
	TreeNode *p, *t; //p = 부모노드, t = 자식노드
	TreeNode *n; //n은 새로운 노드

	t = *root;
	p = NULL;

	//탐색을 먼저 실행
	while (t != NULL) {
		if (compareKey(key, t->student)==0) return;
		p = t;
		if (compareKey(key, t->student) < 0) t = t->left;
		else t = t->right;
	}

	//item이 트리안에 없으므로 삽입가능
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;

	//n에 데이터 복사
	n->student = key;
	n->left = n->right = NULL;

	//부모 노드와 링크 연결
	if (p != NULL) {
		if (compareKey(key, p->student) < 0)
			p->left = n;
		else if (compareKey(key, p->student) > 0)
			p->right = n;
	}
	else
		*root = n;
}

//삭제 함수
void deleteNode(TreeNode **root, element key) {
	TreeNode *p, *child, *succ, *succ_p, *t;
	//key를 갖는 노드 t를 탐색 p는 t의 부모노드

	p = NULL;
	t = *root;

	while (t != NULL && compareKey(t->student, key) != 0) {
		p = t;
		t = (compareKey(key, t->student) < 0) ? t->left : t->right;
	}

	if (t == NULL) {	//탐색 트리에 없는 키
		printf("key is not in the tree");
		return;
	}

	//단말노드인 경우
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else
				p->right = NULL;
		}

		else	//부모 노드가 없으면 루트
			*root = NULL;
	}

	//하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {

		child = (t->left != NULL) ? t->left : t->right;

		if (p != NULL) {
			if (p->left == t)//부모노드를 자식노드와 연결
				p->left = child;
			else p->right = child;
		}

		else
			*root = child;
	}

	else {		//두개의 자식을 가지는 경우
		//오른쪽 서브 트리에서 후속자를 찾는다.
		succ_p = t;
		succ = t->right;
		//후속자를 찾아서 계속 왼쪽으로 이동한다.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		//후속자의 부모와 자식을 연결
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		//후속자를 현재 노드로 이동한다.
		t->student = succ->student;
		t = succ;

	}
	free(t);
}

void UI() {
	printf("****************************************\n");
	printf("1.학생 정보입력(새로 온 학생이 있을 때\n");
	printf("2.학생 정보 삭제(학번을 입력받고)\n");
	printf("3.학생 정보 탐색(물론 학번으로)\n");
	printf("4.학생 정보 학번 오름차순으로 출력\n");
	printf("5.가장 높은 점수 학생 정보 출력\n");
	printf("6.평균 점수 출력\n");
	printf("7.전부 삭제\n");
	printf("8.종료\n");
	printf("****************************************\n");
}

void upPrint(TreeNode *root) {		//중위 순회 , 이진 탐색트리의 중위 순회는 오름차순이다.
	if (root) {
		upPrint(root->left);
		printf("(학번 : %d 수학점수 : %d)\n", root->student.id, root->student.math);
		upPrint(root->right);
	}

}

int maxMath = 0;	//최고점
int student_id = 0;	//최고점 일때 학생 아이디

void searchNode(TreeNode *root)	//키값은 student의 id
{	
	//가장 높은 점수 출력
	
	if (root) {
		searchNode(root->left);
		searchNode(root->right);
		if (root->student.math > maxMath) {
			maxMath = root->student.math;
			student_id = root->student.id;
		}
			
	}
}

int total_score = 0; //총점

void average_tree(TreeNode *root) {
	if (root) {
		average_tree(root->left);
		average_tree(root->right);
		total_score += (root->student.math);
	}
}

void deleteAll(TreeNode *root) {		//트리 전부 삭제하는 함수
	if (root) {
		deleteAll(root->left);
		deleteAll(root->right);
		free(root);
	}
}

int main() {
	int command;
	int i;
	
	element e;
	TreeNode *root = NULL;
	TreeNode *tmp;

	//8명은 미리 insertNode 함수를 써서 입력 -> 시간절약
	e.id = 134; e.math = 65;
	insertNode(&root, e);
	e.id = 125; e.math = 95;
	insertNode(&root, e);
	e.id = 145; e.math = 55;
	insertNode(&root, e);
	e.id = 128; e.math = 50;
	insertNode(&root, e);
	e.id = 129; e.math = 60;
	insertNode(&root, e);
	e.id = 124; e.math = 55;
	insertNode(&root, e);
	e.id = 135; e.math = 70;
	insertNode(&root, e);
	e.id = 147; e.math = 85;
	insertNode(&root, e);

	//두명만 시도해보기
	do {
		total_score = 0;	//총점 전역함수 초기화
		student_id = 0; maxMath = 0;	//최고점 학번, 점수 초기화
		UI();
		printf("\n");
		scanf("%d", &command);
		fflush(stdin);
		printf("\n");
		switch (command) {
		case 1:		//학생 정보입력
			printf("학번:");
			scanf("%d", &e.id);
			printf("수학점수:");
			scanf("%d", &e.math);
			insertNode(&root, e);
			break;
		case 2:		//학생 정보 삭제(학번)
			printf("학번:");
			scanf("%d", &e.id);
			deleteNode(&root, e);
			break;
		case 3:		//학생 정보 탐색(학번)
			printf("학번:");
			scanf("%d", &e.id);
			tmp = search(root, e);
			if (tmp != NULL)
				printf("수학 점수:%d\n", tmp->student.math);
			break;
		case 4:		//학생 정보 학번 오름차순 출력
			upPrint(root);
			break;
		case 5:		//가장 높은 점수 학생 정보 출력
			searchNode(root);
			printf("최고점을 가진 학생의 학번은\n");
			printf("학번 : %d 점수 : %d\n",student_id, maxMath);
			break;
		case 6:		//평균 점수 출력
			average_tree(root);
			printf("평균 : ");
			printf("%d\n", total_score / count_Tree);
			break;
		case 7:		//전부 삭제
			deleteAll(root);
			printf("전부 삭제되었습니다.\n");
			break;
		}

	} while (command != 8);

}