#include <windows.h>
#include <tchar.h>
#include <Fileapi.h>
#include <stdio.h>
#include <winuser.h>
#include <string.h>
#include "myDefine.h"

#define ID_OPEN  1
#define ID_SAVE_AS 3
#define ID_MOVE 4
#define ID_PLUS_ONE 5 
#define ID_FIND_MAX_VALUE 6
#define ID_EXIT 9
#define ID_SEARCH_NUM_INPUT 7
#define ID_SEARCH_NUM 8
#define ID_LINEAR_SEARCH_NUM 11
#define ID_BINEARY_SEARCH_NUM 12
//���� ���� �޼���
#define ID_BUBBLE_SORT 21 
#define ID_SELECT_SORT 22
#define ID_INSERT_SORT 23

#define ID_CALCU_NUM_INPUT 31
#define ID_RECURS_TOT 32
#define ID_RECURS_FIBO 33
#define ID_RECURS_SEARCH 34
#define ID_HANOI_TOWER 35
#define ID_QUICK_SORT 36

//����ü �н��ϱ�
#define ID_READ_STUDENT_INFO 41
#define ID_STUDENT_SORT_NAME 42
#define ID_STUDENT_SORT_NUMBER 43
#define ID_STUDENT_DIRECT_READ 44
#define ID_STUDENT_INSERT_MEMBER 45
#define ID_STUDENT_DELETE_MEMBER_INPUT 46
#define ID_STUDENT_DELETE_MEMBER 47

//����Ʈ �н��ϱ�
#define ID_READ_STUDENT_INFO_LIST 51
#define ID_STUDENT_DIRECT_READ_LIST 52
#define ID_STUDENT_INSERT_MEMBER_LIST 53
#define ID_STUDENT_DELETE_MEMBER_LIST 54

//Ʈ������ �н��ϱ�
#define ID_MAKE_B_TREE 61
#define ID_BREADTH_FIRST_SEARCH_B_TREE 62
#define ID_DEPTH_FIRST_SEARCH_B_TREE 63
#define ID_VALUE_SEARCH_B_TREE 64
#define ID_VALUE_DELETE_B_TREE 65

