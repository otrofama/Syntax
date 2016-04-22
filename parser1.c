//PARSER
#include <token.h>
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
void D()
{
	if(token==var)
	{
		eat(var);
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
			error();
	}
	
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
	}
	if (toke==ID)/////////////////////////
		A();///////////////////////////////
}
void E3P(){
	A();
}
void E4()
{
	switch(token){
		case POR:
			eat(POR);
			E3();
			break;
		case DIV:
			eat(DIV);
			E3();
		case MOD:
			eat(MOD);
			E3();
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
	if(token==INT || token==FLOAT || token==CHAR|| token==VAR){
		D();
		J();
	}
	else if (token==WHILE || token==FOR || token==PAR_AB ||
		token==ID || token==CARACTERES || token==IF || token==SWITCH)
		J();
		 else
		 	error();
}
void K(){
	if(token==/* */ || token==/*  */)//X
		X();
	else if(token==/*  */)//M
		M();
		else if(token==PAR_AB || token==ID || token== CARACTERES)//E
			E();
			else if(token==ELSE)//Z
				Z();
			else if(token==/*  */)//S
}

void A()
{
	eat(ID);////////////
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
	if(token==PAR_AB || token==ID || token== CARACTERES){
		E();
		eat(PCOM);
	}
	else if(token==RETURN){
		eat(RETURN);
		eat(PCOM);
	}
	else if(token==BREAK){
		eat(BREAK);
		eat(PCOM);
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
	if(token==_NOT){
		eat(_NOT);
		U4();
	}
	else if(token==PAR_AB || token==ID || token== CARACTERES)
		E();
	else
		error();
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
	while(token== DIF || token==DOB_IG){
		if(token==DIF){
			eat(DIF);
			U3();
		}
		else
			eat(DOB_IG);
			U3();
	}
}
void U8()
{
	switch(token){
		case PIC_AB:
			eat(PIC_AB);
			E4();
			break;
		case MEN_IG:
			eat(MEN_IG);
			E4();
			break;
		case PIC_CI:
			eat(PIC_CI);
			E4();
			break;
		case MAY_IG:
			eat(MAY_IG);
			E4();
			break;
	}
}

void init()
{
	symbols=(LIST*)malloc(sizeof(LIST));
	//insertar simbolos
}

int main(int argc, char const *argv[])
{
	//abrir archivo...
	token=yylex();
	init();
	P();		//simbolo inicial..
	return 0;
}