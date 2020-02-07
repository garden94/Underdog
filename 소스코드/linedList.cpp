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
	struct stud_node *ptr; //어떤 형태의 메모리 구조를 가지고 있는지 알수있다. 
}STUDENT_NODE;  //8바이트 더 늘어난 상자가 생겼다. 

//내부함수
STUDENT_NODE *readStudent(HWND hEdit); //주소가 들어있는 8바이트 head만 반환한다. 
void writeStudent(HWND hEdit, STUDENT_NODE *head);
void deleteStudentNode(STUDENT_NODE *head);
STUDENT_NODE *readOneStudent(HWND hwnd);
void inputName(HWND hEdit, TCHAR *name);

//외부함수
void filePathReader(HWND hwnd, char *filePath, int flag);
void writeMsgToEdit(HWND hEdit, TCHAR *msg);

//외부 참고 함수
void readStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void directReadStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void insertStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
//삭제할 이름 구하기 
void inputName(HWND hEdit, TCHAR *name){  
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hEdit);
	fileSize = GetWindowText(hEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	sscanf(buff, "삭제할 학생의 이름은? %s", name); 
}

//외부 텍스트 파일 출력하기 
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
//외부 파일에서 사람 한 명 추가하기 
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
//사람 삭제하기 
void deleteStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	STUDENT_NODE *head = NULL;
	STUDENT_NODE *cNode, *dNode = NULL; //dNode는 지워야되는 노드를 가리킴 
	//dNode를 NULL할당 안하면 garbage값이 들어간다. 값을 찾았는지 여부 확인 위해 
	TCHAR name[TEXT_LENGTH], msg[TEXT_LENGTH];
	
	inputName(hDstEdit, name);
	head = readStudent(hSrcEdit);
	
	if(strcmp(head->name, name) == 0){ //첫번째 노드와 비교 
		dNode = head;
		head = dNode->ptr;
		//if(head->ptr == NULL) head = NULL; //원래 ptr이 NULL이 되니까 이 줄은 생략가능 
	}else{
		cNode = head;
		while(cNode != NULL){
			if(strcmp(cNode->ptr->name, name) == 0) break;
			cNode = cNode->ptr;
		}
		if(cNode != NULL){ //cNode == NULL이면 끝까지 다갔는데 못찾았다. 
			dNode = cNode->ptr;
			cNode->ptr = dNode->ptr;
		}
	}
	if(dNode != NULL){
		writeStudent(hSrcEdit, head);
		delete(dNode);
		sprintf(msg, "%s를 삭제하였습니다.", name);
		writeMsgToEdit(hDstEdit, msg);
	}else{
		sprintf(msg, "%s는 데이터에 없습니다.", name);
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

//Source Data 자료를 읽어 오는 거 
void readStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	STUDENT_NODE *head = NULL;
	head = readStudent(hSrcEdit);
	writeStudent(hDstEdit, head);
	deleteStudentNode(head);
}

//리스트 구조체로 정보 출력 
STUDENT_NODE *readStudent(HWND hEdit){
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hEdit);
	fileSize = GetWindowText(hEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL; //Edit 창에서 문자열로 읽어서 버프에 넣겠다. 
	
	STUDENT_NODE *head, *oneStud, *cNode;
	head = NULL; //NULL이 아니면 이상한 값이 들어가 있을 수있다. 
	char* tok2 = strtok(buff, "\r\n");
	while(tok2!=NULL){
		oneStud = new STUDENT_NODE; //새로운 공간 확보 --> 동적메모리할당 
		sscanf(tok2, "%d %s %d %d %d %d\r\n", &oneStud->number, &oneStud->name, 
	  		&oneStud->kor, &oneStud->math, &oneStud->eng, &oneStud->tot);
	  	oneStud->ptr = NULL; //하나 읽은 것을 데이터로 완성(끝맺음을 보여준다) 
	  	if(head ==NULL){ //제일 첫번째것이네 
	  		head = oneStud;
	  		cNode = oneStud; //tmp는 밑에서 cNode에 해당 , 마지막을 가리킨다. 
		  }else{
		  	cNode->ptr = oneStud;
		  	cNode = oneStud;
		  }
		  tok2 = strtok(NULL,"\r\n"); //버프값이 다 들어있어서 한줄씩 잘라야한다. 
		}
		return head; //대가리만 넘어가면 된다. 
}
//출력 후 다음 리스트 칸으로 이동 
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
		tmp = tmp->ptr;//tmp가 다음 리스트칸으로 간다.
	}
	 SetWindowText(hEdit, buff);	
} 
//마지막 리스트 노드 제거 
void deleteStudentNode(STUDENT_NODE *head){
	STUDENT_NODE *tmp, *dNode;
	tmp = head;
	while(tmp != NULL){
		dNode = tmp;
		tmp = tmp->ptr;
		delete(dNode);
	}
}
