#include <stdio.h>


int tamStr (char *string);

int main(int argc, char *argv[]) {

    FILE *input;
    char *trecho, comp=0;
    int cont=0, contn=1, iniciodalinha;

    if((input = fopen(argv[2], "r"))==NULL) printf("Não foi possível abrir o arquivo.\n");

    trecho = argv[1];

    fseek(input, 0, SEEK_SET);
    iniciodalinha = ftell(input);
    
    while(comp!=EOF) {
        comp=fgetc(input); /*string de comparação recebe o char de ponteiro*/

        while(comp==trecho[cont]) {

            if(comp==trecho[cont] && cont==tamStr(trecho)-1){
                printf("%d ", contn);
                fseek(input, iniciodalinha, SEEK_SET);
                comp = fgetc(input);

                while(comp!='\n' && comp!=EOF) {
                    printf("%c", comp);
                    comp = fgetc(input);
                }
                puts("");
                fseek(input, -1, SEEK_CUR);
            }
            cont+=1;
            comp = fgetc(input);
        }
        cont = 0;

        if(comp=='\n') {
            iniciodalinha = ftell(input);
            contn +=1;
        }
    }

    return 0;
}

/*----------------------------------------------------------------------*/


int tamStr (char *string) {
    int cont=0;
    while(string[cont]!='\0') {
        cont+=1;
    }

    return cont;
}
