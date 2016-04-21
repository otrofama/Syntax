//PARSER
#include <token.h>
#include <stdio.h>
#include <stdlib.h>
extern LIST* symbols


int token;


void error()
{
	printf("SYNTAX ERROR\n");
}
void eat(int tok)
{
	if (token==tok)
		token=yylex();
	else
		error();//SYNTAX ERROR
}


//Segun diagramas de sintaxis
void P()
{
	D();
	R();
}

void R()
{
	F();
	RP();
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
		T();
}

void D()
{
	
}
void K()
{

}

void DP()
{
	while(token==var)
	{
		eat(var);
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

void I()
{
	eat(ID);
	IP();
}
void V()
{
	switch(token)
	{
		case NUM:
			eat(NUM);
			break;
		case CARACTERES:
			eat(CARACTERES);
			break;
		case ID:
			eat(ID);
			break;
		default:
			error();
	}
}

void IP()
{
	if (token==IGUAL)
	{
		eat(IGUAL);
		V();
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
			error();
	}
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
	eat(while);
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
	eat(id);
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
	eat(ELSE);
	eat(LLA_AB);
	B();
	eat(LLA_CI);
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
			eat(PCOM);
			B();
			Q();
			N();
			break;
		case DEFAULT:
			eat(DEFAULT);
			eat(PCOM);
			B();
			Q();
			break;
		default:
			error();
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

}

void E3P()
{
	A();
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
		//falta case A();
	}
}
void E4()
{

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

}

void A()
{
	eat(IGUAL);
	E();
}

void O()
{
	eat(ID);
	OP();
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
			error();
	}
}

void Q()
{

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
	switch(token)
	{
		case _NOT:
			eat(_NOT);
			U4();
			break;
		case //E:
	}
}
void U5()
{
	while(token==_OR)
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

}
void U8()
{

}

void init()
{
	symbols=(LIST*)malloc(sizeof(LIST));
	//insertar simbolos
}

int main(int argc, char** argv)
{
	//abrir archivo...
	if (argc > 1)
	{
		FILE *file = fopen(argv[1],"r");
		if (!file);
		{
			perror("No se pudo abrir archivo");
			exit(1);
		}
		else
		{
			yyin = file;
			yyout = fopen("output.dat","w");
			
			token = yylex();
			init();		
			P();		//Símbolo inicial
			
			fclose(yyin);
			fclose(yyout);
		}
	}
	else
		printf("No se ingreso archivo.\n");
	/*token=yylex();
	init();
	P();		//simbolo inicial..
	*/
	return 0;
}