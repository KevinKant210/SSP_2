// Caitlin Fabian and Kevin Kant
// Hw2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LEXEME_LENGTH 500
#define false 0;
#define true 1;
#define iscomment -1;

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
    if(isspace(c) || isalpha(c) || isdigit(c)){
        return true;
    }else{
        return false;
    }
}

int isSpecialSymbol(char c,char next){

    if(c == '+'){
        if(isValidNextSym(next) == true){
            return plussym;
        }
    }

    
    if(c == '-'){

        if(isValidNextSym(next) == true){
            return minussym;
        }
    }
    

    

    if(c == '*'){
        if(isValidNextSym(next) == true){
            return multsym;
        }
    }

    if(c == '/'){
        if(next == '*'){
            return iscomment;
        }else if(isValidNextSym(next) == true){
            return slashsym;
        }

    }

    if(c == '%'){
        if(isValidNextSym(next) == true){
            return modsym;
        }
    }

    if(c == '='){
        if(isValidNextSym(next) == true){
            return eqlsym;
        }
    }

    

    if(c == '!'){
        if(next == '='){
            return neqsym;
        }
        
    }

    

    if(c == '<'){
        if(next == '='){
            return leqsym;
        }if(isValidNextSym(next) == true){
            return lessym;
        }
        
    }

    if(c == '>'){
        if(next == '='){
            return geqsym;
        }else if(isValidNextSym(next) == true){
            return gtrsym;
        }
    }


    if(c == '('){
        if(isValidNextSym(next) == true){
            return lparentsym;
        }
    }

    if(c == ')'){
        if(isValidNextSym(next) == true){
            return rparentsym;
        }
    }

    if(c == ','){
        if(isValidNextSym(next) == true){
            return commasym;
        }
    }

    if(c == ';'){
        if(isValidNextSym(next) == true){
            return semicolonsym;
        }
    }

    if(c == '.'){
        if(isValidNextSym(next) == true){
            return periodsym;
        }
    }

    if(c == ':'){
        if(next == '='){
            return becomessym
        }
    }

    return invalid_symbol;

    
}




int main(int argc, char* argv[]){

    lexeme* tokenTable = (lexeme*) malloc(sizeof(lexeme)*MAX_LEXEME_LENGTH);

    FILE *fp;
    fp = fopen(argv[1], "r");

    
    int halt = false;
    int tokenCounter = 0;
    while(halt == false){
        char c,next;

        lexeme newLex;
        newLex.error_type = none;

        c = fgetc(fp);
        //we will fetch next and put it back if we dont use it
        

        //int i = 0;
        if(c == EOF){
            halt = true;
        }else if(isspace(c)){   
            continue;
        }else if(isalpha(c)){
            //is an identifier or a reserved word
            newLex.name[0] = c;
            int i = 1;


            int alphaHalt = false;
            while(alphaHalt == false){
                c = fgetc(fp)

                if(newLex.error_type != none){
                    //error so we keep reading until symbol or whitespace
                    if(isalpha(c) == true || isdigit(c) == true){
                        //do nothing
                    }else{
                        //ran into symbol or blank character so put it back for the main to handle
                        ungetc(c,fp);
                        alphaHalt = true;
                    }
                
                }else if(isalpha(c) || isdigit(c)){
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
                }


            }


        }else if(isdigit(c)){
            //must be a number
            
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
                        number[i] = c;
                        i++;
                    }
                }else if(isspace(c)){
                    //end of substring so we move on
                    
                    numHalt = true

                    //building the lex
                    newLex.type = numbersym;
                    
                    //do this to convert the character array to a value
                    char* tempArray = (char*) malloc(sizeof(char)*(i+1));
                    for(int j = 0 ; j < i; j++){
                        tempArray[j] = newLex.name;
                    }
                    //store the value
                    newLex.value = atoi(tempArray[j]);
                    
                    free(tempArray);

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
                next = fgetc(fp);

            int output = isSpecialSymbol(c,next);

            if(output < 0){
                //then error must have occured or we ran into a comment
                if(output = iscomment){

                    int commentHalt = false;

                    while(commentHalt == false){
                        char temp = fgetc(fp);

                        if(temp == '*'){
                            temp = fgetc(fp);
                            if(temp == '/'){
                                commentHalt = true
                            }
                        }

                        if(temp == EOF){
                            newLex.error_type = comment_error;
                            commentHalt = true;
                        }

                    }
                }

                newLex.error_type = output;
            }else{
                if(output == neqsym || output == leqsym || output == geqsym || output == becomessym){

                }else{
                    ungetc(next,fp);
                }
            }
            }


            tokenTable[tokenCounter] = newLex;

            tokenCounter++;


        }

        
    
    //we can close the filepointer we are no longer reading
    fclose(fp);

    //we now print out lex table output

    }

    