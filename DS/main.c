#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

/*
��ȣ			��������
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


//������ Ÿ��
typedef struct element {
	int id;	//�л���ȣ	����Ž��Ʈ�������� Ű
	int math;	//��������
}element;

//����� ����
typedef struct TreeNode {
	element student;
	struct TreeNode *left, *right;
}TreeNode;


//Ű�� �� �Լ�
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

//���� Ž�� Ʈ�� ��� �Լ�
void display(TreeNode *p) {
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%d", p->student.id);
		display(p->right);
		printf(")");
	}
}


//����Ž��Ʈ�� Ž���Լ�(�ݺ�)
TreeNode *search(TreeNode *root, element key)	//Ű���� student�� id
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

	return p; //Ž���� �������� ���
}

//���� Ʈ�� ���� �Լ�
//key(id)�� ���� ž�� Ʈ�� root�� �����Ѵ�.
//key�� �̹� root�ȿ� ������ ���Ե��� �ʴ´�.

int count_Tree = 0;//Ʈ�� ����

void insertNode(TreeNode **root, element key) {
	count_Tree++;//�ϴ� Ʈ������ 1�� ����
	TreeNode *p, *t; //p = �θ���, t = �ڽĳ��
	TreeNode *n; //n�� ���ο� ���

	t = *root;
	p = NULL;

	//Ž���� ���� ����
	while (t != NULL) {
		if (compareKey(key, t->student)==0) return;
		p = t;
		if (compareKey(key, t->student) < 0) t = t->left;
		else t = t->right;
	}

	//item�� Ʈ���ȿ� �����Ƿ� ���԰���
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;

	//n�� ������ ����
	n->student = key;
	n->left = n->right = NULL;

	//�θ� ���� ��ũ ����
	if (p != NULL) {
		if (compareKey(key, p->student) < 0)
			p->left = n;
		else if (compareKey(key, p->student) > 0)
			p->right = n;
	}
	else
		*root = n;
}

//���� �Լ�
void deleteNode(TreeNode **root, element key) {
	TreeNode *p, *child, *succ, *succ_p, *t;
	//key�� ���� ��� t�� Ž�� p�� t�� �θ���

	p = NULL;
	t = *root;

	while (t != NULL && compareKey(t->student, key) != 0) {
		p = t;
		t = (compareKey(key, t->student) < 0) ? t->left : t->right;
	}

	if (t == NULL) {	//Ž�� Ʈ���� ���� Ű
		printf("key is not in the tree");
		return;
	}

	//�ܸ������ ���
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else
				p->right = NULL;
		}

		else	//�θ� ��尡 ������ ��Ʈ
			*root = NULL;
	}

	//�ϳ��� �ڽĸ� ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) {

		child = (t->left != NULL) ? t->left : t->right;

		if (p != NULL) {
			if (p->left == t)//�θ��带 �ڽĳ��� ����
				p->left = child;
			else p->right = child;
		}

		else
			*root = child;
	}

	else {		//�ΰ��� �ڽ��� ������ ���
		//������ ���� Ʈ������ �ļ��ڸ� ã�´�.
		succ_p = t;
		succ = t->right;
		//�ļ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		//�ļ����� �θ�� �ڽ��� ����
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		//�ļ��ڸ� ���� ���� �̵��Ѵ�.
		t->student = succ->student;
		t = succ;

	}
	free(t);
}

void UI() {
	printf("****************************************\n");
	printf("1.�л� �����Է�(���� �� �л��� ���� ��\n");
	printf("2.�л� ���� ����(�й��� �Է¹ް�)\n");
	printf("3.�л� ���� Ž��(���� �й�����)\n");
	printf("4.�л� ���� �й� ������������ ���\n");
	printf("5.���� ���� ���� �л� ���� ���\n");
	printf("6.��� ���� ���\n");
	printf("7.���� ����\n");
	printf("8.����\n");
	printf("****************************************\n");
}

void upPrint(TreeNode *root) {		//���� ��ȸ , ���� Ž��Ʈ���� ���� ��ȸ�� ���������̴�.
	if (root) {
		upPrint(root->left);
		printf("(�й� : %d �������� : %d)\n", root->student.id, root->student.math);
		upPrint(root->right);
	}

}

int maxMath = 0;	//�ְ���
int student_id = 0;	//�ְ��� �϶� �л� ���̵�

void searchNode(TreeNode *root)	//Ű���� student�� id
{	
	//���� ���� ���� ���
	
	if (root) {
		searchNode(root->left);
		searchNode(root->right);
		if (root->student.math > maxMath) {
			maxMath = root->student.math;
			student_id = root->student.id;
		}
			
	}
}

int total_score = 0; //����

void average_tree(TreeNode *root) {
	if (root) {
		average_tree(root->left);
		average_tree(root->right);
		total_score += (root->student.math);
	}
}

void deleteAll(TreeNode *root) {		//Ʈ�� ���� �����ϴ� �Լ�
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

	//8���� �̸� insertNode �Լ��� �Ἥ �Է� -> �ð�����
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

	//�θ� �õ��غ���
	do {
		total_score = 0;	//���� �����Լ� �ʱ�ȭ
		student_id = 0; maxMath = 0;	//�ְ��� �й�, ���� �ʱ�ȭ
		UI();
		printf("\n");
		scanf("%d", &command);
		fflush(stdin);
		printf("\n");
		switch (command) {
		case 1:		//�л� �����Է�
			printf("�й�:");
			scanf("%d", &e.id);
			printf("��������:");
			scanf("%d", &e.math);
			insertNode(&root, e);
			break;
		case 2:		//�л� ���� ����(�й�)
			printf("�й�:");
			scanf("%d", &e.id);
			deleteNode(&root, e);
			break;
		case 3:		//�л� ���� Ž��(�й�)
			printf("�й�:");
			scanf("%d", &e.id);
			tmp = search(root, e);
			if (tmp != NULL)
				printf("���� ����:%d\n", tmp->student.math);
			break;
		case 4:		//�л� ���� �й� �������� ���
			upPrint(root);
			break;
		case 5:		//���� ���� ���� �л� ���� ���
			searchNode(root);
			printf("�ְ����� ���� �л��� �й���\n");
			printf("�й� : %d ���� : %d\n",student_id, maxMath);
			break;
		case 6:		//��� ���� ���
			average_tree(root);
			printf("��� : ");
			printf("%d\n", total_score / count_Tree);
			break;
		case 7:		//���� ����
			deleteAll(root);
			printf("���� �����Ǿ����ϴ�.\n");
			break;
		}

	} while (command != 8);

}