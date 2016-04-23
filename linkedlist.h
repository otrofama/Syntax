#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
void error();
//void error(char* msg, char* yytxt,int ychar,int ycolumn);




//int insert_end(List* list, char *str, char *token)

#endif
