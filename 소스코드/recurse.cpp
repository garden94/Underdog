#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "myDefine.h"

void calcuNumInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void calcuTotal(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void calcuFibo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void recursiveSearch(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void solveHanoiTower(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void solveQuickSort(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void writeQSortDataToWindows(HWND hDstEdit,int *data,int dataNum, TCHAR *kind);
//���� ���� ��� �Լ� 
void printEdit(HWND hEdit, TCHAR *msg);
void rHanoi(HWND hEdit, int num, char srcShaft, char dstShaft, char auxShaft);
void quickSort(int data[], int sPos, int ePos);
int readDataToArray(HWND hSrcEdit, int *data);
int rTot(int num);  //1���� ū �ڿ��������� ���� ��ȯ 
int rFibo(int num);
int rSearch(int data[], int sPos, int ePos, int sVal);
void swap(int *p, int *q); 
int partition(int data[], int sPos, int ePos);

 
void writeQSortDataToWindows(HWND hDstEdit,int *data,int dataNum, TCHAR *kind){
	TCHAR buff[BUFF_SIZE];
	TCHAR str[TEXT_LENGTH];
	
	memset(buff, 0, sizeof(buff));
	
	sprintf(str,"%s \r\n\r\n", kind);
	strcat(buff,str);
	for(int i=0; i<dataNum; i++){
		sprintf(str, "%d\r\n", data[i]);
		strcat(buff,str);
	}
	SetWindowText(hDstEdit, buff);
}
//������ ���� ��Ű�� 
void quickSort(int data[], int sPos, int ePos) {
	if(sPos >= ePos) return;
	int mPos = partition(data, sPos, ePos);
	quickSort(data, sPos, mPos-1); //�ǹ� ���� �ٽ� ����Ʈ 
	quickSort(data, mPos+1, ePos); //�ǹ� ������ �ٽ� ����Ʈ 
}
//�������� ������ ������ -> �������̶� ũ�� ���Ͽ� �ٲٴ� �� 
int partition(int data[], int sPos, int ePos) {
	int pivot; //������ 
	int low, high;
	
	low = sPos + 1;
	high = ePos;
	pivot = data[sPos];
	
	while(low <= high) { 
		while(low <= ePos) {
			if(data[low] > pivot) break;
			low++;
		}
		while(high >= sPos + 1) {
			if(data[high] < pivot) break;
			high--;
		}
		if(low < high) {
			swap(&data[low], &data[high]);
			low++; high--;
		}
	}
	
	swap(&data[sPos], &data[high]);
	return high;
}

//2�� ���� �� �ٲٱ� 
void swap(int *p, int *q) {
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

//����Ʈ ����ϱ� 
void solveQuickSort(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	int data[DATA_NUM], dataNum, num;
	
	TCHAR kind[10] = _T("�� ��Ʈ");
	
	dataNum = readDataToArray(hSrcEdit, data);
	
	quickSort(data, 0, dataNum-1);
	
	writeQSortDataToWindows(hDstEdit, data, dataNum, kind);
}

//�ϳ���ž ����Լ� 
void rHanoi(HWND hEdit, int num, char srcShaft, char dstShaft, char auxShaft) {
	TCHAR str[TEXT_LENGTH];
	if(num == 1) {
		sprintf(str, "%d�� ���� : %c�� --> %c������. \r\n", num, srcShaft, dstShaft);
		printEdit(hEdit, str);
		return;
	}else { 
	rHanoi(hEdit, num-1, srcShaft, auxShaft, dstShaft);
	sprintf(str, "%d�� ���� : %c�� --> %c������. \r\n", num, srcShaft, dstShaft);
	printEdit(hEdit, str);
	rHanoi(hEdit, num-1, auxShaft, dstShaft, srcShaft);
	}
}

//�ϳ���ž Ǯ�̸� ȭ�鿡 ����ϴ� �� 
void solveHanoiTower(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	int data[DATA_NUM], dataNum, num;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hDstEdit);
	fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	sscanf(buff,"����� ���� : %d", &num);
	
	TCHAR str[TEXT_LENGTH];
	char srcShaft = 'A', dstShaft = 'C', auxShaft = 'B';
	
	sprintf(str, "\r\n �ϳ��� ž ���(%c�� --> %c��). \r\n\r\n", srcShaft, dstShaft);
	printEdit(hDstEdit, str);
	
	rHanoi(hDstEdit, num, srcShaft, dstShaft, auxShaft); 
}

//������â�� ���ڿ� �߰� 
void printEdit(HWND hEdit, TCHAR *msg) {	
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	int data[DATA_NUM], dataNum, num;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hEdit);
	fileSize = GetWindowText(hEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	
	strcat(buff, msg);
	SetWindowText(hEdit, buff);
}

//���� �˻� ��͹��� 
int rSearch(int data[], int sPos, int ePos, int sVal){
	if(sPos > ePos) return -1;
	int mPos = (int)((sPos+ePos)/2);
	if(data[mPos]==sVal) return mPos;
	else{
		if(sVal < data[mPos]) {
			return rSearch(data, sPos, mPos-1, sVal);
		}else{
			return rSearch(data, mPos+1, ePos, sVal);
		}
	} 
}

//���� �˻� ��ͷ� �� �� ��� 
void recursiveSearch(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	
	 TCHAR buff[BUFF_SIZE];
	  DWORD fileSize;
	  int data[DATA_NUM], dataNum, num;
	 
	  memset(buff, 0,sizeof(buff));
	  fileSize = GetWindowTextLength(hDstEdit);
	  fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	  buff[fileSize] = NULL;
	  sscanf(buff,"�˻��� ���� : %d", &num); //������ ���ƾ��Ѵ�.// 
	  
	  dataNum = readDataToArray(hSrcEdit, data);
	  
	  int searchNumPos = rSearch(data, 0, dataNum-1, num);
	  
	  TCHAR str[TEXT_LENGTH];
	  
	  memset(buff, 0,sizeof(buff));
	  if(searchNumPos == -1){
	  	sprintf(str, "%d�� ���� �����Ϳ� �����ϴ�. \r\n", num);
	  }else{
	  	sprintf(str, "%d�� ���� �������� \r\n%d��°�� �ֽ��ϴ�. \r\n", num, searchNumPos+1);
	  }
	  strcat(buff, str);
	  SetWindowText(hDstEdit, buff);
}

//�Ǻ���ġ ������ �Է°� ����ϴ� �Լ� 
void calcuFibo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	  TCHAR buff[BUFF_SIZE];
	  DWORD fileSize;
	  int data[DATA_NUM], dataNum, num;
	 
	  memset(buff, 0,sizeof(buff));
	  fileSize = GetWindowTextLength(hDstEdit);
	  fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	  buff[fileSize] = NULL;
	  sscanf(buff,"����� ���� : %d", &num);
	  
	  memset(buff, 0, sizeof(buff));
	  TCHAR str[TEXT_LENGTH];
	  int tot;
	  if(num>0) {
	  	if(num ==1 || num == 2) tot = 1;
	  	else{
	  		tot = rFibo(num);
		  }
		  sprintf(str, "�Ǻ���ġ �� %d���� ���� %d�Դϴ�. \r\n",num,tot);
	  } else {
	  	sprintf(str, "%d�� �ڿ����� �ƴմϴ�. \r\n",num);
	  }
	  strcat(buff, str);
	  SetWindowText(hDstEdit, buff); 
}

//����� �� �Է� �޴� �޼��� 
 void calcuNumInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	 TCHAR buff[BUFF_SIZE];
	 TCHAR str[TEXT_LENGTH];
	 
	 memset(buff, 0, sizeof(buff));
	 SetWindowText(hDstEdit, buff); 
	
	 memset(buff, 0,sizeof(buff)); 
	 sprintf(str,"����� ���� :");
	 strcat(buff,str);
	 
	 SetWindowText(hDstEdit,buff);
}

 void calcuTotal(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	  TCHAR buff[BUFF_SIZE];
	  DWORD fileSize;
	  int data[DATA_NUM], dataNum, num;
	 
	  memset(buff, 0,sizeof(buff));
	  fileSize = GetWindowTextLength(hDstEdit);
	  fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	  buff[fileSize] = NULL;
	  sscanf(buff,"����� ���� : %d", &num);
	 
	  int tot = rTot(num);
	  
	  TCHAR str[TEXT_LENGTH];
	  memset(buff, 0, sizeof(buff));
	  
	  sprintf(str,"1���� %d������ ���� %d�Դϴ�. \r\n", num, tot);
	  strcat(buff,str);
	  SetWindowText(hDstEdit, buff);
 }
 
 //����Լ��� num���� �� ���ϱ� 
 int rTot(int num) {
	if(num==1) {
		return (1);
	}else{
		int res = num + rTot(num-1);
		return(res);
	}
}

//�Ǻ���ġ ���� ����Լ��� ǥ�� 
int rFibo(int num) {
	if(num == 1 || num == 2) {
		return 1;
	}else{
		return rFibo(num-1) + rFibo(num-2);
	}
}
