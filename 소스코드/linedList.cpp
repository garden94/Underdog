#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "myDefine.h"
#include <string.h>

typedef struct stud_node{
	int number;
	TCHAR name[10];
	int kor;
	int math;
	int eng;
	int tot;
	struct stud_node *ptr; //� ������ �޸� ������ ������ �ִ��� �˼��ִ�. 
}STUDENT_NODE;  //8����Ʈ �� �þ ���ڰ� �����. 

//�����Լ�
STUDENT_NODE *readStudent(HWND hEdit); //�ּҰ� ����ִ� 8����Ʈ head�� ��ȯ�Ѵ�. 
void writeStudent(HWND hEdit, STUDENT_NODE *head);
void deleteStudentNode(STUDENT_NODE *head);
STUDENT_NODE *readOneStudent(HWND hwnd);
void inputName(HWND hEdit, TCHAR *name);

//�ܺ��Լ�
void filePathReader(HWND hwnd, char *filePath, int flag);
void writeMsgToEdit(HWND hEdit, TCHAR *msg);

//�ܺ� ���� �Լ�
void readStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void directReadStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void insertStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
//������ �̸� ���ϱ� 
void inputName(HWND hEdit, TCHAR *name){  
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hEdit);
	fileSize = GetWindowText(hEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	sscanf(buff, "������ �л��� �̸���? %s", name); 
}

//�ܺ� �ؽ�Ʈ ���� ����ϱ� 
void directReadStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	STUDENT_NODE *head;
	TCHAR filePath[TEXT_LENGTH];
	STUDENT_NODE *oneStud, *cNode;
	
	filePathReader(hwnd, filePath, V_OPEN);
	
	FILE* fp = fopen(filePath, "r+");
	head = NULL;
	while(1){
		oneStud = new STUDENT_NODE;
		if(fscanf(fp,"%d %s %d %d %d %d\r\n", &oneStud->number, &oneStud->name, 
	  		&oneStud->kor, &oneStud->math, &oneStud->eng, &oneStud->tot) == EOF){
	  		break;
		};
		oneStud->ptr = NULL;
		if(head == NULL){
			head = oneStud;
			cNode = oneStud;
		}else{
			cNode->ptr = oneStud;
			cNode = oneStud;
		}
	}
	fclose(fp);
	
	writeStudent(hSrcEdit, head);
	deleteStudentNode(head);
}
//�ܺ� ���Ͽ��� ��� �� �� �߰��ϱ� 
void insertStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	STUDENT_NODE *head = NULL;
	STUDENT_NODE *cNode, *oneStud;
	
	head = readStudent(hSrcEdit);
	oneStud = readOneStudent(hwnd);
	
	if(strcmp(head->name, oneStud->name) > 0){
		oneStud->ptr = head;
		head = oneStud;
	}else{
		cNode = head;
		while(cNode->ptr != NULL){
			if(strcmp(cNode->ptr->name, oneStud->name) > 0) break;
			cNode = cNode->ptr;
		}
		if(cNode->ptr != NULL){
			oneStud->ptr = cNode->ptr;
			cNode->ptr = oneStud;
		}else{
			cNode->ptr = oneStud;
		}
	}
	
	writeStudent(hDstEdit, head);
	deleteStudentNode(head);
}
//��� �����ϱ� 
void deleteStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	STUDENT_NODE *head = NULL;
	STUDENT_NODE *cNode, *dNode = NULL; //dNode�� �����ߵǴ� ��带 ����Ŵ 
	//dNode�� NULL�Ҵ� ���ϸ� garbage���� ����. ���� ã�Ҵ��� ���� Ȯ�� ���� 
	TCHAR name[TEXT_LENGTH], msg[TEXT_LENGTH];
	
	inputName(hDstEdit, name);
	head = readStudent(hSrcEdit);
	
	if(strcmp(head->name, name) == 0){ //ù��° ���� �� 
		dNode = head;
		head = dNode->ptr;
		//if(head->ptr == NULL) head = NULL; //���� ptr�� NULL�� �Ǵϱ� �� ���� �������� 
	}else{
		cNode = head;
		while(cNode != NULL){
			if(strcmp(cNode->ptr->name, name) == 0) break;
			cNode = cNode->ptr;
		}
		if(cNode != NULL){ //cNode == NULL�̸� ������ �ٰ��µ� ��ã�Ҵ�. 
			dNode = cNode->ptr;
			cNode->ptr = dNode->ptr;
		}
	}
	if(dNode != NULL){
		writeStudent(hSrcEdit, head);
		delete(dNode);
		sprintf(msg, "%s�� �����Ͽ����ϴ�.", name);
		writeMsgToEdit(hDstEdit, msg);
	}else{
		sprintf(msg, "%s�� �����Ϳ� �����ϴ�.", name);
		writeMsgToEdit(hDstEdit, msg);
	}
	deleteStudentNode(head);
}

