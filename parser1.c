/*
	parser1.c
	Analizador Sintáctico

	Olivares Castillo José Luis
	Pérez Escorza Iván

	23/Abril/2016

*/



//Librerías necesarias para ejecutar el parser.
#include "Producciones.h"
#include "token.h"
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
//Variables globales
extern List* list;
extern FILE *yyin;
extern int yylex(void);
int token;
extern YYSTYPE yylval;
//int pos;


void eat(int tok)		
{/*función que va leyendo los tokens de la entrada, en caso de ser inválido, envía error*/
	if (token==tok)
		token=yylex();
	else
		error("SYNTAX ERROR");//SYNTAX ERROR
}

//Funciones según el diagrama de sintáxis//

void D()
{
	if(token==VAR)
	{
		eat(VAR);
		eat(LLA_AB);
		C();
		eat(LLA_CI);
		DP();
	}	
	//else if(token==INT ||FLOAT||CHAR||VAR){
	else
	{
		if(token==INT||token==FLOAT||token==CHAR)
		{
			T();
			L();
			eat(PCOM);
			DP();
		}
		else
			error("SYNTAX ERROR");
	}
	
}

void R()
{
	F();
	RP();
}
void P()
{
	D();
	R();
}
void F()
{
	eat(FUNC);
	T();
	eat(ID);
	eat(ARG);
	eat(PAR_AB);
	G();
	eat(PAR_CI);
	eat(LLA_AB);
	B();
	eat(LLA_CI);
}

void RP()
{
	while(token==FUNC)
	F();
}
void C()
{
	T();
	L();
	eat(PCOM);
	CP();
}
void CP()
{
	if(token==INT||token==FLOAT||token==CHAR)
	{
		T();
		L();
		C();
	}
}

void DP()
{
	while(token==VAR)
	{
		eat(VAR);
		T();
		L();
		eat(PCOM);
	}
}

void L()
{
	I();
	LP();
}
void LP()
{
	if(token==COMA)
	{
		eat(COMA);
		L();
	}
}
void I()
{
	eat(ID);
	IP();
}

void IP()
{
	if (token==IGUAL)
	{
		eat(IGUAL);
		V();
	}
}
void V()
{
	switch(token)
	{
		case ENTEROS:
			eat(ENTEROS);
			break;
		case FLOTANTES:
			eat(FLOTANTES);
			break;
		case CARACTERES:
			eat(CARACTERES);
			break;
		case ID:
			eat(ID);
			break;
		default:
			error("SYNTAX ERROR");
	}
}
void T()
{
	switch(token)
	{
		case INT:
			eat(INT);
			break;
		case FLOAT:
			eat(FLOAT);
			break;
		case CHAR:
			eat(CHAR);
			break;
		default:
			error("SYNTAX ERROR");
	}
}
void G()
{////***********************
	T();
	eat(ID);
	GP();
}
void GP()
{
	while(token==ID)
	{
		eat(ID);
		T();
		eat(COMA);
	}
}

void X()
{
	eat(WHILE); //WHILE
	eat(PAR_AB);
	U();
	eat(PAR_CI);
	eat(LLA_AB);
	B();
	eat(LLA_CI);
}

void M()
{
	eat(FOR);
	eat(PAR_AB);
	eat(ID);/////////////////
	A();
	eat(PCOM);
	U();
	eat(PCOM);
	O();
	eat(PAR_CI);
	eat(LLA_AB);
	B();
	eat(LLA_CI);
}

void Z()
{
	eat(IF);
	eat(PAR_AB);
	U();
	eat(PAR_CI);
	eat(LLA_AB);
	B();
	eat(LLA_CI);
	ZP();
}
void ZP()
{//epsilon
	if (token==ELSE)
	{
		eat(ELSE);
		eat(LLA_AB);
		B();
		eat(LLA_CI);
	}
}

void S()
{
	eat(SWITCH);
	eat(PAR_AB);
	eat(ID);
	eat(PAR_CI);
	eat(LLA_AB);
	N();
	eat(LLA_CI);
}

void N()
{
	switch(token)
	{
		case CASE:
			eat(CASE);
			V();
			eat(DPUN);
			B();
			Q();
			N();
			break;
		case DEFAULT:
			eat(DEFAULT);
			eat(DPUN);
			B();
			Q();
			break;
		default:
			error("SYNTAX ERROR");
	}
}

void E()
{
	E1();
	E2();
}
void E1()
{
	E3();
	E4();
}
void E2()
{
	while(token== MAS || token== MENOS)
	{
		if(token==MAS)
		{
			eat(MAS);
			E1();
		}
		else
		{
			eat(MENOS);
			E1();
		}
	}
}
void E3()
{
	switch(token)
	{
		case PAR_AB:
			eat(PAR_AB);
			E();
			eat(PAR_CI);
			break;
		case ID:
			eat(ID);
			E3P();
			break;
		case CARACTERES:
			eat(CARACTERES);
			break;
		default:
			error("SYNTAX ERROR");
	}
	/*if (toke==ID)/////////////////////////
		A();///////////////////////////////
		*/
}
void E3P()
{
	A();
}
void E4()
{
	while(token==POR||token==DIV||token==MOD)
	{
		switch(token)
		{
			case POR:
				eat(POR);
				E3();
				break;
			case DIV:
				eat(DIV);
				E3();
				break;
			case MOD:
				eat(MOD);
				E3();
				break;
			defaul:
				error("SYNTAX ERROR");
		}		
	}
}

