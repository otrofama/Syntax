#define INT			1
#define FLOAT		2
#define CHAR		3
#define VAR 		4
#define FUNC		5
#define ARG			6
#define WHILE		7
#define IF			8
#define ELSE		9
#define SWITCH		10
#define CASE		11
#define FOR			13
#define ID			14
#define ENTEROS		15
#define FLOTANTES	16
#define CARACTERES	17
#define RETURN		18
#define DEFAULT		19
#define BREAK		20
#define DPUN		21 		
#define PCOM		22 		
#define COMA		23 		
#define PAR_AB		24
#define PAR_CI		25 		
#define LLA_AB		26 		
#define LLA_CI		27 		
#define MAS			28 		
#define MENOS		29 		
#define POR			30 		
#define DIV			31 		
#define MOD			32 		
#define PIC_CI		33		
#define PIC_AB		34 		
#define MAY_IG		35 		
#define MEN_IG		36 		
#define DOB_IG		37 		
#define DIF			38 		
#define _AND		39 		
#define _OR			40 		
#define _NOT		41 		
#define DMAS		43 		
#define DMENOS		44 		
#define IGUAL		46 		


typedef union YYSTYPE YYSTYPE;

union YYSTYPE
{
	char* sval;
	float fval;
	int ival;
	char cval;//caracteres
	int line;
	int column;
};

YYSTYPE yylval;

