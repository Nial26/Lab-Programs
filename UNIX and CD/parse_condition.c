#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_condition(char *stmt, char *dest, int *counter){
    int begin, i, k=0;

    while (stmt[++(*counter)] != '('); //Move untill the first open braces

    begin = *counter + 1;

    while (stmt[++(*counter)] != ')'); //Move untill the closing brace

    for (i = begin; i < *counter; i++){
        dest[k++] = stmt[i];
    }
    dest[k++] = '\0';
}

void gen(char *condition, char *ifpart, char *elsepart, int elseflag){
    printf("99: IF ! %s GOTO 101\n",condition);
    printf("100: %s\n", ifpart);
    
    if (elseflag){
        printf("101: %s\n", elsepart);
        printf("102: \n");
    }
    else{
        printf("101: \n");
    }
}

int main(){
    char stmt[100], condition[100], ifpart[100], elsepart[100];
    int counter = 0, stlen, begin, i;

    printf("Enter Expression: ");
    gets(stmt);

    stlen = strlen(stmt);

    counter += 2; //Skip the if

    parse_condition(stmt, condition, &counter);

    while (stmt[++counter] != 't'); // Skip the spaces

    counter += 3; //Skip the 'then'

    parse_condition(stmt, ifpart, &counter);
    
    if (stmt[++counter] == ';'){
        gen(condition, ifpart, elsepart, 0);
    }
    
    else{
        counter += 3; //Skip the 'else'
        parse_condition(stmt, elsepart, &counter);
        gen(condition, ifpart, elsepart, 1);
    }

    return 0;
}
