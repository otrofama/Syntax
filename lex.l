%{
#include <stdio.h>
#include "token.h"
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
List* list;
int columns=0;	//variable que cuenta caracteres
int comment=0;	//si hay comentario abierto

%}

letra [a-zA-Z]
digito [0-9]
id (_|{letra})(_|{letra}|{digito}) 
car \'.\'
ent {digito}+
real {digito}*"."{digito}+
%option yylineno
%s comentario

%%

<INITIAL>
{
	int { columns+=yyleng;
		//printf("%d\n", yylineno);
		yylval.line=yylineno;
		insert_end(list,"int",INT);
		return INT;}

	float {columns+=yyleng;
		//printf("%d\n", yylineno);
		insert_end(list,"float",FLOAT);
		yylval.line=yylineno;
		return FLOAT;}
	char {columns+=yyleng;
		yylval.line=yylineno;
		insert_end(list,"char",CHAR);
		return CHAR;}
	if {columns+=yyleng;
		yylval.line=yylineno;
		insert_end(list,"if",IF);
		return IF;}
	else {columns+=yyleng;
		yylval.line=yylineno;
		insert_end(list,"else",ELSE);
		return ELSE;}
	var {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"var",VAR);
		return VAR;}
	func {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"func",FUNC);
		return FUNC;}
	arg {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"arg",ARG);
		return ARG;}
	while {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"while",WHILE);
		return WHILE;}
	switch {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"switch",SWITCH);
		return SWITCH;}
	case {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"case",CASE);
		return CASE;}
	for {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"for",FOR);
		return FOR;}
	return {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"return",RETURN);
		return RETURN;}
	default {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"default",DEFAULT);
		return DEFAULT;}
	break {columns+=yyleng;
		 yylval.line=yylineno;
		 insert_end(list,"break",BREAK);
		return BREAK;}

	{id} {
		columns+=yyleng;
		yylval.sval=(char*)realloc(yylval.sval,yyleng*sizeof(char));
		strcpy(yylval.sval,yytext);
		yylval.line=yylineno;
		insert_end(list,yytext,ID);
		return ID;}

	{car} {
		columns+=yyleng;
		yylval.cval=yytext[1];
		yylval.line=yylineno;
			return CARACTERES;}

	":"	{
		columns++;
		yylval.line=yylineno;
		return DPUN;}
	";"	{
		columns++;
		yylval.line=yylineno;
		return PCOM;}
	","	{
		columns++;
		yylval.line=yylineno;
		return COMA;}
	"("	{
		columns++;
		yylval.line=yylineno;
		return PAR_AB;}
	")"	{
		columns++;
		yylval.line=yylineno;
		return PAR_CI;}
	"{"	{
		columns++;
		yylval.line=yylineno;
		return LLA_AB;}
	"="	{
		columns++;
		yylval.line=yylineno;
		return IGUAL;}

	"}"	{
		columns++;
		yylval.line=yylineno;
		return DPUN;}

	"+"	{
		columns++;
		yylval.line=yylineno;
		return MAS;}

	"-"	{
		columns++;
		yylval.line=yylineno;
		return MENOS;}

	"*"	{
		columns++;
		yylval.line=yylineno;
		return POR;}
	"/"	{
		columns++;
		yylval.line=yylineno;
		return DIV;}

	"%"	{
		columns++;
		yylval.line=yylineno;
		return MOD;}

	"++" {
		columns++;
		yylval.line=yylineno;
		return DMAS;}
	"--" {
		columns++;
		yylval.line=yylineno;
		return DMENOS;}

	">" {
		columns++;
		yylval.line=yylineno;
		return PIC_CI;}
	"<" {
		columns++;
		yylval.line=yylineno;
		return PIC_AB;}
	">=" {
		columns++;
		yylval.line=yylineno;
		return MAY_IG;}
	"<=" {
		columns++;
		yylval.line=yylineno;
		return MEN_IG;}
	"==" {
		columns++;
		yylval.line=yylineno;
		return DOB_IG;}
	"<>" {
		columns++;
		yylval.line=yylineno;
		return DIF;}
	"&&" {
		columns++;
		yylval.line=yylineno;
		return _AND;}
	"||" {
		columns++;
		yylval.line=yylineno;
		return _OR;}
	"!" {
		columns++;
		yylval.line=yylineno;
		return _NOT;}

	{ent}	{columns++;
			yylval.ival=atoi(yytext);
			yylval.line=yylineno;
			return ENTEROS;}
	{real}	{
			columns++;
			yylval.fval=atof(yytext);
			yylval.line=yylineno;
			return FLOTANTES;}

	"<--"	{BEGIN comentario;
			comment=1;}
	[ \t]	{columns++;}
	"\n"	{columns=0;}
}
<comentario>
	{"-->" {comment=0;
			BEGIN INITIAL;}
	(.|'\n')*	{}
}

.	{error("Error léxico.");}

%%

int yywrap()
{
	return 1;
}


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
	if (tmp == NULL)
		exit(-1);
	printf("Tabla de indices:\n");
	while(tmp != NULL)
	{
		printf("<%s, \t%d>\n",tmp->tupla.str, tmp->tupla.token);
		tmp = tmp->next;
	}
}

//void error(char* msg, char* yytxt,int ychar,int ycolumn)
void error(char* msg)
{
	printf("%s\n",msg);
	printf("%d\n", columns);
	//exit(-1);
}


