#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "myDefine.h"
#include <string.h>
//학생 구조체 
typedef struct stud{
	int number;	//학생 번호 
	TCHAR name[10];	//학생 이름 
	int kor;	//국어 점수 
	int math;	//수학 점수 
	int eng;	//영어 점수 
	int tot;	//총합 점수 
}STUDENT; 

//외부함수
void filePathReader(HWND hwnd, char *filePath, int flag);


void readStudentInfo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void sortStudentByName(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void sortStudentByTotal(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void directReadStudentInfo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void insertStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMemberInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);


//내부 함수// 
int readStudent(HWND hEdit, STUDENT *data);
void writeStudent(HWND hEdit, STUDENT *data, int dataNum);
void studentSwap(STUDENT *p, STUDENT *q);
void writeMsgToEdit(HWND hEdit, TCHAR *msg);
int readOneStudent(HWND hwnd, STUDENT *onestud);
int insertOneStudent(STUDENT*stud, int dataNum, STUDENT *onestud);
//삭제할 학생의 이름을 받는 곳 
void deleteStudentMemberInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE];
	
	memset(buff, 0, sizeof(buff)); 
	SetWindowText(hDstEdit, buff);  
	sprintf(buff, "삭제할 학생의 이름은?");
	SetWindowText(hDstEdit, buff);
}
//Result Data창에 삭제 결과를 보여준다. 
void writeMsgToEdit(HWND hEdit, TCHAR *msg){
	TCHAR buff[BUFF_SIZE];
	
	memset(buff, 0, sizeof(buff)); 
	SetWindowText(hEdit, buff);
	sprintf(buff, "%s", msg); 
	SetWindowText(hEdit, buff);
}

//삭제할 학생 이름이랑 비교해서 Source Data창에서 제거한다. 
void deleteStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){
	TCHAR buff[BUFF_SIZE], name[TEXT_LENGTH], msg[TEXT_LENGTH];
	DWORD fileSize;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hDstEdit);
	fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;  
	sscanf(buff, "삭제할 학생의 이름은? %s", &name);
	
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
		sprintf(msg, "%s를 삭제하였습니다.", name);
		writeMsgToEdit(hDstEdit, msg);	 
	}else{
		sprintf(msg, "%s는 데이터에 없습니다.", name);
		writeMsgToEdit(hDstEdit, msg);	 
	}
	
	
}
//학생 입력 
void insertStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	STUDENT stud[DATA_NUM], oneStud;
	int dataNum;
	
	dataNum = readStudent(hSrcEdit, stud);
	
	if(readOneStudent(hwnd, &oneStud) == -1){ 
		MessageBox(hwnd, "데이터를 읽을 수 없습니다.","메시지", MB_OK);
		return;
	};
	dataNum = insertOneStudent(stud, dataNum, &oneStud);
	writeStudent(hSrcEdit, stud, dataNum);
}

//파일에서 학생정보 불러오기 + 총점 계산 
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

//한명의 학생 정보 읽기 
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
//한 명 읽은 정보 순서에 맞게 삽입하기 
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

//학생 위치 바꾸기 
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
//이름순으로 정렬 
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
//총점으로 정렬 
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

//학생정보 읽기, 총점 구하기 
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
//학생 정보 출 려 
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
