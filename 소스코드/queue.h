class Queue{//원형 큐 
public: //클래스 밖에서 접근 가능한 변수,함수 
	int front;
	int rear;
	NUM_BTREE_NODE *values[MAXVALUE]; 
	
	Queue(){
		front = 0;
		rear = 0;
	}
	
	~Queue(){
	}
	
	int push(NUM_BTREE_NODE *value){
		if(!isFull()){
			values[rear] = value; 
			rear = (rear + 1) % MAXVALUE; //나머지를 넣어야 원이 되니까
			return(0); 
		}else{
			return(-1);
		}
	}
	
	NUM_BTREE_NODE *pop()
	{
		if(!empty()){
			NUM_BTREE_NODE *tmp = values[front]; //주소값이 들어간다. 
			front = (front + 1) % MAXVALUE;
			return(tmp);
		}else{
			return(NULL);
		}
	}
	
	bool empty(){
		if(rear == front)
			return true;
		else
			return false;
	}
	
	bool isFull(){
		if((rear + 1) % MAXVALUE == front)
			return true; //꽉 찬거. 
		else
			return false;
	}
};
