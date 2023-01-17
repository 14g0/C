#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------------*/

/*Struct*/
typedef struct _VENDA {
    char nome[32];
    long int cod;
    long int valor;
    int mes;
} registro;

/*-------------------------------------------------------------*/

/*Protótipo de função*/
void fixFgets(char *string);

/*void novoArquivo(void);*/
void makeFile(registro **vetor);
void readFile(registro **vetor);
void delFile(void);

void addRegistro(registro **vetor);
int checaRegistro(registro venda, registro *vetor);
void delRegistro(registro **vetor);
void altRegistro(registro *vetor);
void printRegistro(registro *vetor);
void bbsRegistro(registro *vetor);
void continuar(void);

/*-------------------------------------------------------------*/

/*Variáveis globais*/

long int tamvet=0;
int cont, cont2;
registro troca;

/*-------------------------------------------------------------*/

int main(void) {

    int option=0;
    registro *vendas=NULL;

    puts("\n\n=*=*=*=*=*=*=*=*= Lista de Registros =*=*=*=*=*=*=*=*=\n");

    readFile(&vendas);

    bbsRegistro(vendas);

    do {
        continuar();

        #ifdef _WIN32
        system("cls");
        #endif

        #ifdef __linux__
        system("clear");
        #endif

        puts("1 -> Incluir um registro.");
        puts("2 -> Excluir um registro.");
        puts("3 -> Alterar o valor de uma venda.");
        puts("4 -> Imprimir os registros no console.");
        puts("5 -> Criar um arquivo com os dados atuais.");
        puts("6 -> Excluir o arquivo de dados.");
        puts("0 -> Para finalizar o programa.");
        printf("Insira a sua opção:\n>");
        
        while(scanf("%d", &option)==0 || option<0 || option>6) {
            while(getchar()!='\n');
            puts("Opção inválida, tente novamente.");
            printf("Insira sua opção:\n>");
        }
        while(getchar()!='\n');

        switch(option) {
            
            case 1:
                addRegistro(&vendas);
                break;
            case 2:
                delRegistro(&vendas);
                break;
            case 3:
                altRegistro(vendas);
                break;
            case 4:
                printRegistro(vendas);
                break;
            case 5:
                makeFile(&vendas);
                break;
            case 6:
                delFile();
                break;
        }

    } while(option!=0);

    printf("Programa encerrado, até a próxima T-T\n");
/*
    if((arqin = fopen(arqatual, "w"))==NULL) printf("não foi possível abrir o arquivo para escrita.");
    escreveArquivo(arqin, vendas);
    fclose(arqin);
*/

    return 0;
}

/*-------------------------------Funções de string-------------------------------*/

void fixFgets(char *string) {
    int cont=0;
    while(string[cont]!='\n') {
        cont+=1;
    }
    string[cont] = '\0';
}

/*------------------------- Funções de Arquivo --------------------------*/

void makeFile(registro **vetor) {
    char nout[20];
    FILE *arquivo;

    printf("Insira o nome do arquivo que deseja criar, com a extensão '.bin':\n>");
    fgets(nout, sizeof(nout), stdin);
    fixFgets(nout);

    if((arquivo = fopen(nout, "wb"))==NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }
    else printf("\033[32mArquivo criado com sucesso\033[m");
    fwrite(*vetor, sizeof(registro), tamvet, arquivo);
    fclose(arquivo);

}

/*----------*/

void readFile(registro **vetor) {
    FILE *arquivo;
    registro *novoreg;
    char ninp[20], conf=0;

    do {
        printf("Insira o nome do arquivo binário que deseja ler, com a extensão:\n>");
        fgets(ninp, sizeof(ninp), stdin);
        fixFgets(ninp);

        if((arquivo = fopen(ninp, "rb"))==NULL) {
            conf=0;
            puts("\033[31mErro na leitura do arquivo binário solicitado.");
    
            puts("\033[33mCaso deseje inserir o nome de outro arquivo, aperte ENTER;");
            printf("Se não deseja inserir o nome de outro arquivo, dê qualquer outra entrada:\033[m\n>");
            scanf("%c", &conf);
            if(conf!='\n') {
                puts("");
                while(getchar()!='\n');
                return;
            }
            puts("");
        }
        else break;
    }while(conf=='\n');

    fseek(arquivo, 0, SEEK_SET);
    if((novoreg = (registro *)malloc(sizeof(registro)))==NULL) {
        printf("Não malocou o novoreg.\n");
        return;
    }
    while(fread(novoreg, sizeof(registro), 1, arquivo)==1) {
        tamvet += 1;
        if((*vetor==NULL)) {
            if((*vetor = (registro *)calloc(tamvet, sizeof(registro)))==NULL) {
                printf("erro no calloc da memória.\n");
                return;
            }
        }
        else {
            if((*vetor = (registro *)realloc(*vetor, tamvet*sizeof(registro)))==NULL) {
                printf("erro no realloc da memória.\n");
                return;
            }
        }

        (*vetor)[tamvet-1] = *novoreg;
    }
    fclose(arquivo);
    puts("\033[1;32mArquivo importado com sucesso.\n\033[m");
}

