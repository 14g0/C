#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-------------------------------------------------------------*/

/*Struct do Contato*/
typedef struct _contato {
    long int numero;
    char nome[50];
    int dia, mes;
} contato;

/*-------------------------------------------------------------*/

/*Protótipos de função*/
void fixFgets(char *string);
int tamStr (char *string);
char *UpperCase(char *string);
char UpperChar(char carac);

void lerArquivo(FILE *arquivo, contato **vetor);
void escreveArquivo(FILE *arquivo, contato *vetor);

void addCtt(contato **vetor);
void bbsCtts(contato *vetor);
void delCtt(contato **vetor);
void getCtt(contato *vetor);
void printCtts(contato *vetor);
void inicialCtts(contato *vetor);
void niverCtts(contato *vetor);

/*-------------------------------------------------------------*/

/*Variáveis globais*/
long int tamvet=0;  /*tamanho do vetor*/
int cont, cont2;
contato troca;

/*-------------------------------------------------------------*/

int main(void) {

    int option=0;
    char fileName[20];
    contato *agenda = NULL;
    FILE *lista = NULL;
    
    lista = fopen("lista", "r+");
    if(lista == NULL) {
        system("clear || cls");
        puts("\033[31;1;4mVejo que você não possui o arquivo padrão de leitura.\033[m");
        puts("Aperte [ENTER] para prosseguir.");
        getchar();
        do{
            system("clear || cls");
            printf("Caso haja um, insira o nome de um arquivo para leitura, senão aperte [ENTER]:\n>");
            fgets(fileName, sizeof(fileName), stdin);
            lista = fopen(fileName, "w+");
            if((*fileName=='\n') && (lista==NULL)) printf("\033[32mOK, vou criar um arquivo então :)\033[m\n");
            else puts("Arquivo não encontrado.");
        } while((lista==NULL) && (*fileName!='\n'));
    }
    lerArquivo(lista, &agenda);
    fclose(lista);
    bbsCtts(agenda);

    
    do {
        system("clear || cls");
        puts("=*=*=*=*=*=*=*=*=Lista de Contato=*=*=*=*=*=*=*=*=\n");
        puts("1 -> Para adicionar um contato à lista.");
        puts("2 -> Para deletar um contato da lista.");
        puts("3 -> Para pesquisar um contato na lista.");
        puts("4 -> Para mostrar todos os contatos da lista.");
        puts("5 -> Para mostrar todos os contatos de uma inicial.");
        puts("6 -> Para mostrar os aniversariantes de um mês.");
        puts("Digite qualquer outro número para encerrar o programa.");

        printf("Insira sua opção:\n>");
        while(scanf("%d", &option)==0) {
            puts("\033[1;31mOpção inválida, tente novamente.\033[m");
            printf("Insira sua opção:\n>");
            while(getchar()!='\n');
        }

        switch(option) {
            case 1:
                addCtt(&agenda);
                break;

            case 2:
                delCtt(&agenda);
                break;

            case 3:
                getCtt(agenda);
                break;

            case 4:
                printCtts(agenda);
                break;

            case 5:
                inicialCtts(agenda);
                break;

            case 6:
                niverCtts(agenda);
                break;

            default:
                if((lista = fopen("lista", "w"))==NULL) printf("Não foi possível abrir o arquivo para escrita dos dados");
                escreveArquivo(lista, agenda);
                fclose(lista);
                printf("\nPrograma encerrado, até a próxima \033[1;34mT=T\033[m");
                return 0;
        }

    } while(option>0 && option<7);


    return 0;

}

/*-------------------------------Funções de string-------------------------------*/

void fixFgets(char *string) {
    int cont = 0;
    while(string[cont]!='\n') cont+=1;
    string[cont] = '\0';
}

/*----------*/

int tamStr (char *string) {
    int cont = 0;
    while(string[cont]!='\0') cont+=1;

    return cont;
}

/*----------*/

char *UpperCase(char *string) {
    int contint=0;
    char *stringb = calloc(tamStr(string), sizeof(char));

    for(contint=0 ; contint<tamStr(string) ; contint+=1) {
        if (string[contint] >= 'a' && string[contint] <= 'z') stringb[contint] = string[contint]-32;
        else stringb[contint] = string[contint];
    }
    return stringb;
}

/*----------*/

char UpperChar(char carac) {
    char upado;

    if(carac>='a' && carac<='z') upado = carac-32;
    else upado = carac;

    return upado;
}

/*------------------------------- ARQUIVO -------------------------------*/

