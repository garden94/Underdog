#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "myDefine.h"

int readDataToArray(HWND hSrcEdit, int *data);
void writeDataToWindows(HWND hDstEdit,int *data,int dataNum);
void writeSortDataToWindows(HWND hDstEdit,int *data,int dataNum, TCHAR *kind,
							int cmpNum, int cpNum);

void bubbleSorting(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){  //���� ���� 
	
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	int data[DATA_NUM], dataNum, num;
	TCHAR kind[10] = _T("����");
	
	dataNum = readDataToArray(hSrcEdit, data);
	
	int i, j, tmp;
	int cmpNum = 0, cpNum = 0;
	for(int i = 0; i<dataNum-1; i++){
		for(int j = 0; j<dataNum-i-1; j++){
			cmpNum++;
			if(data[j] > data[j+1]){
				tmp = data[j+1];
				data[j+1]=data[j];
				data[j]=tmp;
				cpNum+=3;
			}
		}
	}
	
	writeSortDataToWindows(hDstEdit, data, dataNum, kind, cmpNum, cpNum);
}

void selectSorting(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){ //���� ���� 
	
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	int data[DATA_NUM], dataNum, num;
	TCHAR kind[10] = _T("����");
	
	dataNum = readDataToArray(hSrcEdit, data);
	
	int i, j, tmp, tPos;
	int cmpNum = 0, cpNum = 0;
	for(int i = 0; i<dataNum; i++){
		tPos = i;
		for(int j = i; j<dataNum; j++){
			cmpNum++;
			if(data[j] < data[tPos]){
				tPos = j;
			}
		}
		tmp = data[i];
		data[i] = data[tPos];
		data[tPos] = tmp;
		cpNum+=3;
	}
	
	writeSortDataToWindows(hDstEdit, data, dataNum, kind, cmpNum, cpNum);
}

void insertSorting(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){	//���� ���� 
		
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	int data[DATA_NUM], dataNum, num;
	TCHAR kind[10] = _T("����");
	
	dataNum = readDataToArray(hSrcEdit, data);
	
	int i, j, tValue;
	int cmpNum = 0, cpNum = 0;
	for(i = 0; i<dataNum; i++){
		tValue = data[i];
		cpNum+=1;
		/*for(j = i; j>0 && data[j-1] > tValue ; j--) {
			cmpNum+=2;
			data[j] = data[j-1];
			cpNum+=1;
		}
		data[j] = tValue; 
		cpNum+=1;
	} */
	
		for(j = i; j>0; j--){
			cmpNum++;
			if(data[j-1] > tValue){
				data[j] = data[j-1];
				data[j-1] = tValue;
				cpNum+=2;
			}else{
				data[j] = tValue;
				cpNum+=1;
				break;
			}
		} 
		
}
	writeSortDataToWindows(hDstEdit, data, dataNum, kind, cmpNum, cpNum);
}

//�����Ѱ� �� �� ���ϰ� �� �� �����ϴ��� �����ִ�  
void writeSortDataToWindows(HWND hDstEdit,int *data,int dataNum, TCHAR *kind, int cmpNum, int cpNum){
	TCHAR buff[BUFF_SIZE];
	TCHAR str[TEXT_LENGTH];
	
	memset(buff, 0, sizeof(buff));
	

	sprintf(str,"%s ���� \r\n", kind);
	strcat(buff,str);
	sprintf(str,"��:%d, ����:%d \r\n\r\n", cmpNum, cpNum);
	strcat(buff,str);
	for(int i=0; i<dataNum; i++){
		sprintf(str, "%d\r\n", data[i]);
		strcat(buff,str);
	}
	SetWindowText(hDstEdit, buff);
}
