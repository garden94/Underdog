class arrayStack{ //�迭�� Ȱ���ؼ� ���� ���� 
public: 
	int top;
	NUM_BTREE_NODE *data[MAXVALUE]; 
	
	arrayStack(){
		top = 0;
	}
	
	~arrayStack(){
	}
	
	bool empty(){
		if(top == 0)
			return true;
		else
			return false;
	}
	
	bool isFull(){
		if(top == MAXVALUE -1) //0���� �����ϴϱ� 
			return true; 
		else
			return false;
	}
	
	int push(NUM_BTREE_NODE *node){
		if(!isFull()){
			data[top] = node; 
			top = top + 1; 
			return(0); 
		}else{
			return(-1);
		}
	}
	
	NUM_BTREE_NODE *pop()
	{
		if(!empty()){
			top = top - 1;
			NUM_BTREE_NODE *tmp = data[top];
			return(tmp);
		}else{
			return(NULL);
		}
	}
};