STUDENT_NODE *readOneStudent(HWND hwnd){
	TCHAR filePath[TEXT_LENGTH];
	
	filePathReader(hwnd, filePath, V_OPEN);
	
	FILE* fp = fopen(filePath, "r+");
	STUDENT_NODE *oneStud = new STUDENT_NODE;
	if(fscanf(fp,"%d\t%s\t%d\t%d\t%d\t%d\r\n", &oneStud->number, &oneStud->name, 
	  		&oneStud->kor, &oneStud->math, &oneStud->eng, &oneStud->tot) == EOF){
	  		return(NULL);
		};
	oneStud->tot = oneStud->kor + oneStud->math + oneStud->eng;
	oneStud->ptr = NULL;
	fclose(fp);
	return(oneStud);
}

//Source Data �ڷḦ �о� ���� �� 
void readStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	STUDENT_NODE *head = NULL;
	head = readStudent(hSrcEdit);
	writeStudent(hDstEdit, head);
	deleteStudentNode(head);
}

//����Ʈ ����ü�� ���� ��� 
STUDENT_NODE *readStudent(HWND hEdit){
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hEdit);
	fileSize = GetWindowText(hEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL; //Edit â���� ���ڿ��� �о ������ �ְڴ�. 
	
	STUDENT_NODE *head, *oneStud, *cNode;
	head = NULL; //NULL�� �ƴϸ� �̻��� ���� �� ���� ���ִ�. 
	char* tok2 = strtok(buff, "\r\n");
	while(tok2!=NULL){
		oneStud = new STUDENT_NODE; //���ο� ���� Ȯ�� --> �����޸��Ҵ� 
		sscanf(tok2, "%d %s %d %d %d %d\r\n", &oneStud->number, &oneStud->name, 
	  		&oneStud->kor, &oneStud->math, &oneStud->eng, &oneStud->tot);
	  	oneStud->ptr = NULL; //�ϳ� ���� ���� �����ͷ� �ϼ�(�������� �����ش�) 
	  	if(head ==NULL){ //���� ù��°���̳� 
	  		head = oneStud;
	  		cNode = oneStud; //tmp�� �ؿ��� cNode�� �ش� , �������� ����Ų��. 
		  }else{
		  	cNode->ptr = oneStud;
		  	cNode = oneStud;
		  }
		  tok2 = strtok(NULL,"\r\n"); //�������� �� ����־ ���پ� �߶���Ѵ�. 
		}
		return head; //�밡���� �Ѿ�� �ȴ�. 
}
//��� �� ���� ����Ʈ ĭ���� �̵� 
void writeStudent(HWND hEdit, STUDENT_NODE *head){
	TCHAR buff[BUFF_SIZE];
	TCHAR str[TEXT_LENGTH];
	STUDENT_NODE *tmp;
	 
	memset(buff, 0, sizeof(buff));
	tmp = head;
	while(tmp != NULL){
		sprintf(str,"%2d %5s %5d %5d %5d %5d\r\n", tmp->number, tmp->name, 
	  		tmp->kor, tmp->math, tmp->eng, tmp->tot);
		strcat(buff,str);
		tmp = tmp->ptr;//tmp�� ���� ����Ʈĭ���� ����.
	}
	 SetWindowText(hEdit, buff);	
} 
//������ ����Ʈ ��� ���� 
void deleteStudentNode(STUDENT_NODE *head){
	STUDENT_NODE *tmp, *dNode;
	tmp = head;
	while(tmp != NULL){
		dNode = tmp;
		tmp = tmp->ptr;
		delete(dNode);
	}
}
