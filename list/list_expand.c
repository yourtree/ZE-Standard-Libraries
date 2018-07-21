#include "list_expand.h"

Node *nodeWithInt(int m_int) {
	Node *p_node;
	int *p_int = (int *)malloc(sizeof(int));
	*p_int = m_int;
	p_node = initNode();
	initMallocValueForNode(p_node, "int", (void *)p_int);
	return p_node;
}

Node *nodeWithDouble(double m_double) {
	Node *p_node;
	double *p_double = (double *)malloc(sizeof(double));
	*p_double = m_double;
	p_node = initNode();
	initMallocValueForNode(p_node, "double", (void *)p_double);
	return p_node;
}

Node *nodeWithString(const char *m_string) {
	Node *p_node;
	char *p_string = (char *)malloc(sizeof(char)*(strlen(m_string) + 1));
	strcpy_s(p_string, sizeof(p_string), m_string);
	p_node = initNode();
	initMallocValueForNode(p_node, "string", (void *)p_string);
	return p_node;
}

Node *nodeWithPointer(void *m_pointer) {
	Node *p_node = initNode();
	initMallocValueForNode(p_node, "pointer", m_pointer);
	return p_node;
}

Node *nodeWithComplex(void) {
	Node *p_node = initNode();
	p_node->type = "list";
	p_node->value = initList();
	p_node->if_malloc = 1;
	return p_node;
}

Node *findByIndexForNode(List *p_list, unsigned long long m_index) {
	Node *p_node = p_list->head;
	unsigned long long i;
	for (i = 0; i < m_index; i++) {
		p_node = p_node->next;
	}
	return p_node;
}

int listThrough(List *p_list, int(*p_func)(const char *, void *)) {
	Node *p_node = p_list->head;
	while (p_node != NULL) {
		if (p_node->if_malloc == 1) {
			int m_return = (*p_func)(p_node->type, p_node->value);
			if (m_return == -1) break;
			else if (m_return == 1) {
				p_node = p_node->last;
				continue;
			}
			else {

			}
		}
		p_node = p_node->next;
	}
	return 0;
}

int getByIntForNode(Node *p_node) {
	if (!strcmp(p_node->type, "int")) return *(int *)(p_node->value);
	else return -1;
}

char *getByStringForNode(Node *p_node) {
	if (!strcmp(p_node->type, "string")) return (char *)(p_node->value);
	else return NULL;
}

double getByDoubleForNode(Node *p_node) {
	if (!strcmp(p_node->type, "double")) return *(double *)(p_node->value);
	else return -1;
}

void *getByPointerForNode(Node *p_node) {
	if (!strcmp(p_node->type, "pointer")) return (void *)(p_node->value);
	else return NULL;
}

void printListInfo(List *p_list, int priority) {
	int i = 0;
	Node *p_node;
	for (i = 0; i < priority; i++) printf("   ");
	printf("###LIST(location:%p, id:%llu){\n", p_list, p_list->id);
	for (i = 0; i < priority + 1; i++) printf("   ");
	printf("HEAD->%p / Tail->%p / Length:%llu\n", p_list->head, p_list->tail, p_list->length);
	p_node = p_list->head;
	while (p_node != NULL) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("%d.... \n", i);
		printNodeInfo(p_node, priority + 1);
		p_node = p_node->next;
		i++;
	}
	for (i = 0; i < priority; i++) printf("   ");
	printf("}\n");

}

void printList(List *p_list) {
	int if_nearLast = 0;
	Node *p_node = p_list->head;
	printf("[");
	while (p_node != NULL) {
		if (!if_nearLast && p_node->next == NULL) if_nearLast = 1;
		if (!strcmp(p_node->type, "int")) {
			printf("%d", *(int *)(p_node->value));
		}
		else if (!strcmp(p_node->type, "double")) {
			printf("%a", *(double *)(p_node->value));
		}
		else if (!strcmp(p_node->type, "string")) {
			printf("%s", (char *)(p_node->value));
		}
		else if (!strcmp(p_node->type, "pointer")) {
			printf("%p", (char *)(p_node->value));
		}
		else if (!strcmp(p_node->type, "list")) {
			printList((List *)p_node->value);
		}
		if (!if_nearLast) {
			printf(", ");
		}
		p_node = p_node->next;
	}
	printf("]");
}

void printNodeInfo(Node *p_node, int priority) {
	int i;
	for (i = 0; i < priority; i++) printf("   ");
	printf("#NODE(location:%p, id:%llu){\n", p_node, p_node->id);
	for (i = 0; i < priority + 1; i++) printf("   ");
	printf("NEXT->%p / LAST->%p / MALLOC:%d\n", p_node->next, p_node->last, p_node->if_malloc);
	if (!strcmp(p_node->type, "int")) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(int):%d\n", *(int *)(p_node->value));
	}
	else if (!strcmp(p_node->type, "double")) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(double):%a\n", *(double *)(p_node->value));
	}
	else if (!strcmp(p_node->type, "string")) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(string):%s\n", (char *)(p_node->value));
	}
	else if (!strcmp(p_node->type, "pointer")) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(pointer):%s\n", (char *)(p_node->value));
	}
	else if (!strcmp(p_node->type, "list")) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(List):\n");
		printListInfo((List *)p_node->value, priority + 2);
	}
	for (i = 0; i < priority; i++) printf("   ");
	printf("}\n");
}

