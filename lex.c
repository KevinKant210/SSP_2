// Caitlin Fabian and Kevin Kant
// Hw2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEXEME_LENGTH 500

typedef enum token_type { elsesym  =  1,  identsym  =  2,  numbersym  =  3,  plussym  =  4,  minussym  =  5,  multsym  =  6,  
slashsym = 7, modsym = 8,  eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, 
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, 
semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym 
= 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, 
procsym = 30, writesym = 31, readsym = 32 } token_type;

// token.type = modsym == token.type = 8;
// saves us the headache of putting in numbers

typedef struct lexeme{
    token_type type;
    char name[12];
    int value;
    int error_type;
}lexeme;

lexeme table[MAX_LEXEME_LENGTH];

int main(int argc, char* argv[]){

    FILE *fp;
    fp = fopen(argv[1], "r");

    lexeme tempLex;

    int halt = 0;

    while(!halt){
        char c;
        c = fgetc(fp);

        int i = 0;

        while(isalpha(c)){

            tempLex.name[i] = c;
            c = fgetc(fp);
            i++;
        }

        printf("%s", tempLex.name);

        //if()
    
        halt = 1;

    }

    fclose(fp);

return 0;
}