/*----------*/

void delFile(void) {
    char ndel[20];

    printf("Insira o nome do arquivo que deseja deletar:\n>");
    fgets(ndel, sizeof(ndel), stdin);
    fixFgets(ndel);

    if((remove(ndel))==0) puts("O arquivo foi deletado com sucesso.\n");
    else puts("O arquivo não pôde ser deletado.\n");
    
    while(getchar()!='\n');
}

/*------------------------------- SWITCHS -------------------------------*/

void addRegistro(registro **vetor) {
    registro novavenda;

    printf("Insira o código de vendedor do %ldºRegistro:\n>", tamvet+1);
    while(scanf("%ld", &novavenda.cod)==0) {
        while(getchar()!='\n');
        puts("\033[31mCódigo de vendedor inválido, tente novamente.\033[m");
        printf("Insira o código do vendedor:\n>");
    }
    puts("");
    
    printf("Insira o mês da venda do código %ld:\n>", novavenda.cod);
    while(scanf("%d", &novavenda.mes)==0 || novavenda.mes<1 || novavenda.mes>12) {
        while(getchar()!='\n');
        puts("Mês inválido, tente novamente.");
        printf("Insira o mês da venda do código %ld:\n>", novavenda.cod);
    }

    if(checaRegistro(novavenda, *vetor)==-1){
        puts("\033[1;31mEste registro não pode ser cadastrado.");
        puts("\033[1;33mJá existe outro registro com o mesmo código de vendedor e mês.\n\033[m");
        return;
    }

    tamvet +=1;

    while(getchar()!='\n');
    printf("Insira o nome do %ldºVendedor:\n>", tamvet);
    fgets(novavenda.nome, sizeof(novavenda.nome), stdin);
    fixFgets(novavenda.nome);
    puts("");

    printf("Insira o valor da venda:\n>");
    while(scanf("%ld", &novavenda.valor)==0) {
        while(getchar()!='\n');
        printf("Valor inválido, tente novamente.");
        printf("Insira o valor da venda:\n>");
    }
    puts("");

    if(*vetor==NULL) {
        if((*vetor = (registro *)calloc(tamvet, sizeof(registro)))==NULL) puts("Não foi possível inicializar o espaço.\n");
    }
    else {
        if((*vetor = (registro *)realloc(*vetor, tamvet*sizeof(registro)))==NULL) puts("Não foi possível rralocar a memória.\n\n");
    }

    (*vetor)[tamvet-1] = novavenda;
    puts("");
    printf("\033[1;32mO registro foi adicionado com sucesso!\033[m\n");
    printf("Nome: %s\n", (*vetor)[tamvet-1].nome);
    printf("Código: %ld\n", (*vetor)[tamvet-1].cod);
    printf("Valor da venda:%ld\n", (*vetor)[tamvet-1].valor);
    printf("Mês da venda: %02d\n", (*vetor)[tamvet-1].mes);
    puts("");

    while(getchar()!='\n');

    bbsRegistro(*vetor);

    return;
}

/*----------*/

int checaRegistro(registro venda, registro *vetor) {
    for(cont=0 ; cont<tamvet ; cont+=1) {
        if((vetor[cont].cod==venda.cod) && (vetor[cont].mes==venda.mes)) {
            return -1;
        }
        else if((cont==tamvet-1) && (vetor[cont].cod!=venda.cod) && (vetor[cont].mes!=venda.mes)) return 1;
    }
    return 0;
}

/*----------*/

