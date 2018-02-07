typedef struct Node{
	unsigned long int id;
	void *value;
	struct Node *next;
	struct Node *front;
} Node;

typedef struct List{
	Node *head;
	Node *tail;
	unsigned long int length;
} List;

List *init_list();
Node *init_node();
int insertInHead(List *p_list, Node *p_node);
int insertInTail(List*p_list, Node *p_node);
int removeById(List *p_list, unsigned long id);
int removeByNode(List *p_list, Node *p_node);
int popFromHead(List *p_list);
int popFromTail(List *p_list);
unsigned long int len(List *p_list);
Node *findById(List *p_list, unsigned long int id);
Node *findByValue(List *p_list, char type[], void *value);