void lerArquivo(FILE *arquivo, contato **vetor) {
    contato novoctt;
    int cont2;
    char carac = fgetc(arquivo);

    while(carac!=EOF) {
        tamvet+=1;
        if(*vetor==NULL){
            if((*vetor = (contato *)calloc(tamvet, sizeof(contato)))==NULL) puts("Não foi possível inicializar o espaço de memória.");
        }
        else{
            if((*vetor = (contato *)realloc(*vetor, tamvet*sizeof(contato)))==NULL) puts("Não foi possível realocar o espaço na memória.");
        }

        for(cont2=0 ; carac!='$' ; cont2+=1) {
            novoctt.nome[cont2] = carac;
            carac = fgetc(arquivo);
        }
        novoctt.nome[cont2]='\0';
        fscanf(arquivo, "%ld$%d/%d$", &novoctt.numero, &novoctt.dia, &novoctt.mes);

        (*vetor)[tamvet-1] = novoctt;
        printf("\033[1;32mO contato foi adicionado com sucesso!\033[m\n");
        printf("Nome: %s\n", (*vetor)[tamvet-1].nome);
        printf("Número: %ld\n", (*vetor)[tamvet-1].numero);
        printf("Data de aniversário: %02d/%02d\n\n", (*vetor)[tamvet-1].dia, (*vetor)[tamvet-1]. mes);

        carac = fgetc(arquivo);
    }
}

/*----------*/

void escreveArquivo(FILE *arquivo, contato *vetor) {
    for(cont=0 ; cont<tamvet ; cont+=1) {
        fprintf(arquivo, "%s$%ld$%d/%d$", vetor[cont].nome, vetor[cont].numero, vetor[cont].dia, vetor[cont].mes);
    }
}

/*------------------------------- SWITCHS -------------------------------*/

void addCtt(contato **vetor) {
    contato novoctt;
    tamvet += 1;

    if(*vetor==NULL){
        if((*vetor = (contato *)calloc(tamvet, sizeof(contato)))==NULL) puts("Não foi possível inicializar o espaço de memória.");
    }
    else{
        if((*vetor = (contato *)realloc(*vetor, tamvet*sizeof(contato)))==NULL) puts("Não foi possível realocar o espaço na memória.");
    }

    while(getchar()!='\n');
    printf("Insira o nome do %ldºContato:\n>", tamvet);
    fgets(novoctt.nome, sizeof(novoctt.nome), stdin);
    fixFgets(novoctt.nome);
    puts("");

    printf("Insira o número do telefone de \033[1;32m%s\033[m:\n>", novoctt.nome);
    while(scanf("%ld", &novoctt.numero)==0) {
        puts("\033[1;31mNúmero inválido, tente novamente.\033[m");
        printf("Insira o número do telefone de \033[1;32m%s\033[m:\n>", novoctt.nome);
        while(getchar()!='\n');
    }
    puts("");

    printf("Insira a data de aniversário de \033[1;32m%s\033[m, no formato \033[1;33m'dd/mm'\033[m:\n>", novoctt.nome);
    while(scanf("%d/%d", &novoctt.dia, &novoctt.mes)==0 || novoctt.dia>31 || novoctt.dia<1 || novoctt.mes>12 || novoctt.mes<1 || (novoctt.mes==2 && novoctt.dia>28)) {
        puts("\033[1;31mA data de aniversário não é válida, tente novamente.\033[m");
        printf("Insira o aniversário de \033[1;32m%s\033[m, no formato 'dd/mm':\n>", novoctt.nome);
        while(getchar()!='\n');
    }
    while(getchar()!='\n');

    (*vetor)[tamvet-1] = novoctt;
    puts("");
    printf("\033[1;32mO contato foi adicionado com sucesso!\033[m\n");
    printf("Nome: %s\n", (*vetor)[tamvet-1].nome);
    printf("Número: %ld\n", (*vetor)[tamvet-1].numero);
    printf("Data de aniversário: %02d/%02d\n\n", (*vetor)[tamvet-1].dia, (*vetor)[tamvet-1]. mes);

    bbsCtts(*vetor);

}

/*----------*/

void bbsCtts(contato *vetor) {
    for(cont=0 ; cont<tamvet ; cont+=1) {
        for(cont2=0 ; cont2<tamvet-1 ; cont2+=1) {
            if(strcmp(UpperCase(vetor[cont].nome), UpperCase(vetor[cont2].nome))<0) {
                troca = vetor[cont];
                vetor[cont] = vetor[cont2];
                vetor[cont2] = troca;
            }
        }
    }
}

/*----------*/

