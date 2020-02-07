#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "myDefine.h"
#include <string.h>
//#include "quene.h" //����Ʈ�� �ٲ� .
#include "listQueue.h" //queue��� ����Ʈ�� Ȱ�� 
#include "arrayStack.h"
#include "listStack.h"

void readDataMakeBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void breadthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void depthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void valueSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void valueDeleteBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);

//�����Լ�
NUM_BTREE_NODE *insertNumBtreeNode(NUM_BTREE_NODE *head, NUM_BTREE_NODE *node);
NUM_BTREE_NODE *readDataMakeBtreeInFunc(HWND hSrcEdit);
NUM_BTREE_NODE *findNumInTree(NUM_BTREE_NODE *head, int num);
void writeBtreeNode(HWND hEdit, NUM_BTREE_NODE *head);
void writeBtreeToBuff(NUM_BTREE_NODE *node, TCHAR *buff);
void preorder(NUM_BTREE_NODE *node, TCHAR *buff);
void postorder(NUM_BTREE_NODE *node, TCHAR *buff);
void deleteBtreeNode(NUM_BTREE_NODE *cNode);
NUM_BTREE_NODE *deleteNumInTree(NUM_BTREE_NODE *head, int num);

//���� Ʈ���� ��� �����Ѵ�. 
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
//����Ʈ�� ���� ����Ѵ�. 
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
		writeBtreeToBuff(node->lptr, buff); //���� ��ȸ 
		sprintf(str,"%d \r\n", node->number);//�ڱ��ڽ���� 
		strcat(buff, str); 
		writeBtreeToBuff(node->rptr, buff); //������ ��ȸ 
	} //����� ����� ���ϴ�// 
}
//Source Dataâ���� ���ڸ� �а� ���� Ʈ���� �����. 
void readDataMakeBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hSrcEdit);
	fileSize = GetWindowText(hSrcEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;//�ҽ��� �ִ� �����͸� �о buff�� �ִ� �۾� 
	
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
	deleteBtreeNode(head);//head �������� ���� Ʈ�� ���� 
}
//���� ��ȸ 
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
//���� ��ȸ 
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
//�ʺ� Ž��, ť(queue)�� Ȱ���Ѵ�. 
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
//���� �켱 Ž�� 
void depthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE], str[TEXT_LENGTH];
	NUM_BTREE_NODE *head;
	head = readDataMakeBtreeInFunc(hSrcEdit); //head ���������ϱ� �پ��� ���� delete�����ֱ� 
	
	memset(buff, 0, sizeof(buff));
	sprintf(str,"���� ��ȸ. \r\n");
	strcat(buff, str);
	preorder(head, buff);
	sprintf(str,"\r\n");
	strcat(buff, str);
	
	memset(buff, 0, sizeof(buff));
	sprintf(str,"���� ��ȸ. \r\n");
	strcat(buff, str);
	preorder(head, buff);
	sprintf(str,"\r\n");
	strcat(buff, str);
	
	SetWindowText(hDstEdit, buff);
	
	deleteBtreeNode(head); //���� head�����ϱ�  
}
// ���� �а� Ʈ�� �����ϰ� head��ȯ �ϴ� �Լ�. 
NUM_BTREE_NODE *readDataMakeBtreeInFunc(HWND hSrcEdit){
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hSrcEdit);
	fileSize = GetWindowText(hSrcEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;//�ҽ��� �ִ� �����͸� �о ������ �ִ� �۾� 
	
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
} //���� Ʈ���� �޸𸮿� �����Ǵ� �Լ�. 

NUM_BTREE_NODE *findNumInTree(NUM_BTREE_NODE *cNode, int num) {
	if(cNode == NULL) return(NULL);
	if(cNode->number == num) return(cNode);//�ּҰ��� ��ȯ�Ͽ���. 
	if(num < cNode->number) return(findNumInTree(cNode->lptr, num)); 
	else return(findNumInTree(cNode->rptr, num));
} //cNode�� ��� ��� ���̸鼭 ����Ǳ� ������ �������� �ᵵ �ٸ� ���̵ȴ�. 
/* Ʈ������ �� �˻�
	���ڷ� �Ѱ� ���� �� NULL�̸� ������ �˻��Ѵ�. 
	���ڷ� �Ѱ� ���� Ʈ���� head�� ����Ű�� node�� ��� ���� ã�� ���̸� ����Ʈ ���� head ���� ��ȯ�Ѵ�.
	ã�� ���� head�� ����Ű�� node�� ��� ������ ������ head�� ����, ũ�� �������� node �˻� 
*/

void valueSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE];
	int fileSize, num;
	NUM_BTREE_NODE *head, *tmp;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hDstEdit);
	fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	sscanf(buff,"�˻��� ���� : %d", &num);
	
	head = readDataMakeBtreeInFunc(hSrcEdit);
	
	tmp = findNumInTree(head, num); //tmp���� head�� ���� �ּҰ� �ƴϸ� NULL�� ���´�. 
	memset(buff, 0, sizeof(buff));
	if(tmp != NULL){
		sprintf(buff, "%d�� BTree�� �ֽ��ϴ�. \r\n", num);
	}else{
		sprintf(buff, "%d�� BTree�� �����ϴ�. \r\n", num);
	}
	SetWindowText(hDstEdit, buff);
	deleteBtreeNode(head); //�ݳ����� ������ ������ ������. 
}

void deleteBtreeNode(NUM_BTREE_NODE *cNode){ //���� ����� ������ �������� 
	if(cNode == NULL) return;
	else{
		deleteBtreeNode(cNode->lptr);
		deleteBtreeNode(cNode->rptr);
		delete(cNode);
	} //������ ����Ű�� ���� ���� �ͺ��� ����� �ȴ�. ���� ��ȸ������� ���� 
}

void valueDeleteBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE];
	int fileSize, num;
	NUM_BTREE_NODE *head, *tmp;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hDstEdit);
	fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	sscanf(buff,"�˻��� ���� : %d", &num);
	
	head = readDataMakeBtreeInFunc(hSrcEdit);
	
	tmp = deleteNumInTree(head,num);
	memset(buff, 0, sizeof(buff));
	if(tmp != NULL){
		sprintf(buff, "%d�� BTree�� �����Ͽ����ϴ�.. \r\n", num);
		delete(tmp);
	}else{
		sprintf(buff, "%d�� BTree�� �����ϴ�. \r\n", num);
	}
	SetWindowText(hDstEdit, buff);
	writeBtreeNode(hSrcEdit,head); 
	deleteBtreeNode(head); //�ݳ����� ������ ������ ������. 
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
















