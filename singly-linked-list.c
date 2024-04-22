/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;
    headnode = initialize(headnode);
    

	do{
        printf("[----- [hwajinLee]  [2020037103] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first; // h->first는 시작했을때 맨 첫번쨰 노드를 가르키는데, 아무것도 없다면 null일테고 
    //노드가 존재한다면 그 노드를 내가 생성한 node의 link로 이어주는 코드임

    //그리고 맨 첫번째 노드를 방금 생성했던 노드로 꼽아주는것
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    if (h->first == NULL) {
        //노드가 없는 상태라면 insertFirst와 같은 동작을 함으로 
        insertFirst(h, key);
    }else if (h->first->link == NULL) {
        //노드의 갯수가 하나밖에 없을땐 first랑만 배교해야함 (다음 else if문부터는 2개 이상이라 가정하고 노드링크의 노드를 확인할 예정)
        if (h->first->key > key) {
            //헤드 키가 key보다 크다면 맨 앞으로 insert되야하니까 >> 뒤에꺼를 확인하고 크다면 앞에거랑 이어야하기때문에 노드링크에 노드를 확인함
            insertFirst(h, key);
        }else {
            listNode* node = (listNode*)malloc(sizeof(listNode));
	        node->key = key;
            h->first->link = node;
        }
    } else if (h->first->key > key) {
        //첫번째 노드의 키보다 작다면 맨 앞으로 와야하니까 inserFirst를 호출
        insertFirst(h, key);
    }else {
        //순서를 돌아가면서 확인할것(while문)
        listNode* node = (listNode*)malloc(sizeof(listNode));
	    node->key = key;
        //첫번째 노드를 담아옴 (이제 이 compareNode의 링크를 돌면서 적절한 위치를 탐색할거임)
        listNode* compareNode = h->first;
         while (compareNode->link != NULL && compareNode->link->key < key) {
            compareNode = compareNode->link;
        }
        // 새로운 노드를 삽입
        node->link = compareNode->link;
        compareNode->link = node;
    }
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    if (h->first == NULL) {
        //노드가 없는 상태라면 insertFirst와 같은 동작을 함으로 
        insertFirst(h, key);
    }else {
         //순서를 돌아가면서 확인할것(while문)
        listNode* node = (listNode*)malloc(sizeof(listNode));
	    node->key = key;
        //첫번째 노드를 담아옴 (이제 이 compareNode의 링크를 돌면서 적절한 위치를 탐색할거임)
        listNode* compareNode = h->first;
        while (1) {
            if (compareNode->link == NULL) { //비교하는 노드의 링크가 없을 경우(마지막 노드라면) 마지막 노드의 링크에 생성한 노드 연결
                compareNode->link = node;
                break;
            }else {
                compareNode = compareNode->link;
            }
        }
    }
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
//노드가 없을 경우 print만 찍어주고 넘기기
    if (h->first == NULL) {
        printf("삭제할 노드가 없음");
    }else if (h->first->link == NULL) {
        //노드가 하나라면 삭제시키고 연결끊기
        free(h->first);
        h->first = NULL;
    }else {
        //노드가 여러개라면, 헤드를 두번쨰 노드와 연결시키고 첫번째 노드 삭제해야함
        listNode* twoNode = h->first->link;
        free(h->first);
        h->first = twoNode;
    }   
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    //삭제가 되었는지 확인하는 변수
    bool deleted = false;

    //노드key의 값이 들어온 key와 같을때 해당 노드를 삭제한다고 생각하고 풀었습니다.
    //키값이 같으 노드가 많다면 그 중 가장 앞에 있는 노드를 지우는 로직으로 진행하였습니다.
    if (h->first == NULL) {
        //노드가 없다면 프린트띄우고 넘어가기
        printf("삭제할 노드가 없어요");
    } else if (h->first->link == NULL) {
        //노드가 하나밖에 없다면 하나의 노드가 해당하는 key값을 가지고 있는지 체크 후 삭제 결정
        if (h->first->key == key) {
            free(h->first);
            h->first = NULL;
        } else {
            printf("해당하는 키값을 가진 노드가 없어요");
        }
    } else {
        //노드가 두개 이상일때
        //첫 노드는 우선 확인

         //첫번째 노드의 키값이 동일할 경우
        if (h->first->key == key) {
            listNode* temp = h->first;
            h->first = h->first->link;
            free(temp);
        } else {
            listNode* compareNode = h->first;
             //같은 키값을 가진 노드를 탐색
            while (compareNode->link != NULL) {
                if (compareNode->link->key == key) {
                    //찾았으면 삭제하고 free
                    listNode* temp = compareNode->link;
                    compareNode->link = temp->link;
                    free(temp);
                    break;
                } else {
                    compareNode = compareNode->link;
                }
            }
        }
    }
    return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    if (h->first == NULL) {
        //노드가 없으면 아무런 동작 안함
        return 0;
    }else if (h->first->link == NULL) {
        //노드 하나가 다일 경우 하나의 노드 삭제
        free(h->first);
        h->first = NULL;
    }else {
        //노드가 두개 이상일 경우
        listNode* compareNode = h->first;
        while(1) {
            if (compareNode->link->link == NULL) {
                listNode* temp = compareNode->link;
                compareNode->link = NULL;
                free(temp);
                break;
            }
            compareNode = compareNode->link;
        }
    }
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

