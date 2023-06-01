/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


typedef struct node {//node를 구조체로 선언
	int key;//int형 변수 key선언
	struct node *left;//구조체 node형 포인터 left 선언
	struct node *right;//구조체 node형 포인터 right 선언
} Node;

/* for stack */
#define MAX_STACK_SIZE	20//MAX_STACK_SIZE를 20으로 설정
Node* stack[MAX_STACK_SIZE];//크기가 20인 Node형 포인터 stack 선언
int top = -1; //int형 변수 top을 -1로 하여 스택 초기화

Node* pop();//스택에서 pop
void push(Node* aNode);//Node형 포인터 aNode를 매개인자로 하는 void형 push 함수(스택에 삽입)

/* for queue */
#define MAX_QUEUE_SIZE	20//Max queue size를 20으로 설정
Node* queue[MAX_QUEUE_SIZE];//크기가 MAX_QUEUE_SIZE인 Node형 포인터 queue 선언
int front = -1;
int rear = -1;
//int형 변수 front, rear를 -1로 하여 큐 초기화


int initializeBST(Node** h);//Node형 이중포인터를 매개인자로 받는 int형 initializeBST 함수(트리 초기화)
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */

Node* deQueue();//큐에서 삭제
void enQueue(Node* aNode);//Node형 포인터를 매개인자로 받는 void형 enQueue함수 (큐에 삽입)

/* you may add your own defined functions if necessary */


void printStack();//스택 출력하는 void형 printStack 함수



