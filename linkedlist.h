#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList List;
typedef struct Tupla Tupla;
typedef struct Nodo Nodo;
struct Tupla
{
	char* str;
	//char* token;
	int token;
};
struct Nodo
{
	Tupla tupla;
	Nodo* next;
};
struct LinkedList
{
	Nodo* root;
	int num;
};

//int insert_end(List* list, char *str, char *token);
int insert_end(List* list, char *str, int token);
//Nodo* crea_nodo(char* str, char* token);
Nodo* crea_nodo(char* str, int token);
int search(char* str, List* list);
void init_list(List *list);
void print(List* list);
void error(char* msg, char* yytxt,int ychar,int ycolumn);




//int insert_end(List* list, char *str, char *token)
int insert_end(List* list, char *str, int token)
{
	int pos = search(str,list);
	if (pos != -1)
	{
		return pos;
	}

	Nodo* newtmp = crea_nodo(str, token);
	Nodo* tmp = list->root;

	if (!list->root)
	{
		list->root = newtmp;
	}
	else
	{
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = newtmp;
	}
	list->num++;
	return list->num -1;
}
//Nodo* crea_nodo(char* str, char* token)
Nodo* crea_nodo(char* str, int token)
{
	Nodo* newnodo = (Nodo *)malloc(sizeof(Nodo));
	int len = strlen(str);	
	newnodo->tupla.str = malloc(len*sizeof(char));
	strcpy(newnodo->tupla.str,str);
	newnodo->tupla.token=token;
	newnodo->next = NULL;
	return newnodo;
}
int search(char* str, List* list)
{
	Nodo* tmp = list->root;
	int pos = 0;

	while(tmp)
	{
		if (strcmp(tmp->tupla.str,str) == 0)
		{
			return pos;
		}
		tmp = tmp->next;
		pos++;
	}
	return -1;
}

void init_list(List *list)
{
	list->root = NULL;
	list->num = 0;
}
void print(List* list)
{
	Nodo* tmp =  list->root;
	printf("Tabla de indices:\n");
	while(tmp != NULL)
	{
		printf("<%s, \t%d>\n",tmp->tupla.str, tmp->tupla.token);
		tmp = tmp->next;
	}
}

void error(char* msg, char* yytxt,int ychar,int ycolumn)
{
	printf("%s en: %s, línea: %d, caracter: %d\n",msg,yytext,ycolumn,ychar);
	exit(-1);
}


#endif
