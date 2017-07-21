%{
    #include <ctype.h>
    int i = 0;
    char str[100];
%}

%token id
%left '+' '-' '*' '/'

%%

E : S {infix_postfix(str);}
S : S '+' T| S '-' T |T
T : T '*' F| T '/' F |F
F : id | '(' S ')'

%%


#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Enter an Expression : ");
    yyparse();
    return 0;
}

yyerror(){
    printf("Invalid Expression\n");
    exit(1);
}

yylex(){
    char ch = ' ';
    while (ch != '\n'){
        ch = getchar();
        str[i++] = ch;
        if (isalpha(ch)){
            return id;
        }
        else if (ch == '+' | ch == '-'|ch == '*'| ch == '/'| ch == '('|ch == ')'){
            return ch;
        }
    }
    str[--i] = '\0';
    return 0;
}

void push(char *stk, int *top, char ch){
    stk[++(*top)] = ch;
}

char pop(char *stk, int *top){
    return stk[(*top)--];
}

int precedence(char ch){
    switch(ch){
        case '+':case '-': return 1;
        case '*':case '/': return 2; 
        case '(': return 0;
        default: return -1;
    }
}

void infix_postfix(char *infix){
    
    char cursymb, stksymb, postfix[100], stack[100];
    int top = -1, iptr = -1, pptr = -1;

    push(stack, &top, '\0');

    while ((cursymb = infix[++iptr]) != '\0'){
        switch (cursymb){
            case '(' : push(stack, &top, cursymb);
                       break;
            case ')' : stksymb = pop(stack, &top);
                       while (stksymb != '('){
                           postfix[++pptr] = stksymb;
                           stksymb = pop(stack, &top);
                       }
                       break;
            case '+':
            case '-':
            case '*':
            case '/':while (precedence(stack[top]) > precedence(cursymb)){
                            postfix[++pptr] = pop(stack, &top);
                      }
                      push(stack, &top, cursymb);
                      break;
            default : if (isalnum(cursymb) == 0){
                            printf("Error\n");
                            exit(0);
                     }
                     postfix[++pptr] = cursymb;
        }
    }
    while (top != -1){
        postfix[++pptr] = pop(stack, &top);
    }
    printf("Postfix Expression = %s\n", postfix);
}
