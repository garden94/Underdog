#define TEXT_LENGTH 500
#define MAX_DATA_NUM 300 
#define DATA_NUM 100 
#define BUFF_SIZE 3000
#define V_OPEN 1
#define V_SAVE 2
#define MAXVALUE 100

//노드 자료 구조 
typedef struct num_btree_node{
	int number;
	struct num_btree_node *lptr; //left
	struct num_btree_node *rptr; //right
}NUM_BTREE_NODE;
