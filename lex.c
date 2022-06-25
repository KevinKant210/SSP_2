// Caitlin Fabian and Kevin Kant
// Hw2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LEXEME_LENGTH 500
#define false 0
#define true 1
#define iscomment -1

typedef enum error_type{
    none = -2, no_letter_on_start = -3,long_number = -4, invalid_symbol = -5, comment_error = -6,too_long_identifier = -7 } error_type;


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



int isValidNextSym(char c){
    if(isspace(c) || isalpha(c) || isdigit(c) || c == EOF){
        return true;
    }else{
        return false;
    }
}

int isSpecialSymbol(char c,char next,lexeme* token){

    if(c == '+'){
        if(isValidNextSym(next) == true){
            token->name[0] = '+';
            
            return plussym;
        }
    }

    
    if(c == '-'){

        if(isValidNextSym(next) == true){
            token->name[0] = '-';
            return minussym;
        }
    }
    

    

    if(c == '*'){
        if(isValidNextSym(next) == true){
            token->name[0] = '*';
            return multsym;
        }
    }

    if(c == '/'){
        if(next == '*'){
            return iscomment;
        }else if(isValidNextSym(next) == true){
            token->name[0] = '/';
            return slashsym;
        }

    }

    if(c == '%'){
        if(isValidNextSym(next) == true){
            token->name[0] = '%';
            return modsym;
        }
    }

    if(c == '='){
        if(isValidNextSym(next) == true){
            token->name[0] = '=';
            return eqlsym;
        }
    }

    

    if(c == '!'){
        if(next == '='){
            token->name[0] = '!';
            token->name[1] = '=';
            return neqsym;
        }
        
    }

    

    if(c == '<'){
        if(next == '='){
            token->name[0] = '<';
            token->name[1] = '=';
            return leqsym;
            
        }if(isValidNextSym(next) == true){
            token->name[0] = '<';
            return lessym;
        }
        
    }

    if(c == '>'){
        if(next == '='){
            token->name[0] = '>';
            token->name[1] = '=';
            return geqsym;
        }else if(isValidNextSym(next) == true){
            token->name[0] = '>';
            return gtrsym;
        }
    }


    if(c == '('){
        if(isValidNextSym(next) == true){
            token->name[0] = '(';
            return lparentsym;
        }
    }

    if(c == ')'){
        if(isValidNextSym(next) == true){
            token->name[0] = ')';
            return rparentsym;
        }
    }

    if(c == ','){
        if(isValidNextSym(next) == true){
            token->name[0] = ',';
            return commasym;
        }
    }

    if(c == ';'){
        if(isValidNextSym(next) == true){
            token->name[0] = ';';
            return semicolonsym;
        }
    }

    if(c == '.'){
        if(isValidNextSym(next) == true){
            token->name[0] = '.';
            return periodsym;
        }
    }

    if(c == ':'){
        if(next == '='){
            token->name[0] = ':';
            token->name[1] = '=';
            return becomessym;
        }
    }

    return invalid_symbol;

    
}

void printName(lexeme token){
    for(int i = 0 ; i < strlen(token.name); i++){
        if(isspace(token.name[i]) == false ){
            printf("%c",token.name[i]);
        }
        
        
    }
}


