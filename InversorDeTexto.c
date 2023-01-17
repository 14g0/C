/*
    O programa, como já diz o nome, inverte todo o texto de um arquivo de texto.
*/


#include <stdio.h>
#include <stdlib.h>

void fixStr(char *string);
void inverteStr(char *string);

int main(void) {

    FILE *inp, *out;
    int cont, tam=1;
    char letra=0, ninp[20], nout[20], **inverter;

    printf("Insira o nome do arquivo de input:\n>");
    fgets(ninp, 20, stdin);
    printf("Insira o nome do arquivo de output:\n>");
    fgets(nout, 20, stdin);
    
    fixStr(ninp); fixStr(nout);

    inp = fopen(ninp, "r");
    out = fopen(nout, "w");

    if(inp==NULL) printf("Não foi possível abrir o arquivo.\n");
    if(out==NULL) printf("Não foi possível abrir o arquivo.\n");

/*-------------------------------------------------------------------------------*/
    
    fseek(inp, 0, SEEK_SET);
    for(cont=0 ; letra!=EOF ; cont+=1) {
        letra = fgetc(inp);
        if(letra=='\n') tam+=1;
    }
    printf("%d", tam);

/*-------------------------------------------------------------------------------*/

    inverter = (char **)malloc(50*tam*sizeof(char));

    fseek(inp, 0, SEEK_SET);
    for(cont=0 ; cont<tam; cont+=1) {
        inverter[cont] = (char *)malloc(50*sizeof(char));
        fgets(inverter[cont], 50, inp);
        inverteStr(inverter[cont]);
    }
    for(cont=tam-1 ; cont>=0 ; cont-=1) {
        fputs(inverter[cont], out);
    }


    return 0;

}

void fixStr(char *string) {
    int cont=1;
    while(string[cont]!='\n') {
        cont+=1;
    }

    string[cont] = '\0';
}

void inverteStr(char *string) {
    char troca;
    int cont=0, cont2;

    while(string[cont]!='\0') {
        cont+=1;
    }

    for(cont2=0 ; cont2<=(cont/2)-1 ; cont2+=1) {
        troca = string[cont2];
        string[cont2] = string[cont-1-cont2];
        string[cont-1-cont2] = troca;
    }
}