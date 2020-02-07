#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "myDefine.h"
#include <string.h>
//�л� ����ü 
typedef struct stud{
	int number;	//�л� ��ȣ 
	TCHAR name[10];	//�л� �̸� 
	int kor;	//���� ���� 
	int math;	//���� ���� 
	int eng;	//���� ���� 
	int tot;	//���� ���� 
}STUDENT; 

//�ܺ��Լ�
void filePathReader(HWND hwnd, char *filePath, int flag);


void readStudentInfo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void sortStudentByName(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void sortStudentByTotal(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void directReadStudentInfo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void insertStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMemberInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);


//���� �Լ�// 
int readStudent(HWND hEdit, STUDENT *data);
void writeStudent(HWND hEdit, STUDENT *data, int dataNum);
void studentSwap(STUDENT *p, STUDENT *q);
void writeMsgToEdit(HWND hEdit, TCHAR *msg);
int readOneStudent(HWND hwnd, STUDENT *onestud);
int insertOneStudent(STUDENT*stud, int dataNum, STUDENT *onestud);
//������ �л��� �̸��� �޴� �� 
void deleteStudentMemberInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE];
	
	memset(buff, 0, sizeof(buff)); 
	SetWindowText(hDstEdit, buff);  
	sprintf(buff, "������ �л��� �̸���?");
	SetWindowText(hDstEdit, buff);
}
//Result Dataâ�� ���� ����� �����ش�. 
void writeMsgToEdit(HWND hEdit, TCHAR *msg){
	TCHAR buff[BUFF_SIZE];
	
	memset(buff, 0, sizeof(buff)); 
	SetWindowText(hEdit, buff);
	sprintf(buff, "%s", msg); 
	SetWindowText(hEdit, buff);
}

//������ �л� �̸��̶� ���ؼ� Source Dataâ���� �����Ѵ�. 
void deleteStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE], name[TEXT_LENGTH], msg[TEXT_LENGTH];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hDstEdit);
	fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;  
	sscanf(buff, "������ �л��� �̸���? %s", &name);
	
	STUDENT stud[DATA_NUM];
	int dataNum, pos;
	
	dataNum = readStudent(hSrcEdit, stud); 
	
	for(pos=0; pos < dataNum; pos++){
		if(strcmp(stud[pos].name, name) == 0) break;
	} 
	
	if(pos < dataNum){ 
		for(int i = pos; i < dataNum-1; i++){
			stud[i] = stud[i+1];
		}
		writeStudent(hSrcEdit, stud, dataNum-1);
		sprintf(msg, "%s�� �����Ͽ����ϴ�.", name);
		writeMsgToEdit(hDstEdit, msg);	 
	}else{
		sprintf(msg, "%s�� �����Ϳ� �����ϴ�.", name);
		writeMsgToEdit(hDstEdit, msg);	 
	}
	
	
}
//�л� �Է� 
void insertStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	STUDENT stud[DATA_NUM], oneStud;
	int dataNum;
	
	dataNum = readStudent(hSrcEdit, stud);
	
	if(readOneStudent(hwnd, &oneStud) == -1){ 
		MessageBox(hwnd, "�����͸� ���� �� �����ϴ�.","�޽���", MB_OK);
		return;
	};
	dataNum = insertOneStudent(stud, dataNum, &oneStud);
	writeStudent(hSrcEdit, stud, dataNum);
}

//���Ͽ��� �л����� �ҷ����� + ���� ��� 
void directReadStudentInfo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR filePath[TEXT_LENGTH];
	STUDENT stud[DATA_NUM];
	int dataNum;
	
	filePathReader(hwnd, filePath, V_OPEN);
	
	FILE* fp = fopen(filePath, "r+");  
	
	while(1) {
		if(fscanf(fp,"%d\t%s\t%d\t%d\t%d\r\n", &stud[dataNum].number, &stud[dataNum].name,
			&stud[dataNum].kor, &stud[dataNum].math, &stud[dataNum].eng) == EOF){
			break;
		}; 
		stud[dataNum].tot = stud[dataNum].kor + stud[dataNum].math + stud[dataNum].eng;
		dataNum++;
	}
	fclose(fp);
	
	writeStudent(hDstEdit, stud, dataNum);
}