void makeUI(HWND hwnd,HWND *hSrcEdit, HWND *hDstEdit, HWND *lbl_A, HWND *lbl_B);
void filePathReader(HWND hwnd, char *filePath, int flag);
void fileReader(HWND hwnd,HWND hSrcEdit, char *filePath);
void fileSaver(HWND hwnd,HWND hDstEdit, char *filePath);
void move(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void plusOne(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
int readDataToArray(HWND hSrcEdit, int *data);
void writeDataToWindows(HWND hDstEdit,int *data,int dataNum);
void writeSortDataToWindows(HWND hDstEdit,int *data,int dataNum, TCHAR *kind, int cmpNum, int cpNum);
void findMaxValue(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void searchNumInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void linearSearchNum(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void binearySearchNum(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void bubbleSorting(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void selectSorting(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void insertSorting(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void calcuNumInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void calcuTotal(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void calcuFibo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void recursiveSearch(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void solveHanoiTower(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void solveQuickSort(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void readStudentInfo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void sortStudentByName(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void sortStudentByTotal(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void directReadStudentInfo(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void insertStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMemberInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMember(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void readStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void directReadStudentInfoList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void insertStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void deleteStudentMemberList(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
//���� Ʈ�� �н��ϱ� 
void readDataMakeBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void breadthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void depthFirstSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void valueSearchBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
void valueDeleteBtree(HWND hwnd, HWND hSrcEdit, HWND hDstEdit);
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	static HWND hSrcEdit, hDstEdit, lbl_A, lbl_B; 						//�� ���� 
 	static TCHAR filePath[TEXT_LENGTH];
	switch(Message) {
			case WM_CREATE:{
		   makeUI(hwnd, &hSrcEdit, &hDstEdit, &lbl_A, &lbl_B);
		   break;
		  }
  
  		case WM_COMMAND: {
		   switch(LOWORD(wParam)){
		    case ID_OPEN: {								//������ �ҷ��´�. 
			     filePathReader(hwnd, filePath, V_OPEN);
			     fileReader(hwnd, hSrcEdit, filePath);     //���� â�� ��� 
			     break;
			    }
		    
		    case ID_SAVE_AS: {							//������ �����Ѵ�. 
			     filePathReader(hwnd, filePath, V_SAVE);
			     fileSaver(hwnd, hDstEdit, filePath);     //���� ������ ���� 
			     break;
			    }
		    
		    case ID_MOVE: {
			     move(hwnd, hSrcEdit, hDstEdit);     
			     break;
			    }
		    
		    case ID_PLUS_ONE : {
			     plusOne(hwnd, hSrcEdit, hDstEdit);     
			     break;
			    }
		    
		    case ID_FIND_MAX_VALUE:{
			     findMaxValue(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }
		    
		    case ID_SEARCH_NUM_INPUT:{ //�˻��� �� �Է¸� �ϱ� -> ���߿� �˻� ��� ���� 
			     searchNumInput(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }
		    
		    case ID_LINEAR_SEARCH_NUM:{
			     linearSearchNum(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }
		    
		    
		    case ID_BINEARY_SEARCH_NUM:{
			     binearySearchNum(hwnd, hSrcEdit, hDstEdit);
			     break;  
			    }
			    
		    case ID_BUBBLE_SORT:{
			     bubbleSorting(hwnd, hSrcEdit, hDstEdit);
			     break;  
			    }
		
		    case ID_SELECT_SORT:{
			     selectSorting(hwnd, hSrcEdit, hDstEdit);
			     break;  
			    }
		    
		    case ID_INSERT_SORT:{
			     insertSorting(hwnd, hSrcEdit, hDstEdit);
			     break;  
			    }
			    
			case ID_CALCU_NUM_INPUT:{	//����� �� �Է� �ޱ� 
			     calcuNumInput(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }    
		    case ID_RECURS_TOT:{  //�Է¹��� ����� ������ �� ���ϱ� 
			     calcuTotal(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }    
			case ID_RECURS_FIBO:{
			     calcuFibo(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }       
			case ID_RECURS_SEARCH:{		//���� �˻�(���) 
			     recursiveSearch(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }           
			 case ID_HANOI_TOWER:{	
			     solveHanoiTower(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }        
			 case ID_QUICK_SORT:{
			     solveQuickSort(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }   
				    
			 case ID_READ_STUDENT_INFO:{
			     readStudentInfo(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }   
				  
			case ID_STUDENT_SORT_NAME:{
			     sortStudentByName(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    }   
				  
			case ID_STUDENT_SORT_NUMBER:{
			     sortStudentByTotal(hwnd, hSrcEdit, hDstEdit);
			     break;   
			    } 
			//������ �ҷ��� �л����� ����ϱ�    
			case ID_STUDENT_DIRECT_READ:{
				 directReadStudentInfo(hwnd, hSrcEdit, hDstEdit);
				 break;
			}       
			case ID_STUDENT_INSERT_MEMBER:{
				 insertStudentMember(hwnd, hSrcEdit, hDstEdit);
				 break;
			}  
			case ID_STUDENT_DELETE_MEMBER_INPUT:{
				 deleteStudentMemberInput(hwnd, hSrcEdit, hDstEdit);
				 break;
			}  
			case ID_STUDENT_DELETE_MEMBER:{
				 deleteStudentMember(hwnd, hSrcEdit, hDstEdit);
				 break;
			}       	
			case ID_READ_STUDENT_INFO_LIST:{
				 readStudentInfoList(hwnd, hSrcEdit, hDstEdit);
				 break;
			}      
			case ID_STUDENT_DIRECT_READ_LIST:{
				 directReadStudentInfoList(hwnd, hSrcEdit, hDstEdit);
				 break;
			}  	    
			case ID_STUDENT_INSERT_MEMBER_LIST:{
				 insertStudentMemberList(hwnd, hSrcEdit, hDstEdit);
				 break;
			}  	
			case ID_STUDENT_DELETE_MEMBER_LIST:{
				 deleteStudentMemberList(hwnd, hSrcEdit, hDstEdit);
				 break;
			}  	   	
			case ID_MAKE_B_TREE:{
				 readDataMakeBtree(hwnd, hSrcEdit, hDstEdit);
				 break;
			}  	   		
			case ID_BREADTH_FIRST_SEARCH_B_TREE:{
				 breadthFirstSearchBtree(hwnd, hSrcEdit, hDstEdit);
				 break;
			}  	   	
			case ID_DEPTH_FIRST_SEARCH_B_TREE:{
				 depthFirstSearchBtree(hwnd, hSrcEdit, hDstEdit);
				 break;
			}  	   		
			case ID_VALUE_SEARCH_B_TREE:{
				 valueSearchBtree(hwnd, hSrcEdit, hDstEdit);
				break;
			}
			case ID_VALUE_DELETE_B_TREE:{
				 valueDeleteBtree(hwnd, hSrcEdit, hDstEdit);
				break;
			}		      		      
		    case ID_EXIT: {
			     CloseWindow(hwnd);
			     DestroyWindow(hwnd);
			     break;
			    }    
			    
		   }
		   break; 
		  }
  
		case WM_SIZE:{ 				//ȭ�� ũ�� ��ȭ�� ���� ������ â ��ȭ 
		   RECT rect;
		   GetClientRect(hwnd, &rect);
		   MoveWindow(lbl_B, rect.right/2+10, 10, 100, 20,TRUE);
		   MoveWindow(hSrcEdit, 10, 40, rect.right/2-20, rect.bottom-50,TRUE);
		   MoveWindow(hDstEdit, rect.right/2+10, 40, rect.right/2-20, rect.bottom-50,TRUE);
		   break;
		  }
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

void makeUI(HWND hwnd,HWND *hSrcEdit, HWND *hDstEdit, HWND *lbl_A, HWND *lbl_B){
	 HMENU hMenubar = CreateMenu();
	 HMENU hFile = CreateMenu();
	 HMENU hProc = CreateMenu();
	 HMENU hSort = CreateMenu();
	 HMENU hRecurs = CreateMenu();
	 HMENU hStruct = CreateMenu();
	 HMENU hList = CreateMenu();
	 HMENU hBtree = CreateMenu();
	  
	 AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, "File");
	 AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hProc, "Process");
	 AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hSort, "Sorting"); 
	 AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hRecurs, "Recursive");
	 AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hStruct, "Struct");
	 AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hList, "List");
	 AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hBtree, "Btree");
	 
	 AppendMenu(hFile, MF_POPUP, ID_OPEN, "����");
	 AppendMenu(hFile, MF_POPUP, ID_SAVE_AS, "�����ϱ�");
	 AppendMenu(hFile, MF_POPUP, ID_EXIT, "Exit");
	 
	 AppendMenu(hProc, MF_POPUP, ID_MOVE, "�̵��ϱ�");
	 AppendMenu(hProc, MF_POPUP, ID_PLUS_ONE, "1���ϱ�");
	 AppendMenu(hProc, MF_POPUP, ID_FIND_MAX_VALUE, "�ִ밪 ���ϱ�");    
	 AppendMenu(hProc, MF_POPUP, ID_SEARCH_NUM_INPUT, "�˻��� �� �Է��ϱ�");
	 AppendMenu(hProc, MF_POPUP, ID_LINEAR_SEARCH_NUM, "���� ������ �˻��ϱ�");
	 AppendMenu(hProc, MF_POPUP, ID_BINEARY_SEARCH_NUM, "���� ������ �˻��ϱ�");
	
	 AppendMenu(hSort, MF_POPUP, ID_BUBBLE_SORT, "���� ����");
	 AppendMenu(hSort, MF_POPUP, ID_SELECT_SORT, "���� ����");
	 AppendMenu(hSort, MF_POPUP, ID_INSERT_SORT, "���� ����");
	
	 AppendMenu(hRecurs, MF_POPUP, ID_CALCU_NUM_INPUT, "����� �� �Է��ϱ�");
	 AppendMenu(hRecurs, MF_POPUP, ID_RECURS_TOT, "n���� �� ���ϱ�");
	 AppendMenu(hRecurs, MF_POPUP, ID_RECURS_FIBO, "�Ǻ���ġ�� ���ϱ�");
	 AppendMenu(hRecurs, MF_POPUP, ID_RECURS_SEARCH, "�����˻�(���)");
	 AppendMenu(hRecurs, MF_POPUP, ID_HANOI_TOWER, "�ϳ��� ž Ǯ��");
	 AppendMenu(hRecurs, MF_POPUP, ID_QUICK_SORT, "��(Quick) ��Ʈ");
	
	 AppendMenu(hStruct, MF_POPUP, ID_READ_STUDENT_INFO, "�л������б�(����)");
	 AppendMenu(hStruct, MF_POPUP, ID_STUDENT_SORT_NAME, "�̸����� �����ϱ�");
	 AppendMenu(hStruct, MF_POPUP, ID_STUDENT_SORT_NUMBER, "�������� �����ϱ�");
	 AppendMenu(hStruct, MF_POPUP, ID_STUDENT_DIRECT_READ, "���Ͽ��� �ٷ� �б�");
	 AppendMenu(hStruct, MF_POPUP, ID_STUDENT_INSERT_MEMBER, "���ĵ� �����Ϳ� ��� �߰��ϱ�");
	 AppendMenu(hStruct, MF_POPUP, ID_STUDENT_DELETE_MEMBER_INPUT, "������ �̸���?");
	 AppendMenu(hStruct, MF_POPUP, ID_STUDENT_DELETE_MEMBER, "�Է��� �л� ���� �����ϱ�");
	
	 AppendMenu(hList, MF_POPUP, ID_READ_STUDENT_INFO_LIST, "Edit â���� �л������б�(List)");
	 AppendMenu(hList, MF_POPUP, ID_STUDENT_DIRECT_READ_LIST, "���ĵ� ���Ͽ��� �ٷ� �б�(List)");
	 AppendMenu(hList, MF_POPUP, ID_STUDENT_INSERT_MEMBER_LIST, "���ĵ� �����Ϳ� ��� �߰��ϱ�(List)");
	 AppendMenu(hList, MF_POPUP, ID_STUDENT_DELETE_MEMBER_LIST, "�Է��� �л� ���� �����ϱ�(List)");
	
	 AppendMenu(hBtree, MF_POPUP, ID_MAKE_B_TREE, "���� Ʈ�� ����");
	 AppendMenu(hBtree, MF_POPUP, ID_BREADTH_FIRST_SEARCH_B_TREE, "�ʺ� �켱 Ž��(Btree)");
	 AppendMenu(hBtree, MF_POPUP, ID_DEPTH_FIRST_SEARCH_B_TREE, "���� �켱 Ž��(Btree)");
	 AppendMenu(hBtree, MF_POPUP, ID_VALUE_SEARCH_B_TREE, "Ʈ������ �� ã��(Btree)");
	 AppendMenu(hBtree, MF_POPUP, ID_VALUE_DELETE_B_TREE, "Ʈ������ �� �����ϱ�(Btree)");
	 SetMenu(hwnd, hMenubar);
	   
	 RECT rect;						//������ ȭ�� ����� 
	 GetClientRect(hwnd, &rect);
	 *lbl_A = CreateWindow(_T("STATIC"), _T("Source Data : "), WS_CHILD|WS_VISIBLE,
	      10,10, 100, 20,hwnd, NULL,NULL,NULL);					
	 *lbl_B = CreateWindow(_T("STATIC"), _T("Result Data : "), WS_CHILD|WS_VISIBLE,
	      rect.right/2+10,10, 100, 20,hwnd, NULL,NULL,NULL);      
	 *hSrcEdit = CreateWindow(_T("Edit"), NULL,
	   WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|WS_BORDER
	   |ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE,
	   10, 40, rect.right/2-20, rect.bottom-50, hwnd, NULL,NULL,NULL);
	 *hDstEdit = CreateWindow(_T("Edit"), NULL,
	   WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|WS_BORDER
	   |ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE,
	   rect.right/2+10, 40, rect.right/2-20, rect.bottom-50, hwnd, NULL,NULL,NULL);   
}

void filePathReader(HWND hwnd, char *filePath, int flag){		//���� ��� �������� 
	 OPENFILENAME OFN;
	 TCHAR str[TEXT_LENGTH], lpstrFile[TEXT_LENGTH];
	 TCHAR filter[] = "Text File \0 *.txt;*.doc \0Every File(*.*)\0 *.*\0 ";
	 
	 memset(lpstrFile, 0, sizeof(lpstrFile));
	 memset(&OFN, 0, sizeof(OPENFILENAME));
	 OFN.lStructSize = sizeof(OPENFILENAME);
	 OFN.hwndOwner = hwnd;
	 OFN.lpstrFilter = filter;
	 OFN.lpstrFile = lpstrFile;
	 OFN.nMaxFile = TEXT_LENGTH;
	 if(flag == V_OPEN){ //ID_OPEN 
	  if(GetOpenFileName(&OFN) != 0){
	   sprintf(filePath, "%s", OFN.lpstrFile);
	  }
	}else{	//ID_SAVE_AS
	  if(GetSaveFileName(&OFN) != 0){
	   sprintf(filePath, "%s", OFN.lpstrFile);
	  } 
	}
}

void fileReader(HWND hwnd, HWND hEdit, char *filePath){			//���� �о� ������ â�� ����� 
	 HANDLE hFile;
	 TCHAR buff[BUFF_SIZE];
	 TCHAR str[TEXT_LENGTH];
	 DWORD fileSize;
	 hFile = CreateFile(_T(filePath), GENERIC_READ,
	     FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
	 if(hFile == INVALID_HANDLE_VALUE){
	  sprintf(str, "%s ������ ���� �����ϴ�. ", filePath);
	  MessageBox(hwnd, str,"FILE ����", MB_OK);
	  return;      
	 }
	 
	 memset(buff, 0, sizeof(buff));
	 
	 ReadFile(hFile, buff, (BUFF_SIZE-1)*sizeof(TCHAR),&fileSize, NULL);
	 CloseHandle(hFile);
	 
	 SetWindowText(hEdit, buff); 
}

void fileSaver(HWND hwnd,HWND hEdit, char *filePath){  //������ â�� �ִ� ������ �����Ѵ�. 
	 HANDLE hFile;
	 TCHAR buff[BUFF_SIZE];
	 TCHAR str[TEXT_LENGTH];
	 DWORD fileSize;
	 hFile = CreateFile(_T(filePath), GENERIC_WRITE,
	     FILE_SHARE_READ,NULL,CREATE_ALWAYS,0,0);
	 if(hFile == INVALID_HANDLE_VALUE){
	  sprintf(str, "%s ������ ���� �����ϴ�. ", filePath);
	  MessageBox(hwnd, str,"FILE ����", MB_OK);
	  return;      
	 }
	 
	 memset(buff, 0, sizeof(buff));
	 
	 fileSize = GetWindowTextLength(hEdit);
	 fileSize = GetWindowText(hEdit,(LPTSTR)buff, fileSize+1);
	 buff[fileSize] = NULL;
	 WriteFile(hFile, buff, fileSize*sizeof(TCHAR),(LPDWORD)&fileSize, NULL);
	 
	 CloseHandle(hFile);
}

void move(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){ 	//���� â���� ������ â���� ������ �Լ� 
	 TCHAR buff[BUFF_SIZE];
	 DWORD fileSize;
	
	 memset(buff, 0, sizeof(buff));
	 
	 fileSize = GetWindowTextLength(hSrcEdit);
	 fileSize = GetWindowText(hSrcEdit,(LPTSTR)buff, fileSize+1);
	 buff[fileSize] = NULL;
	 
	 SetWindowText(hDstEdit, buff); 
}


void plusOne(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){ //���� â�� �ִ� ���ڸ� �о +1 �ϰ� ���� â�� ��� 
	 int data[100];
	 int dataNum;
	
	 
	 dataNum = readDataToArray(hSrcEdit, data);
	 
	 for(int i=0; i<dataNum; i++){
	  data[i]=data[i]+1;
	 }
	 
	 writeDataToWindows(hDstEdit, data, dataNum);
 
}


int readDataToArray(HWND hSrcEdit, int *data){ //�迭 ���� �������� 
	 TCHAR buff[BUFF_SIZE];
	 DWORD fileSize;
	 
	 
	 memset(buff, 0, sizeof(buff));
	 fileSize = GetWindowTextLength(hSrcEdit);
	 fileSize = GetWindowText(hSrcEdit,(LPTSTR)buff, fileSize+1);
	 buff[fileSize] = NULL;
	 
	 int dataNum = 0;
	 char *tok2 = strtok(buff,"\r\n");
	 while(tok2!=NULL){
	  data[dataNum] = atoi(tok2);
	  tok2 = strtok(NULL,"\r\n");
	  dataNum++;
	 }
	 
	return dataNum;
	 
}

void writeDataToWindows(HWND hDstEdit,int *data,int dataNum){ //�迭���� ����ϱ� 
	 TCHAR buff[BUFF_SIZE];
	 TCHAR str[TEXT_LENGTH];
	 
	 memset(buff, 0, sizeof(buff));
	 for(int i=0; i<dataNum; i++){
	  sprintf(str,"%d\r\n",data[i]);
	  strcat(buff,str);
	 }
	 
	 SetWindowText(hDstEdit, buff);
}

void findMaxValue(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){ //�ִ밪 ���ϱ� 
	 int data[MAX_DATA_NUM];
	 int dataNum;
	 int maxValue, maxValuePos[MAX_DATA_NUM];
	 int maxDataNum;
	 
	 dataNum = readDataToArray(hSrcEdit, data);
	 
	 maxValue = data[0];	//�ִ밪 ������ �迭 ù��°�� ���� 
	 for(int i=0; i<dataNum; i++){	//�迭 �ϳ��ϳ� ���� ���Ѵ�. 
	  if(maxValue < data[i]){
	   maxValue = data[i];
	  }
   }
 
 
	 maxDataNum = 0;
	 for(int i=0; i<dataNum; i++){       //�ִ� ��ġ ���ϱ�// 
	  if(maxValue == data[i]){
	   maxValuePos[maxDataNum] = i;
	   maxDataNum++;
	  }
	 }
	 
	 TCHAR buff[BUFF_SIZE];
	 TCHAR str[TEXT_LENGTH];
	 
	 memset(buff, 0, sizeof(buff));
	 sprintf(str,"�ִ밪 :%d\r\n�ִ밪 ��ġ :",maxValue);
	 strcat(buff,str);
	 for(int i=0; i<maxDataNum; i++){
	  sprintf(str,"%d,",maxValuePos[i]+1);
	  strcat(buff,str);
	 }
	
	 sprintf(str,"\r\n");
	 strcat(buff,str);
	 
	 SetWindowText(hDstEdit, buff);
	  
}

void searchNumInput(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){	//�˻��� ���� �Է� �޴´� 
	 TCHAR buff[BUFF_SIZE];
	 TCHAR str[TEXT_LENGTH];
	 
	 memset(buff, 0, sizeof(buff));
	 SetWindowText(hDstEdit, buff);  
	
	 memset(buff, 0, sizeof(buff));  
	 sprintf(str,"�˻��� ���� :");
	 strcat(buff,str);
	 
	 SetWindowText(hDstEdit,buff);
	 
}

void linearSearchNum(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){	//���� ������ �˻� 
	 TCHAR buff[BUFF_SIZE];
	 DWORD fileSize;
	 int data[DATA_NUM], dataNum, num;
	 
	 memset(buff, 0,sizeof(buff));
	 fileSize = GetWindowTextLength(hDstEdit);
	 fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	 buff[fileSize] = NULL;
	 sscanf(buff,"�˻��� ���� : %d", &num);
	 
	 dataNum = readDataToArray(hSrcEdit, data); 
	 
	 int searchNumPos = -1, cmpNum=0;
	 for(int i=0; i<dataNum; i++){  //��Ƚ�� ���� 
	  cmpNum++;
	  if(data[i] == num){
	   searchNumPos =i;
	   break;
	  } 
}	  
	  TCHAR str[TEXT_LENGTH];
	  
	  memset(buff, 0, sizeof(buff));
	  if(searchNumPos == -1){
	    sprintf(str,"%d �� ���� �����Ϳ� �����ϴ�. \r\n", num);
	      }else{
	    sprintf(str,"%d �� ���� �������� \r\n%d��° �ֽ��ϴ�. \r\n", num, searchNumPos+1);
	  }
	  strcat(buff,str);
	  sprintf(str,"�� Ƚ���� %d�� �Դϴ�. \r\n", cmpNum);
	  strcat(buff,str);
	  
	  SetWindowText(hDstEdit, buff);
 
 
}


void binearySearchNum(HWND hwnd, HWND hSrcEdit, HWND hDstEdit){ 	//���� �˻�, ���ĵ� �����͸� �����ϴ�. 
	 TCHAR buff[BUFF_SIZE];
	 DWORD fileSize;
	 int data[DATA_NUM], dataNum, num;
	 
	 memset(buff, 0,sizeof(buff));
	 fileSize = GetWindowTextLength(hDstEdit);
	 fileSize = GetWindowText(hDstEdit,(LPTSTR)buff, fileSize+1);
	 buff[fileSize] = NULL;
	 sscanf(buff,"�˻��� ���� : %d", &num);
	 
	 dataNum = readDataToArray(hSrcEdit, data); 
	 
	 int searchNumPos = -1, cmpNum=0;
	 int fPos = 0, ePos = dataNum, mPos;  //fPos�� �տ� �ִ� ��, ePos�� �� �� 
	 while (fPos < ePos){
	  mPos = int((fPos+ePos)/2);
	  cmpNum++;
	  if(data[mPos] == num){  //�߰����̶� �˻��� ���� ����ؼ� �� 
	  	searchNumPos = mPos;
	  	break;
	  }
	  cmpNum++; 
	  if(data[mPos] < num) { 
	  	fPos = mPos;
	  }else{
	  	ePos = mPos;
	  }
  }

  
	 TCHAR str[TEXT_LENGTH];
	  
	 memset(buff, 0, sizeof(buff));
	 if(searchNumPos == -1){
	   sprintf(str,"%d �� ���� �����Ϳ� �����ϴ�. \r\n", num);
	    }else{
	   sprintf(str,"%d �� ���� �������� \r\n%d��° �ֽ��ϴ�. \r\n", num, searchNumPos+1);
	 }
	 strcat(buff,str);
	 sprintf(str,"�� Ƚ���� %d�� �Դϴ�. \r\n", cmpNum);
	 strcat(buff,str);
	 
	 SetWindowText(hDstEdit, buff);

}