void J()
{
	K();
	JP();
}

void JP()
{
	while(token==WHILE || token==FOR ||token==PAR_AB||token==ID
		||token==CARACTERES||token==IF||token==SWITCH)
	{
		K();
	}
}

void B()
{
	if(token==INT || token==FLOAT || token==CHAR|| token==VAR)
	{
		D();
		J();
	}
	else 
	{
		if (token==WHILE || token==FOR || token==PAR_AB ||
		token==ID || token==CARACTERES || token==IF || token==SWITCH)
			J();
		else
		 	error("SYNTAX ERROR");
	}
		
}
void K()
{
	switch(token)
	{
		case WHILE:
			X();
			break;
		case FOR:
			M();
			break;
		case PAR_AB:
			E();
			break;
		case ID:
			E();
			break;
		case CARACTERES:
			E();
			break;
		case IF:
			Z();
			break;
		case SWITCH:
			S();
			break;
		default:
			error("SYNTAX ERROR");
	}
	/*
	//if(token== || token==)//X
		X();
	else if(token==)//M
		M();
		else if(token==PAR_AB || token==ID || token== CARACTERES)//E
			E();
			else if(token==ELSE)//Z
				Z();
			else if(token==)//S
	if (token==WHILE)
	{
		X();
	}
	else
	{
		if (token==FOR)
		{
			M();
		}
		else
		{
			if (token==PAR_AB||token==ID||token==CARACTERES)
			{
				E();
			}
			else
			{
				if (token==IF)
				{
					Z();
				}
				else
				{
					if (token==SWITCH)
					{
						S();
					}
					else
					{
						error("SYNTAX ERROR");
					}
				}
			}
		}
	}
	*/
}

void A()
{
	//eat(ID);////////////
	eat(IGUAL);
	E();
}


void OP()
{
	switch(token)
	{
		case DMAS:
			eat(DMAS);
			break;
		case DMENOS:
			eat(DMENOS);
			break;
		default:
			error("SYNTAX ERROR");
	}
}
void O()
{
	eat(ID);
	OP();
}
void Q()
{
	if(token==PAR_AB || token==ID || token== CARACTERES)
	{
		E();
		eat(PCOM);
	}
	else 
	{
		if(token==RETURN)
		{
			eat(RETURN);
			eat(PCOM);
		}
		else
		{
			if(token==BREAK)
			{
				eat(BREAK);
				eat(PCOM);
			}
		}
	}
}

void U()
{
	U1();
	U5();
}
void U1()
{
	U2();
	U6();
}
void U2()
{
	U3();
	U7();
}
void U3()
{
	U4();
	U8();
}
void U4()
{
	if(token==_NOT)
	{
		eat(_NOT);
		U4();
	}
	else
	{
		if(token==PAR_AB || token==ID || token== CARACTERES)
			E();
		else
			error("SYNTAX ERROR");
	} 
}
void U5()
{
	while(token=_OR)
	{
		eat(_OR);
		U1();
	}
}
void U6()
{
	while(token==_AND)
	{
		eat(_AND);
		U2();
	}
}

void U7()
{
	while(token== DIF || token==DOB_IG)
	{
		if(token==DIF)
		{
			eat(DIF);
			U3();
		}
		else
		{
			if (token==DOB_IG)
			{
				eat(DOB_IG);
				U3();
			}
		}
	}
}
void U8()
{
	while(token==PIC_AB||token==MEN_IG||token==PIC_CI||token==MAY_IG)
	{
		switch(token)
		{
			case PIC_AB:
				eat(PIC_AB);
				U4();
				break;
			case MEN_IG:
				eat(MEN_IG);
				U4();
				break;
			case PIC_CI:
				eat(PIC_CI);
				U4();
				break;
			case MAY_IG:
				eat(MAY_IG);
				U4();
				break;
			default:
				error("SYNTAX ERROR");
		}
	}
}

void init()
{//Inicializa la tabla de símbolos.
	list=(List*)malloc(sizeof(List));
}

int main(int argc, char** argv)
{
	system("clear");
	//abrir archivo...
	if (argc > 1)
	{
		FILE *file = fopen(argv[1],"r");
		if (!file)
		{
			perror("No se pudo abrir archivo");
			exit(1);
		}
		else
		{
			yyin = file;
			//yyout = fopen("output.dat","w");
			init();		

			token = yylex();
			
			P();		//Símbolo inicial
			print(list);
			fclose(yyin);
			//fclose(yyout);
		}
	}
	else
		printf("No se ingreso archivo.\n");
	return 0;
}