int main()
{
	char command;//char형 변수 command 선언
	int key;//int형 변수 key 선언
	Node* head = NULL;//Node형 포인터 head를 NULL로 초기화

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
        printf("-----------[----- [Kimdongwoo] [2020039058] -----]--------------\n");
        printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//입력받은 값 command에 할당

		switch(command) {
		case 'z': case 'Z'://z 대소문자 입력받았을 때
			initializeBST(&head);//head의 주소를 매개인자로 받아 initializeBST함수 호출하여 트리 초기화
			break;
		case 'q': case 'Q'://q 대소문자 입력받았을 때
			freeBST(head);//head를 매개인자로 받아 freeBST 함수 호출하여 할당된 메모리 해제
			break;
		case 'i': case 'I'://i 대소문자 입력받았을 때
			printf("Your Key = ");
			scanf("%d", &key);//입력받은 값 key에 할당
			insert(head, key);//head와 key를 매개인자로 받는 insert함수 호출하여 노드 삽입
			break;
		case 'd': case 'D'://d 대소문자 입력받았을 때
			printf("Your Key = ");
			scanf("%d", &key);//입력받은 값 key에 할당
			deleteNode(head, key);//head와 key를 매개인자로 받은 deleteNode 호출하여 노드 삭제
			break;

		case 'r': case 'R'://r 대소문자 입력받았을 때
			recursiveInorder(head->left);//head의 left를 매개인자로 받아 recursiveInorder 함수 호출하여 재귀적 중위 순회
			break;
		case 't': case 'T'://t 대소문자 입력받았을 때
			iterativeInorder(head->left);//head의 left를 매개인자로 받아 iterativeInorder 함수 호출하여 반복적 중위 순회
			break;

		case 'l': case 'L'://l 대소문자 입력받았을 때
			levelOrder(head->left);//head의 left를 매개인자로 받아 levelOrder함수 호출하여 레벨순서 순회
			break;

		case 'p': case 'P'://p 대소문자 입력받았을 때
			printStack();//printStack 함수 호출하여 stack 출력
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q 대소문자 입력받기 전까지 반복

	return 1;
}

int initializeBST(Node** h) {//초기화 하는 initializeBST 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)//포인터 h가 NULL이 아니라면
		freeBST(*h);//포인터 h에 할당된 메모리 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));//포인터 h에 Node의 크기만큼 동적 메모리 할당
	(*h)->left = NULL;	/* root */ //포인터 h의 left NULL로 초기화
	(*h)->right = *h;//포인터 h의 right에 h 저장
	(*h)->key = -9999;//포인터 h의 key -9999로 초기화 

	top = -1;//top을 -1로 하여 스택 초기화

	front = rear = -1;//front와 rear를 -1로 하여 큐 초기화

	return 1;
}



void recursiveInorder(Node* ptr)//재귀적 중위 순회
{
	if(ptr) {//ptr이 있다면
		recursiveInorder(ptr->left);//ptr의 left를 매개인자로 받아 recursiveInorder 호출하여 재귀적 중위 순회
		printf(" [%d] ", ptr->key);//ptr의 key값 출력
		recursiveInorder(ptr->right);//ptr의 right를 매개인자로 받아 recursiveInorder 호출하여 재귀적 중위 순회
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)//반복적 중위 순회
{
	for(;;)
	{
		for(; node; node = node->left)//node의 left만큼 
			push(node);//node를 매기인자로 받아 push함수 호출하여 삽입
		node = pop();//삭제

		if(!node) break;//node가 비어있으면 break
		printf(" [%d] ", node->key);//node의 key 출력

		node = node->right;//node에 node의 right 저장
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr);//ptr을 매개인자로 받는 enQueue함수 호출하여 큐에 삽입

	for(;;)
	{
		ptr = deQueue();//큐에서 삭제
		if(ptr) {
			printf(" [%d] ", ptr->key);//ptr의 key 출력

			if(ptr->left)//ptr의 left이라면
				enQueue(ptr->left);//ptr의 right에 삽입
			if(ptr->right)//ptr의 right라면
				enQueue(ptr->right);//ptr의 left에 삽입
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//Node형 포인터 newNode에 Node 크기만큼 동적메모리 할당
	newNode->key = key;//newNode의 key에 key 값 할당
	newNode->left = NULL;//newNode의 left NULL로 초기화
	newNode->right = NULL;//newNode의 right NULL로 초기화

	if (head->left == NULL) {//head의 left가 NULL이라면
		head->left = newNode;//head의 left에 newNode 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//Node형 포인터 ptr에 head의 left 저장

	Node* parentNode = NULL;//Node형 parentNode NULL로 초기화
	while(ptr != NULL) {//ptr이 NULL이 아닐동안 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;//ptr의 key가 key값과 같다면 1 리턴

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)//ptr의 key 값이 key 보다 작다면
			ptr = ptr->right;//ptr에 ptr의 right 저장
		else
			ptr = ptr->left;//ptr에 ptr의 left 저장
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)//parentNode의 key가 key보다 크다면
		parentNode->left = newNode;//parentNode의 left에 newNode 저장
	else
		parentNode->right = newNode;//parentNode의 right에 newNode 저장
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {//head가 NULL이라면
		printf("\n Nothing to delete!!\n");//삭제할 것이 없다고 출력
		return -1;
	}

	if (head->left == NULL) {//head의 left가 NULL이라면
		printf("\n Nothing to delete!!\n");//삭제할 것이 없다고 출력
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;//Node형 포인터 root에 head의 left 저장



	Node* parent = NULL;//Node의 parent NULL로 초기화
	Node* ptr = root;//Node의 ptr에 root 저장

	while((ptr != NULL)&&(ptr->key != key)) {//ptr이 NULL이 아니다 and ptr의 key가 key 값이 아닐 동안
		if(ptr->key != key) {//ptr의 key가 key가 아니라면

			parent = ptr;	/* save the parent */

			if(ptr->key > key)//ptr의 key가 입력받은 key보다 크다면
				ptr = ptr->left;//ptr에 ptr의 left 저장
			else
				ptr = ptr->right;//ptr에 ptr의 right 저장
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)//ptr이 NULL이라면
	{
		printf("No node for key [%d]\n ", key);//입력받은 값에 해당하는 노드가 없다고 출력
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)//ptr의 left가 NULL and ptr의 right가 NULL이라면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)//parent의 left가 ptr과 같다면
				parent->left = NULL;//parent의 left NULL로 초기화
			else
				parent->right = NULL;//parent의 right NULL로 초기화
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;//head의 left NULL로 초기화

		}

		free(ptr);//ptr에 할당된 메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))//ptr의 left가 NULL or ptr의 right가 NULL
	{
		Node* child;//Node형 포인터 child 선언
		if (ptr->left != NULL)//ptr의 left가 NULL이 아니라면
			child = ptr->left;//child에 ptr의 left 저장
		else
			child = ptr->right;//child에 ptr의 right 저장

		if(parent != NULL)//parent가 NULL이 아니라면
		{
			if(parent->left == ptr)//parent의 left가 ptr과 같다면
				parent->left = child;//parent의 left에 child 저장 
			else
				parent->right = child;//parent의 right에 child 저장
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;//root에 child 저장
		}

		free(ptr);//ptr에 할당된 메모리 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;//Node형 포인터 candidate 선언
	parent = ptr;//parent에 ptr 저장


	candidate = ptr->right;//candidate에  ptr의 right 저장

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)//candidate의 left 가 NULL이 아닐 동안 반복
	{
		parent = candidate;//parent에 candidate 저장
		candidate = candidate->left;//candidate에 candidate의 left 저장
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)//parent의 right가 candidate와 같다면
		parent->right = candidate->right;//parent의 right에 candidate의 right 저장
	else
		parent->left = candidate->right;//parent의 left에 candidate의 right 저장

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;//ptr의 key에 candidate의 key 저장

	free(candidate);//candidate에 할당된 메모리 해제
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {//ptr이 존재한다면
		freeNode(ptr->left);//freeNode 함수를 호출하여 ptr의 left에 할당된 메모리 해제
		freeNode(ptr->right);//freeNode 함수를 호출하여 ptr의 right에 할당된 메모리 해제
		free(ptr);//ptr에 할당된 메모리 해제
	}
}

int freeBST(Node* head)//트리에 할당된 메모리 해제
{

	if(head->left == head)//head의 left와 head가 같다면
	{
		free(head);//head에 할당된 메모리 해제
		return 1;
	}

	Node* p = head->left;//Node형 포인터 p에 head의 left 저장

	freeNode(p);//freeNode 함수 호출하여 노드 p에 할당된 메모리 해제

	free(head);//head에 할당된 메모리 해제
	return 1;
}



Node* pop()//스택에서 삭제
{
	if (top < 0) return NULL;//top이 0보다 작다면 (초기화 되어있다면)
	return stack[top--];//stack[top--] 반환
}

void push(Node* aNode)//스택에 삽입
{
	stack[++top] = aNode;//stack[++top]에 aNode 저장
}


void printStack()//
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)//
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()//큐에서 삭제
{
	if (front == rear) {//front와 rear이 같다면
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;//MULL 리턴
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];//queue[front] 반환

}

void enQueue(Node* aNode)//큐에 삽입
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;//queue[rear]에 aNode 저장
}