void printNode(Node *p_node) {
	int i;
	printf("#NODE(location:%p, id:%llu){\n", p_node, p_node->id);
	printf("   ");
	printf("NEXT->%p / LAST->%p\n", p_node->next, p_node->last, p_node->if_malloc);
	for (i = 0; i < 1; i++) printf("   ");
	printf("ifMalloc: ");
	if (p_node->if_malloc) {
		printf("YES\n");
		for (i = 0; i < 1; i++) printf("   ");
		printf("Value(type: %s): ", p_node->type);
		if (!strcmp(p_node->type, "int")) {
			printf("%d", *(int *)(p_node->value));
		}
		else if (!strcmp(p_node->type, "double")) {
			printf("%a\n", *(double *)(p_node->value));
		}
		else if (!strcmp(p_node->type, "string")) {
			printf("%s\n", (char *)(p_node->value));
		}
		else if (!strcmp(p_node->type, "pointer")) {
			printf("%s\n", (char *)(p_node->value));
		}
		else if (!strcmp(p_node->type, "list")) {
			printList((List *)p_node->value);
		}
	}
	else printf("NO\n");
	
	printf("}\n");
}


Node *findByIntForNode(List *p_list, int target) {
	Node *t_node;
	int *p_target = (int *)malloc(sizeof(int));
	*p_target = target;
	t_node = findByValue(p_list, "int", p_target);
	free(p_target);
	return t_node;
}

Node *findByDoubleForNode(List *p_list, double target) {
	Node *t_node;
	double *p_target = (double *)malloc(sizeof(double));
	*p_target = target;
	t_node = findByValue(p_list, "double", p_target);
	free(p_target);
	return t_node;
}

Node *findByStringForNode(List *p_list, char *target) {
	Node *t_node;
	char *p_temp = (char *)malloc(sizeof(char)*(strlen(target) + 1));
	strcpy_s(p_temp, sizeof(p_temp), target);
	t_node = findByValue(p_list, "string", p_temp);
	free(p_temp);
	return t_node;
}

Node *findByPointerForNode(List *p_list, void *target) {
	Node *t_node = findByValue(p_list, "pointer", target);
	return t_node;
}

int addValueForComplex(Node * p_node, char *type, void *value) {
	List *c_list;
	Node *c_node;
	if (!strcmp(p_node->type, "list")) {
		c_list = (List *)p_node->value;
		c_node = initNode();
		initMallocValueForNode(c_node, type, value);
		insertInTail(c_list, c_node);
		return  0;
	}
	return  -1;
}

int addIntForComplex(Node *p_node, int temp) {
	if (!strcmp(p_node->type, "list")) {
		int *p_temp = (int *)malloc(sizeof(int));
		*p_temp = temp;
		addValueForComplex(p_node, "int", p_temp);
		return 0;
	}
	return -1;
}

int addDoubleForComplex(Node *p_node, double temp) {
	if (!strcmp(p_node->type, "list")) {
		double *p_temp = (double *)malloc(sizeof(double));
		*p_temp = temp;
		addValueForComplex(p_node, "double", p_temp);
		return 0;
	}
	return -1;
}

int addStringForComplex(Node *p_node, char *temp) {
	if (!strcmp(p_node->type, "list")) {
		char *p_temp = (char *)malloc(sizeof(strlen(temp) + 1));
		strcpy_s(p_temp, sizeof(p_temp), temp);
		addValueForComplex(p_node, "string", p_temp);
		return 0;
	}
	return -1;
}

int addPointerForComplex(Node *p_node, void *temp) {
	if (!strcmp(p_node->type, "list")) {
		addValueForComplex(p_node, "pointer", temp);
		return 0;
	}
	return -1;
}

List *m_findByInt(List* p_list, int temp) {
	int *p_temp = (int *)malloc(sizeof(int));
	List *t_list;
	*p_temp = temp;
	t_list = mply_findByValue(p_list, "int", (void *)p_temp);
	free(p_temp);
	return t_list;
}

List *m_findByDouble(List* p_list, double temp) {
	List *t_list;
	double *p_temp = (double *)malloc(sizeof(double));
	*p_temp = temp;
	t_list = mply_findByValue(p_list, "double", (void *)p_temp);
	free(p_temp);
	return t_list;
}

List *m_findByString(List* p_list, char *temp) {
	List *t_list;
	char *p_temp = (char *)malloc(sizeof(char)*(strlen(temp) + 1));
	strcpy_s(p_temp, sizeof(p_temp), temp);
	t_list = mply_findByValue(p_list, "string", (void *)p_temp);
	free(p_temp);
	return t_list;
}

List *m_findByPointer(List* p_list, void *temp) {
	List *t_list = mply_findByValue(p_list, "double", (void *)temp);
	return t_list;
}

unsigned long long getIndexByNode(List *p_list, Node *p_node) {
	Node *t_node = p_list->head;
	unsigned long long index = 0;
	while (t_node != NULL) {
		if (p_node->id == t_node->id) return index;
		index++;
		t_node = t_node->next;
	}
	return 0;
}

List *m_findByIntForNode(List* p_list, int temp) {
	int *p_temp = (int *)malloc(sizeof(int));
	*p_temp = temp;
	return mply_findByValue(p_list, "int", (void *)p_temp);
}

List *m_findByDoubleForNode(List* p_list, double temp) {
	double *p_temp = (double *)malloc(sizeof(double));
	*p_temp = temp;
	return mply_findByValue(p_list, "double", (void *)p_temp);
}

List *m_findByStringForNode(List* p_list, char *temp) {
	char *p_temp = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
	strcpy_s(p_temp, sizeof(p_temp), temp);
	return mply_findByValue(p_list, "string", (void *)p_temp);
}

List *m_findByPointerForNode(List* p_list, void *temp) {
	return mply_findByValue(p_list, "pointer", (void *)temp);
}