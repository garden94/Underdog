#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "myDefine.h"
#include <string.h>
//#include "quene.h" //리스트로 바꿈 .
#include "listQueue.h" //queue대신 리스트로 활용 
#include "arrayStack.h"
#include "listStack.h"

void readDataMakeBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void breadthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void depthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void valueSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void valueDeleteBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);

//내부함수
NUM_BTREE_NODE *insertNumBtreeNode(NUM_BTREE_NODE *head, NUM_BTREE_NODE *node);
NUM_BTREE_NODE *readDataMakeBtreeInFunc(HWND hSrcEdit);
NUM_BTREE_NODE *findNumInTree(NUM_BTREE_NODE *head, int num);
void writeBtreeNode(HWND hEdit, NUM_BTREE_NODE *head);
void writeBtreeToBuff(NUM_BTREE_NODE *node, TCHAR *buff);
void preorder(NUM_BTREE_NODE *node, TCHAR *buff);
void postorder(NUM_BTREE_NODE *node, TCHAR *buff);
void deleteBtreeNode(NUM_BTREE_NODE *cNode);
NUM_BTREE_NODE *deleteNumInTree(NUM_BTREE_NODE *head, int num);

//이진 트리에 노드 삽입한다. 
NUM_BTREE_NODE *insertNumBtreeNode(NUM_BTREE_NODE *head, NUM_BTREE_NODE *node) {
	NUM_BTREE_NODE *cNode, *tNode;
	
	if(head == NULL){
		head = node;
	}else{
		cNode = head; tNode = head;
		while(cNode != NULL){
			if(node->number < cNode->number){
				tNode = cNode;
				cNode = cNode->lptr;
			}else{
				tNode = cNode;
				cNode = cNode->rptr;
			}
		}
	
	if(node->number < tNode->number){
		tNode->lptr = node;
	  }else{
		tNode->rptr = node;
		}
	return(head);
	}
}
//이진트리 내용 출력한다. 
void writeBtreeNode(HWND hEdit, NUM_BTREE_NODE *head){
	TCHAR buff[BUFF_SIZE];
	
	memset(buff, 0, sizeof(buff));
	writeBtreeToBuff(head, buff);
	SetWindowText(hEdit, buff);
}

void writeBtreeToBuff(NUM_BTREE_NODE *node, TCHAR *buff){
	TCHAR str[TEXT_LENGTH];
	
	if(node == NULL) return;
	else{
		writeBtreeToBuff(node->lptr, buff); //왼쪽 순회 
		sprintf(str,"%d \r\n", node->number);//자기자신찍고 
		strcat(buff, str); 
		writeBtreeToBuff(node->rptr, buff); //오른쪽 순회 
	} //재귀적 방법이 편하다// 
}
//Source Data창에서 숫자를 읽고 이진 트리를 만든다. 
void readDataMakeBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hSrcEdit);
	fileSize = GetWindowText(hSrcEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;//소스에 있는 데이터를 읽어서 buff에 넣는 작업 
	
	NUM_BTREE_NODE *head = NULL, *node;
	char* tok2 = strtok(buff,"\r\n");
	while(tok2!=NULL){
		node = new NUM_BTREE_NODE;
		node->number = atoi(tok2);
		node->lptr = NULL;
		node->rptr = NULL;
		head = insertNumBtreeNode(head, node);
		tok2 = strtok(NULL, "\r\n");
	}
	
	writeBtreeNode(hDstEdit, head);
	deleteBtreeNode(head);//head 없어지기 전에 트리 제거 
}
//전위 순회 
void preorder(NUM_BTREE_NODE *node, TCHAR *buff){
	TCHAR str[TEXT_LENGTH];
	
	if(node == NULL) return;
	else{
		sprintf(str,"%d -> ", node->number);
		strcat(buff,str);
		preorder(node->lptr, buff);
		preorder(node->rptr, buff);
	}
} 
//후위 순회 
void postorder(NUM_BTREE_NODE *node, TCHAR *buff){
	TCHAR str[TEXT_LENGTH];
	
	if(node == NULL) return;
	else{
		postorder(node->lptr, buff);
		postorder(node->rptr, buff);
		sprintf(str,"%d -> ", node->number);
		strcat(buff,str);
	}
} 
//너비 탐색, 큐(queue)를 활용한다. 
void breadthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE], str[TEXT_LENGTH];
	//queue q;
	//ListQueue q;
	arrayStack q;
	//listStack q;
	NUM_BTREE_NODE *head, *tmp;
	memset(buff, 0, sizeof(buff));
	
	head = readDataMakeBtreeInFunc(hSrcEdit);
	tmp = head;
	
	q.push(tmp);
	while(!q.empty()){
		tmp = q.pop();
		if(tmp->lptr != NULL)q.push(tmp->lptr);
		if(tmp->rptr != NULL)q.push(tmp->rptr);
		sprintf(str,"%d \r\n", tmp->number);
		strcat(buff, str);
	}
	SetWindowText(hDstEdit, buff);
	deleteBtreeNode(head);
}
//깊이 우선 탐색 
void depthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE], str[TEXT_LENGTH];
	NUM_BTREE_NODE *head;
	head = readDataMakeBtreeInFunc(hSrcEdit); //head 생성했으니까 다쓰고 나서 delete시켜주기 
	
	memset(buff, 0, sizeof(buff));
	sprintf(str,"전위 순회. \r\n");
	strcat(buff, str);
	preorder(head, buff);
	sprintf(str,"\r\n");
	strcat(buff, str);
	
	memset(buff, 0, sizeof(buff));
	sprintf(str,"후위 순회. \r\n");
	strcat(buff, str);
	preorder(head, buff);
	sprintf(str,"\r\n");
	strcat(buff, str);
	
	SetWindowText(hDstEdit, buff);
	
	deleteBtreeNode(head); //위에 head있으니까  
}
// 값을 읽고 트리 생성하고 head반환 하는 함수. 
NUM_BTREE_NODE *readDataMakeBtreeInFunc(HWND hSrcEdit){
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hSrcEdit);
	fileSize = GetWindowText(hSrcEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;//소스에 있는 데이터를 읽어서 버프에 넣는 작업 
	
	NUM_BTREE_NODE *head = NULL, *node;
	char* tok2 = strtok(buff,"\r\n");
	while(tok2!=NULL){
		node = new NUM_BTREE_NODE;
		node->number = atoi(tok2);
		node->lptr = NULL;
		node->rptr = NULL;
		head = insertNumBtreeNode(head, node);
		tok2 = strtok(NULL, "\r\n");
	}
	return(head);
} //이진 트리가 메모리에 구성되는 함수. 

