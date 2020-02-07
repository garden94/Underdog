class listStack{ //리스트를 활용한 스택 구현 
	public:
		typedef struct queue_node{
			NUM_BTREE_NODE *node;
			struct queue_node *ptr;
		}QUEUE_NODE;
		
		QUEUE_NODE* top;
		
		listStack(){
			top = NULL;
		}
		
		~listStack(){
			QUEUE_NODE *tmp;
			while(top != NULL){
				tmp = top;
				top = top->ptr;
				delete tmp;
			} 
		}
		
		bool empty(){
			if(top == NULL)
				return true;
			else
				return false;
		}
		
		int push(NUM_BTREE_NODE *node){
			QUEUE_NODE *cNode;
			cNode = new QUEUE_NODE;
			if(cNode != NULL){ //동적할당을 바로 받았다. 
				cNode->node = node;
				cNode->ptr = NULL;
				if(empty()){
					top = cNode;
				}else{
					cNode->ptr = top;
					top = cNode;
				}
				return(0);
			}else{
				return(-1);
			}
		}
		
		NUM_BTREE_NODE *pop()
		{
			NUM_BTREE_NODE *tmp; 
			QUEUE_NODE *cNode; 
			if(!empty()){
				cNode = top;
				top = top->ptr;
				tmp = cNode->node;
				delete cNode;
				return(tmp);
			}else{
				return(NULL);
			}
		}
};