//�Ѹ��� �л� ���� �б� 
int readOneStudent(HWND hwnd, STUDENT *onestud){
	TCHAR filePath[TEXT_LENGTH];
	
	filePathReader(hwnd, filePath, V_OPEN);
	
	FILE* fp = fopen(filePath, "r+");
	
	if(fscanf(fp,"%d\t%s\t%d\t%d\t%d\r\n", &onestud->number, &onestud->name,
		&onestud->kor, &onestud->math, &onestud->eng) == EOF){
		return(-1);
	};
	onestud->tot = onestud->kor + onestud->math + onestud->eng;
	fclose(fp);
	return(1);
} 
//�� �� ���� ���� ������ �°� �����ϱ� 
int insertOneStudent(STUDENT*stud, int dataNum, STUDENT *oneStud){
	int pos; 
	
	for(pos = dataNum; pos>0; pos--){ 
		if(strcmp(stud[pos-1].name, oneStud->name) > 0){ 
			stud[pos] = stud[pos-1];
		}else{
			break;
		}
	} 
	
	stud[pos] = *oneStud;
	return(dataNum+1); 

}

//�л� ��ġ �ٲٱ� 
void studentSwap(STUDENT *p, STUDENT *q){
	STUDENT temp;
	
	temp = *p;
	*p = *q; 
	*q = temp;
}

void readStudentInfo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	STUDENT stud[DATA_NUM]; 
	int dataNum;
	
	dataNum = readStudent(hSrcEdit, stud);
	writeStudent(hDstEdit, stud, dataNum);
}
//�̸������� ���� 
void sortStudentByName(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	STUDENT stud[DATA_NUM];
	int dataNum;
	
	dataNum = readStudent(hSrcEdit, stud);
	int i, j, tPos;
	for(int i = 0; i<dataNum; i++){
		tPos = i;
		for(int j = i; j<dataNum; j++){
			if(strcmp(stud[j].name, stud[tPos].name) < 0){
				tPos = j;
			}
		}
		studentSwap(&stud[i], &stud[tPos]);
	}
	
	writeStudent(hDstEdit, stud, dataNum);
}
//�������� ���� 
void sortStudentByTotal(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	STUDENT stud[DATA_NUM];
	int dataNum;
	
	dataNum = readStudent(hSrcEdit, stud);
	int i, j, tPos;
	for(int i = 0; i<dataNum; i++){
		tPos = i;
		for(int j = i; j<dataNum; j++){
			if(stud[j].tot > stud[tPos].tot){
				tPos = j;
			}
		}
		studentSwap(&stud[i], &stud[tPos]);
	}
	
	writeStudent(hDstEdit, stud, dataNum);
}

//�л����� �б�, ���� ���ϱ� 
int readStudent(HWND hEdit, STUDENT *data){
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	 
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hEdit);
	fileSize = GetWindowText(hEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	 
	int dataNum = 0;
	char *tok2 = strtok(buff,"\r\n");
	while(tok2!=NULL){
		sscanf(tok2, "%d\t%s\t%d\t%d\t%d\r\n", &data[dataNum].number, &data[dataNum].name, 
	  		&data[dataNum].kor, &data[dataNum].math, &data[dataNum].eng);
	  	data[dataNum].tot = data[dataNum].kor + data[dataNum].math + data[dataNum].eng;
	  	tok2 = strtok(NULL,"\r\n");
	  	dataNum++;
	} 
	return dataNum;
	
}
//�л� ���� �� �� 
void writeStudent(HWND hEdit, STUDENT *data, int dataNum){
	TCHAR buff[BUFF_SIZE];
	TCHAR str[TEXT_LENGTH];
	 
	memset(buff, 0, sizeof(buff));
	for(int i=0; i<dataNum; i++){
		sprintf(str,"%5d %10s %4d %4d %4d %4d\r\n", data[i].number, data[i].name, 
	  		data[i].kor, data[i].math, data[i].eng, data[i].tot);
		strcat(buff,str);
	}
	 SetWindowText(hEdit, buff);
	
}
