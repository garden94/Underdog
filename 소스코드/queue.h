class Queue{//���� ť 
public: //Ŭ���� �ۿ��� ���� ������ ����,�Լ� 
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
			rear = (rear + 1) % MAXVALUE; //�������� �־�� ���� �Ǵϱ�
			return(0); 
		}else{
			return(-1);
		}
	}
	
	NUM_BTREE_NODE *pop()
	{
		if(!empty()){
			NUM_BTREE_NODE *tmp = values[front]; //�ּҰ��� ����. 
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
			return true; //�� ����. 
		else
			return false;
	}
};