int main(int argc, char* argv[]){

    lexeme* tokenTable = (lexeme*) malloc(sizeof(lexeme)*MAX_LEXEME_LENGTH);

    FILE *fp;
    fp = fopen(argv[1], "r");

    
    int halt = false;
    int tokenCounter = 0;
    while(halt == false){

        //printf("in Main\n");
        char c,next;

        lexeme newLex;

        for(int i = 0; i < 12; i++){
            newLex.name[i] = 0;
        }
        newLex.error_type = none;
        newLex.type = 0;
        c = fgetc(fp);
        //we will fetch next and put it back if we dont use it
        

        //int i = 0;
        if(c == EOF){
            halt = true;
        }else if(isspace(c)){   
            continue;
        }else if(isalpha(c)){
           // printf("in Alpha\n");
            //is an identifier or a reserved word
            newLex.name[0] = c;
            int i = 1;


            int alphaHalt = false;
            while(alphaHalt == false){
                
                c = fgetc(fp);

                if(newLex.error_type != none){
                    //error so we keep reading until symbol or whitespace
                    if(isalpha(c) != false || isdigit(c) != false){
                        //do nothing
                    }else{
                        //ran into symbol or blank character so put it back for the main to handle
                        ungetc(c,fp);
                        alphaHalt = true;
                    }
                
                }else if(isalpha(c) != false || isdigit(c) != false){
                    //case where our substring hasnt ended
                    if(i == 11){
                        //we have a too long identifier
                        newLex.error_type = too_long_identifier;
                    }else{
                        newLex.name[i] = c;
                        i++;
                    }
                }else{
                    //isnt a letter or digit so must be a symbol or a space
                    
                    ungetc(c,fp);

                    //finalize and store token
                    if(strcmp(newLex.name,"else") == 0){
                        newLex.type = elsesym;
                    }else if(strcmp(newLex.name,"begin") == 0){
                        newLex.type = beginsym;
                    }else if(strcmp(newLex.name,"end") == 0){
                        newLex.type = endsym;
                    }else if(strcmp(newLex.name,"if") == 0){
                        newLex.type = ifsym;
                    }else if(strcmp(newLex.name,"then") == 0){
                        newLex.type = thensym;
                    }else if(strcmp(newLex.name,"while") == 0){
                        newLex.type = whilesym;
                    }else if(strcmp(newLex.name,"do") == 0){
                        newLex.type = dosym;
                    }else if(strcmp(newLex.name,"call") == 0){
                        newLex.type = callsym;
                    }else if(strcmp(newLex.name,"const") == 0){
                        newLex.type = constsym;
                    }else if(strcmp(newLex.name,"var") == 0){
                        newLex.type = varsym;
                    }else if(strcmp(newLex.name,"procedure") == 0){
                        newLex.type = procsym;
                    }else{
                        newLex.type = identsym;
                    }
                    alphaHalt = true;
                }

                


            }


        }else if(isdigit(c)){
            //must be a number
            printf("in digit \n");
            int i = 0;

            newLex.name[i];
            i++;
            
            int numHalt = false;

            while(numHalt == false){
                c = fgetc(fp);

                if(newLex.error_type != none){
                    //we ran into an error at some point so read until we get to a new symbol or blankspace
                    if(isalpha(c) == false && isdigit(c) == false){
                        ungetc(c,fp);
                        numHalt = true;
                    }

                }else if(isdigit(c)){
                    if(i == 4){
                        //this means we already have five numbers in our array
                        

                        newLex.error_type = long_number;

                    }else{
                        newLex.name[i] = c;
                        i++;
                    }
                }else if(isspace(c)){
                    //end of substring so we move on
                    
                    numHalt = true;

                    //building the lex
                    newLex.type = numbersym;

                    //stuff to convert from value to number
                    /*
                    //do this to convert the character array to a value
                    char* tempArray = (char*) malloc(sizeof(char)*(i+1));
                    for(int j = 0 ; j < i; j++){
                        tempArray[j] = newLex.name[j];
                    }
                    //store the value
                    newLex.value = atoi(tempArray);
                    
                    free(tempArray);
                    */

                }else if(isalpha(c)){
                    //is a letter so we run into an error

                    //run through the invalid comment
                   

                    newLex.error_type = no_letter_on_start;
                    
                }else{
                    //must be some kind of symbol so we put it back and end this DFA
                    ungetc(c,fp);
                    numHalt = true;
                }
            }
            

        }else{
            //we ran into a symbol
            //printf("in symbol\n");
            next = fgetc(fp);

            int output = isSpecialSymbol(c,next,&newLex);

            if(output < 0){
                //then error must have occured or we ran into a comment
                if(output = iscomment){

                    int commentHalt = false;

                    while(commentHalt == false){
                        char temp = fgetc(fp);

                        if(temp == EOF){
                            newLex.error_type = comment_error;
                            commentHalt = true;
                        }else if(temp == '*'){
                            temp = fgetc(fp);
                            if(temp == '/'){
                                commentHalt = true;
                            }
                        }

                    }
                }

                newLex.error_type = output;
            }else{
                if(output == neqsym || output == leqsym || output == geqsym || output == becomessym){
                    
                }else{
                    ungetc(next,fp);
                }

                newLex.type = output;
            }
            }


            tokenTable[tokenCounter] = newLex;

            tokenCounter++;


        }

        
    
    //we can close the filepointer we are no longer reading
    fclose(fp);

    //we now print out lex table output
        for(int i = 0; i < tokenCounter; i++){

            
            if(tokenTable[i].error_type != none){
                printf("Error: %d\n",tokenTable[i].error_type);
            }else{
                if(tokenTable[i].type == 0){
                    //this must be some whitespace or EOF that slipped through the cracks

                }else if(tokenTable[i].type == identsym){
                    //print an identifier
                    
                    printf("%d ", tokenTable[i].type);
                    printName(tokenTable[i]);
                }else if(tokenTable[i].type == numbersym){
                    //print a number
                    printf("Number!");
                    printName(tokenTable[i]);
                    printf("%d %d",tokenTable[i].value, tokenTable[i].type);
                }else{
                    //reserved word or a symbol
                    //printName(tokenTable[i]);
                    printf(" %d",tokenTable[i].type);
                }
                
                printf(" ");
            }
        }

        free(tokenTable);
    }

    