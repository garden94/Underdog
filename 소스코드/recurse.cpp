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
//파일 내부 사용 함수 
void printEdit(HWND hEdit, TCHAR *msg);
void rHanoi(HWND hEdit, int num, char srcShaft, char dstShaft, char auxShaft);
void quickSort(int data[], int sPos, int ePos);
int readDataToArray(HWND hSrcEdit, int *data);
int rTot(int num);  //1보다 큰 자연수까지의 합을 반환 
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
//기준점 증가 시키기 
void quickSort(int data[], int sPos, int ePos) {
	if(sPos >= ePos) return;
	int mPos = partition(data, sPos, ePos);
	quickSort(data, sPos, mPos-1); //피벗 왼쪽 다시 퀵소트 
	quickSort(data, mPos+1, ePos); //피벗 오른쪽 다시 퀵소트 
}
//기준점을 가져서 나누기 -> 기준점이랑 크기 비교하여 바꾸는 거 
int partition(int data[], int sPos, int ePos) {
	int pivot; //기준점 
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

//2개 변수 값 바꾸기 
void swap(int *p, int *q) {
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

//퀵소트 출력하기 
void solveQuickSort(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	int data[DATA_NUM], dataNum, num;
	
	TCHAR kind[10] = _T("퀵 소트");
	
	dataNum = readDataToArray(hSrcEdit, data);
	
	quickSort(data, 0, dataNum-1);
	
	writeQSortDataToWindows(hDstEdit, data, dataNum, kind);
}

//하노이탑 재귀함수 
void rHanoi(HWND hEdit, int num, char srcShaft, char dstShaft, char auxShaft) {
	TCHAR str[TEXT_LENGTH];
	if(num == 1) {
		sprintf(str, "%d번 원반 : %c축 --> %c축으로. \r\n", num, srcShaft, dstShaft);
		printEdit(hEdit, str);
		return;
	}else { 
	rHanoi(hEdit, num-1, srcShaft, auxShaft, dstShaft);
	sprintf(str, "%d번 원반 : %c축 --> %c축으로. \r\n", num, srcShaft, dstShaft);
	printEdit(hEdit, str);
	rHanoi(hEdit, num-1, auxShaft, dstShaft, srcShaft);
	}
}

//하노이탑 풀이를 화면에 출력하는 거 
void solveHanoiTower(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	TCHAR buff[BUFF_SIZE];
	DWORD fileSize;
	int data[DATA_NUM], dataNum, num;
	
	memset(buff, 0, sizeof(buff));
	fileSize = GetWindowTextLength(hDstEdit);
	fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	buff[fileSize] = NULL;
	sscanf(buff,"계산할 수는 : %d", &num);
	
	TCHAR str[TEXT_LENGTH];
	char srcShaft = 'A', dstShaft = 'C', auxShaft = 'B';
	
	sprintf(str, "\r\n 하노이 탑 결과(%c축 --> %c축). \r\n\r\n", srcShaft, dstShaft);
	printEdit(hDstEdit, str);
	
	rHanoi(hDstEdit, num, srcShaft, dstShaft, auxShaft); 
}

//에디터창에 문자열 추가 
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

//이진 검색 재귀버전 
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

//이진 검색 재귀로 한 거 출력 
void recursiveSearch(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	
	 TCHAR buff[BUFF_SIZE];
	  DWORD fileSize;
	  int data[DATA_NUM], dataNum, num;
	 
	  memset(buff, 0,sizeof(buff));
	  fileSize = GetWindowTextLength(hDstEdit);
	  fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	  buff[fileSize] = NULL;
	  sscanf(buff,"검색할 수는 : %d", &num); //포멧이 같아야한다.// 
	  
	  dataNum = readDataToArray(hSrcEdit, data);
	  
	  int searchNumPos = rSearch(data, 0, dataNum-1, num);
	  
	  TCHAR str[TEXT_LENGTH];
	  
	  memset(buff, 0,sizeof(buff));
	  if(searchNumPos == -1){
	  	sprintf(str, "%d는 원본 데이터에 없습니다. \r\n", num);
	  }else{
	  	sprintf(str, "%d는 원본 데이터의 \r\n%d번째에 있습니다. \r\n", num, searchNumPos+1);
	  }
	  strcat(buff, str);
	  SetWindowText(hDstEdit, buff);
}

//피보나치 수열을 입력과 출력하는 함수 
void calcuFibo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	  TCHAR buff[BUFF_SIZE];
	  DWORD fileSize;
	  int data[DATA_NUM], dataNum, num;
	 
	  memset(buff, 0,sizeof(buff));
	  fileSize = GetWindowTextLength(hDstEdit);
	  fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	  buff[fileSize] = NULL;
	  sscanf(buff,"계산할 수는 : %d", &num);
	  
	  memset(buff, 0, sizeof(buff));
	  TCHAR str[TEXT_LENGTH];
	  int tot;
	  if(num>0) {
	  	if(num ==1 || num == 2) tot = 1;
	  	else{
	  		tot = rFibo(num);
		  }
		  sprintf(str, "피보나치 수 %d항의 값은 %d입니다. \r\n",num,tot);
	  } else {
	  	sprintf(str, "%d는 자연수가 아닙니다. \r\n",num);
	  }
	  strcat(buff, str);
	  SetWindowText(hDstEdit, buff); 
}

//계산할 값 입력 받는 메서드 
 void calcuNumInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit) {
	 TCHAR buff[BUFF_SIZE];
	 TCHAR str[TEXT_LENGTH];
	 
	 memset(buff, 0, sizeof(buff));
	 SetWindowText(hDstEdit, buff); 
	
	 memset(buff, 0,sizeof(buff)); 
	 sprintf(str,"계산할 수는 :");
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
	  sscanf(buff,"계산할 수는 : %d", &num);
	 
	  int tot = rTot(num);
	  
	  TCHAR str[TEXT_LENGTH];
	  memset(buff, 0, sizeof(buff));
	  
	  sprintf(str,"1에서 %d까지의 합은 %d입니다. \r\n", num, tot);
	  strcat(buff,str);
	  SetWindowText(hDstEdit, buff);
 }
 
 //재귀함수로 num까지 합 구하기 
 int rTot(int num) {
	if(num==1) {
		return (1);
	}else{
		int res = num + rTot(num-1);
		return(res);
	}
}

//피보나치 수열 재귀함수로 표현 
int rFibo(int num) {
	if(num == 1 || num == 2) {
		return 1;
	}else{
		return rFibo(num-1) + rFibo(num-2);
	}
}
