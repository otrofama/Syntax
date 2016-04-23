%{
#include <stdio.h>
#include "token.h"
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
List* symbols;
/*
lex
*/
int columns;	//variable que cuenta caracteres
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
	int {yylval.line=yylineno;
		return INT;}

	float {	yylval.line=yylineno;
			return FLOAT;}
	char {yylval.line=yylineno;
		return CHAR;}
	if {yylval.line=yylineno;
		return IF;}
	else {yylval.line=yylineno;
		return ELSE;}
	var {yylval.line=yylineno;
		return VAR;}
	func {yylval.line=yylineno;
		return FUNC;}
	arg {yylval.line=yylineno;
		return ARG;}
	while {yylval.line=yylineno;
		return WHILE;}
	switch {yylval.line=yylineno;
		return SWITCH;}
	case {yylval.line=yylineno;
		return CASE;}
	for {yylval.line=yylineno;
		return FOR;}
	return {yylval.line=yylineno;
		return RETURN;}
	default {yylval.line=yylineno;
		return DEFAULT;}
	break {yylval.line=yylineno;
		return BREAK;}

	{id} {
		yylval.sval=(char*)realloc(yylval.sval,yyleng*sizeof(char));
		strcpy(yylval.sval,yytext);
		yylval.line=yylineno;
		/*
		insertar a tabla de símbolos, insert(id,list);
		*/
		return ID;}

	{car} {yylval.cval=yytext[1];
		yylval.line=yylineno;
			return CARACTERES;}

	":"	{
		yylval.line=yylineno;
		return DPUN;}
	";"	{
		yylval.line=yylineno;
		return PCOM;}
	","	{
		yylval.line=yylineno;
		return COMA;}
	"("	{
		yylval.line=yylineno;
		return PAR_AB;}
	")"	{
		yylval.line=yylineno;
		return PAR_CI;}
	"{"	{
		yylval.line=yylineno;
		return LLA_AB;}
	"="	{
		yylval.line=yylineno;
		return IGUAL;}

	"}"	{
		yylval.line=yylineno;
		return DPUN;}

	"+"	{
		yylval.line=yylineno;
		return MAS;}

	"-"	{
		yylval.line=yylineno;
		return MENOS;}

	"*"	{
		yylval.line=yylineno;
		return POR;}
	"/"	{
		yylval.line=yylineno;
		return DIV;}

	"%"	{
		yylval.line=yylineno;
		return MOD;}

	"++" {
		yylval.line=yylineno;
		return DMAS;}
	"--" {
		yylval.line=yylineno;
		return DMENOS;}

	">" {
		yylval.line=yylineno;
		return PIC_CI;}
	"<" {
		yylval.line=yylineno;
		return PIC_AB;}
	">=" {
		yylval.line=yylineno;
		return MAY_IG;}
	"<=" {
		yylval.line=yylineno;
		return MEN_IG;}
	"==" {
		yylval.line=yylineno;
		return DOB_IG;}
	"<>" {
		yylval.line=yylineno;
		return DIF;}
	"&&" {
		yylval.line=yylineno;
		return _AND;}
	"||" {
		yylval.line=yylineno;
		return _OR;}
	"!" {
		yylval.line=yylineno;
		return _NOT;}

	{ent}	{yylval.ival=atoi(yytext);
			yylval.line=yylineno;
			return ENTEROS;}
	{real}	{yylval.fval=atof(yytext);
			yylval.line=yylineno;
			return FLOTANTES;}

	"<--"	{BEGIN comentario;
			comment=1;}
	[ \t\n]	{}
}
<comentario>
	{"-->" {comment=0;
			BEGIN INITIAL;}
	(.|'\n')*	{}
}

.	{printf("error lexico\n");}

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

//void error(char* msg, char* yytxt,int ychar,int ycolumn)
void error()
{
	//printf("%s en: %s, línea: %d, caracter: %d\n",msg,yytext,ycolumn,ychar);
	printf("error\n");
	exit(-1);
}