void delRegistro(registro **vetor) {
    registro *vetsup, del;

    if(*vetor==NULL) printf("Não há registros neste vetor.\n");
    else {
        if((vetsup = (registro *)malloc(tamvet*sizeof(registro)))==NULL) printf("Não foi possível alocar o vetor de suporte.\n");
        else {
            for(cont=0 ; cont<tamvet ; cont+=1) {
                vetsup[cont] = (*vetor)[cont];
            }

            printf("Insira o código do vendedor que deseja deletar:\n>");
            while(scanf("%ld", &del.cod)==0) {
                while(getchar()!='\n');
                puts("Código de vendedor inválido.");
                printf("Insira o código do vendedor que deseja deletar:\n>");
            }
            puts("");
            printf("Insira o mês da venda para o código \033[1;32m%ld\033[m:\n>", del.cod);
            while(scanf("%d", &del.mes)==0 || del.mes<1 || del.mes>12) {
                while(getchar()!='\n');
                puts("Mês inválido.");
                printf("Insira o mês da venda para o código \033[1;32m%ld\033[m:\n>", del.cod);
            }

            for(cont=0 ; cont<tamvet ; cont+=1) {
                if((vetsup[cont].cod==del.cod) && (vetsup[cont].mes==del.mes)) {
                    puts("\nAchei o registro que você deseja deletar.");
                    printf("Nome: %s\n", vetsup[cont].nome);
                    printf("Código: %ld\n", vetsup[cont].cod);
                    printf("Valor: %ld\n", vetsup[cont].valor);
                    printf("Mês: %d\n", vetsup[cont].mes);
                    puts("");
                    tamvet-=1;

                    if((*vetor = (registro *)realloc(*vetor, tamvet*sizeof(registro)))==NULL && tamvet==0) puts("A lista se encontra vazia.\n");
                    else if((*vetor = (registro *)realloc(*vetor, tamvet*sizeof(registro)))==NULL)  puts("Não foi possível realocar as vendas.\n");
                    
                    for(cont2=cont ; cont2<tamvet ; cont2+=1) {
                        (*vetor)[cont2] = vetsup[cont2+1];
                    }
                    break;
                }
                else if((cont==tamvet-1) && (vetsup[cont].cod!=del.cod) && (vetsup[cont].mes!=del.mes)) puts("Não há registros cadastrados com esses dados.\n");
            }
        }
        free(vetsup);
    }
    
}

/*----------*/

void altRegistro(registro *vetor) {
    registro altreg;

    printf("Insira o código do vendedor para alteração:\n>");
    while(scanf("%ld", &altreg.cod)==0) {
        while(getchar()!='\n');
        puts("Código inválido, tente novamente.");
        printf("Insira o código do vendedor para alteração:\n>");
    }
    puts("");

    printf("Insira o mês para alteração\n>");
    while(scanf("%d", &altreg.mes)==0 || altreg.mes>12 || altreg.mes<1) {
        while(getchar()!='\n');
        puts("Mês inválido, tente novamente.");
        printf("Insira o mês para alteração:\n>");
    }

    if(checaRegistro(altreg, vetor)==-1) {
        puts("\033[1;32mEncotrei o registro.\033[m");
        printf("Insira o valor para alteração:\n>");
        while(scanf("%ld", &altreg.valor)==0) {
            while(getchar()!='\n');
            puts("Valor inválido, tente novamente.");
            printf("Insira o valor para alteração:\n>");
        }
        vetor[cont].valor = altreg.valor;
        puts("\033[1;32mValor alterado com sucesso.\033[m");
    }
    else puts("\033[1;31mRegistro não encontrado.\033[m\n");
    puts("");

    while(getchar()!='\n');
}

/*----------*/

void printRegistro(registro *vetor) {
    puts("");
    if(vetor==NULL) printf("Não há contatos para serem mostrados.\n\n");
    for(cont=0 ; cont<tamvet ; cont+=1) {
        printf("%dºRegistro\n", cont+1);
        printf("Nome: %s\n", vetor[cont].nome);
        printf("Código: %ld\n", vetor[cont].cod);
        printf("Valor: %ld\n", vetor[cont].valor);
        printf("Mês da venda: %d\n\n", vetor[cont].mes);
    }
}

/*----------*/

void bbsRegistro(registro *vetor) {
    registro troca;

    for(cont=0 ; cont<tamvet-1 ; cont+=1) {
        for(cont2=0 ; cont2<tamvet-1-cont ; cont2+=1) {
            if(vetor[cont2].cod>vetor[cont2+1].cod) {
                troca = vetor[cont2];
                vetor[cont2] = vetor[cont2+1];
                vetor[cont2+1] = troca;
            }
            else if((vetor[cont2].cod==vetor[cont2+1].cod) && vetor[cont2].mes>vetor[cont2+1].mes) {
                troca = vetor[cont2];
                vetor[cont2] = vetor[cont2+1];
                vetor[cont2+1] = troca;
            }
        }
    }
}

/*----------*/

void continuar(void) {
    printf("Aperte ENTER para continuar:");
    while(getchar()!='\n');
}