void delCtt(contato **vetor) {
    contato *vetsup;
    long int numdel;
    cont2=0;
    while(getchar()!='\n');

    if(*vetor==NULL) printf("Não há contatos para serem deletados.");
    else {
        if((vetsup = (contato *)malloc(tamvet*sizeof(contato)))==NULL) printf("Não foi possível alocar o espaço para deleção.");
        else {
            for(cont=0 ; cont<tamvet ; cont+=1) {
                vetsup[cont] = (*vetor)[cont];
            }

            printf("Insira o número do contato que deseja deletar:\n>");
            while(scanf("%ld", &numdel)==0) {
                while(getchar()!='\n');
                printf("\033[1;31mNúmero inválido, tente novamente.\033[m");
                printf("Insira o número do contato que deseja deletar:\n>");
            }
            for(cont=0 ; cont<tamvet ; cont+=1) {
                if(numdel==vetsup[cont].numero) {
                    puts("Achei o contato que você quer deletar:");
                    printf("Nome: %s\n", vetsup[cont].nome);
                    printf("Número: %ld\n\n", vetsup[cont].numero);
                    tamvet-=1;
                    if((*vetor = (contato *)realloc(*vetor, tamvet*sizeof(contato)))==NULL && tamvet==0) printf("A lista agora não possui nenhum contato.");
                    else if((*vetor = (contato *)realloc(*vetor, tamvet*sizeof(contato)))==NULL) printf("Não foi possível realocar a lista.");

                    for(cont2=cont ; cont2<tamvet ; cont2+=1) {
                        (*vetor)[cont]=vetsup[cont+1];
                    }
                    break;
                }
                else if(cont==tamvet-1 && numdel!=vetsup[cont].numero) puts("O número digitado não corresponde a nenhum contato\n");
            }
        }
    }
    free(vetsup);
}

/*----------*/

void getCtt(contato *vetor) {
    char buscar[50], conf=0;
    cont2=0;
     while(getchar()!='\n');

    printf("Insira o nome que deseja procurar:\n>");
    fgets(buscar, 50, stdin);
    fixFgets(buscar);

    for(cont=0 ; cont<tamvet ; cont+=1) {
        if(strcmp(UpperCase(vetor[cont].nome), UpperCase(buscar))==0) {
            cont2+=1;
            printf("%dº %s\n", cont2, vetor[cont].nome);
            printf("Número: %ld\n", vetor[cont].numero);
            printf("Aniversário: %02d/%02d\n", vetor[cont].dia, vetor[cont].mes);
            puts("");
            puts("Caso deseje procurar por mais cadastros com esse nome digite [S].");
            printf("Caso não deseje mais procurar, digite [N]:\n>");
            while(scanf("%c", &conf)==0 || (conf!='S' && conf!='N')) {
                while(getchar()!='\n');
                puts("\033[1;31mEntrada inválida.\033[m");
                printf("Insira [S] ou [N]:\n>");
            }
            while(getchar()!='\n');
            if(conf=='S') continue;
            else break;
        }
        else if((cont==tamvet-1) && (strcmp(UpperCase(vetor[cont].nome), UpperCase(buscar))!=0) && cont2==0) puts("\033[1;31mUsuário não cadastrado.\033[m\n");
        else if((cont==tamvet-1) && (strcmp(UpperCase(vetor[cont].nome), UpperCase(buscar))!=0) && cont2>0) puts("\033[1;31mNão há mais nenhum usuário cadastrado com este nome.\033[m\n");
    }
}


/*----------*/

void printCtts(contato *vetor) {
    system("clear || cls");
    if(vetor==NULL) printf("Não há contatos nesta lista.\n");
    for(cont=0 ; cont<tamvet ; cont+=1) {
        printf("%dº Contato:\n", cont+1);
        printf("Nome: %s\n", vetor[cont].nome);
        printf("Número: %ld\n", vetor[cont].numero);
        printf("Data de aniversário: %02d/%02d\n\n", vetor[cont].dia, vetor[cont].mes);
    }
}

/*----------*/

void inicialCtts(contato *vetor) {
    char inicial = 0;
    
    while(getchar()!='\n');
    printf("Insira a inicial que deseja mostrar os contato:\n>");
    scanf("%c", &inicial);

    for(cont=0 ; cont<tamvet ; cont+=1) {
        if(UpperChar(inicial)==UpperChar(vetor[cont].nome[0])) {
            printf("%dºContato: %s\n", cont+1, vetor[cont].nome);
            printf("Número: %ld\n", vetor[cont].numero);
            printf("Aniversário: %02d/%02d\n\n", vetor[cont].dia, vetor[cont].mes);
        }
    }
}

/*----------*/

void niverCtts(contato *vetor) {
    int nivermes;
    cont2=0;

    printf("Insira o mês que deseja verirficar os aniversariantes:\n>");
    while(scanf("%d", &nivermes)==0 || nivermes>12 || nivermes<1) {
        while(getchar()!='\n');
        puts("\033[1;31mMês inválido, tente novamente.\033[m");
        printf("Insira o mês que deseja verirficar os aniversariantes:\n>");
    }
    puts("Os aniversariantes são:");
    for(cont=0 ; cont<tamvet ; cont+=1) {
        if(vetor[cont].mes==nivermes) {
            cont2+=1;
            printf("%dºContato:\n", cont+1);
            printf("Nome: %s\n", vetor[cont].nome);
            printf("Data: %02d/%02d\n\n", vetor[cont].dia, vetor[cont].mes);
        }
        else if((cont==tamvet-1) && (vetor[cont].mes!=nivermes) && (cont2==0)) printf("Não há usuários cadastrados que fazem aniversário no mês escolhido.");
    }
}
