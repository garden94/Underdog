class ListQueue{ //����Ʈ ť 
	public:
		typedef struct quene_node{
			NUM_BTREE_NODE *node;
			struct quene_node *ptr;
		}QUEUE_NODE;
		
		QUEUE_NODE *front;
		QUEUE_NODE *rear;
		
		ListQueue(){
			front = NULL;
			rear = NULL;
		}
		
		~ListQueue(){
			QUEUE_NODE *tmp;
			while(front != NULL){
				tmp = front;
				front = front->ptr;
				delete tmp;
			} //Ʈ���� �������� �� �ƴ϶� ť�� �������� �Ŵ�. 
		}
		
		int push(NUM_BTREE_NODE *value){
			QUEUE_NODE *cNode;
			cNode = new QUEUE_NODE;
			if(cNode != NULL){
				cNode->node = value;
				cNode->ptr = NULL;
				if(empty()){
					front = cNode;
					rear = cNode;
				}else{
					rear->ptr = cNode;
					rear = cNode;
				}
				return(0);
			}else{
				return(-1);
			}
		}
		NUM_BTREE_NODE *pop(){
			NUM_BTREE_NODE *tmp; //������ �Ҵ��� �ſ��� ���� �Ҵ��̴�.(�ý��� ����) 
			QUEUE_NODE *cNode; //���� �Ҵ��̾  delete������Ѵ�. 
			if(!empty()){
				cNode = front;
				front = front->ptr;
				if(front == NULL) rear = NULL;
				tmp = cNode->node;
				delete cNode;
				return(tmp);
			}else{
				return(NULL);
			}
		}
		
		bool empty(){
			if(front == NULL & rear == NULL)
				return true;
			else
				return false;
		}
};
