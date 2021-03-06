#include<stdlib.h>

typedef enum token_type { elsesym  =  1,  identsym  =  2,  numbersym  =  3,  plussym  =  4,  minussym  =  5,  multsym  =  6,  
slashsym = 7, modsym = 8,  eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, 
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, 
semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym 
= 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, 
procsym = 30, writesym = 31, readsym = 32 } token_type;

typedef struct lexeme{
    token_type type;
    char name[12];
    int value;
    int error_type;
}lexeme;

int main()
{
    enum token_type token = elsesym;

    
    printf("Hello World: ");
    printf("%d",token);

    return 0;
}