NUM_BTREE_NODE *findNumInTree(NUM_BTREE_NODE *cNode, int num) {
	if(cNode == NULL) return(NULL);
	if(cNode->number == num) return(cNode);//주소값을 반환하였다. 
	if(num < cNode->number) return(findNumInTree(cNode->lptr, num)); 
	else return(findNumInTree(cNode->rptr, num));
} //cNode의 경우 계속 쌓이면서 저장되기 때문에 같은것을 써도 다른 값이된다. 
/* 트리에서 값 검색
	인자로 넘겨 받은 게 NULL이면 끝까지 검색한다. 
	인자로 넘겨 받은 트리의 head가 가리키는 node의 멤버 값이 찾는 값이면 포인트 변수 head 값에 반환한다.
	찾는 값이 head가 가리키는 node의 멤버 값보다 작으면 head의 왼쪽, 크면 오른쪽의 node 검색 
*/

void valueSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE];
	int fileSize, num;
	NUM_BTREE_NODE *head, *tmp;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hDstEdit);
	fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	sscanf(buff,"검색할 수는 : %d", &num);
	
	head = readDataMakeBtreeInFunc(hSrcEdit);
	
	tmp = findNumInTree(head, num); //tmp에는 head에 대한 주소값 아니면 NULL이 들어온다. 
	memset(buff, 0, sizeof(buff));
	if(tmp != NULL){
		sprintf(buff, "%d는 BTree에 있습니다. \r\n", num);
	}else{
		sprintf(buff, "%d는 BTree에 없습니다. \r\n", num);
	}
	SetWindowText(hDstEdit, buff);
	deleteBtreeNode(head); //반납하지 않으면 공간이 꽉찬다. 
}

void deleteBtreeNode(NUM_BTREE_NODE *cNode){ //새로 생기는 별개의 기억공간임 
	if(cNode == NULL) return;
	else{
		deleteBtreeNode(cNode->lptr);
		deleteBtreeNode(cNode->rptr);
		delete(cNode);
	} //양쪽이 가리키는 것이 없는 것부터 지우면 된다. 후위 순회방법으로 삭제 
}

void valueDeleteBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE];
	int fileSize, num;
	NUM_BTREE_NODE *head, *tmp;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hDstEdit);
	fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	sscanf(buff,"검색할 수는 : %d", &num);
	
	head = readDataMakeBtreeInFunc(hSrcEdit);
	
	tmp = deleteNumInTree(head,num);
	memset(buff, 0, sizeof(buff));
	if(tmp != NULL){
		sprintf(buff, "%d는 BTree에 삭제하였습니다.. \r\n", num);
		delete(tmp);
	}else{
		sprintf(buff, "%d는 BTree에 없습니다. \r\n", num);
	}
	SetWindowText(hDstEdit, buff);
	writeBtreeNode(hSrcEdit,head); 
	deleteBtreeNode(head); //반납하지 않으면 공간이 꽉찬다. 
}

NUM_BTREE_NODE *deleteNumInTree(NUM_BTREE_NODE *head, int num){
	NUM_BTREE_NODE *cNode, *tNode, *dNode;
	
	if(head==NULL){
		return(NULL);
	}else{
		cNode = head; tNode = head;
		while(cNode !=NULL){
			if(cNode->number==num){
				if(cNode->lptr ==NULL & cNode->rptr ==NULL){
					if(num <tNode -> number){
					}else{
						tNode->rptr = NULL;
					}
					dNode = cNode;
				}else{
					if(cNode->lptr!= NULL & cNode->rptr != NULL){
						NUM_BTREE_NODE *tmp;
						tmp =cNode;
						dNode = cNode->rptr;
						while(dNode->lptr !=NULL){
							tmp = dNode;
							dNode = dNode ->lptr;
						}
						cNode ->number = dNode ->number;
						if(tmp==cNode){
							cNode->rptr=dNode->rptr;
						}else{
							tmp->lptr=dNode->rptr;
						}
					}else{
						if(cNode->lptr != NULL&cNode->rptr==NULL){
							if(tNode->lptr==cNode){
								tNode->lptr=cNode->lptr;
							}else{
								tNode->rptr=cNode->lptr;
							}
						}else{
							if(tNode->lptr == cNode){
								tNode->lptr=cNode->rptr;
							}
						}
						dNode = cNode;
					}
				}
					return(dNode);	
				}
				if(num< cNode->number){
					tNode = cNode;
					cNode = cNode->lptr;
				}else{
					tNode = cNode;
					cNode = cNode->rptr;
				
			}
		}
	}
	return(NULL);
}
















