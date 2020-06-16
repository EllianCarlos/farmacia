#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxi 30
#define max 2

struct cadastro_prod{              /*struct com as infos do produto*/
char tipo[maxi], nome[maxi], fornecedor[maxi]; /*tipo = natureza do produto*/
float preco;
int identificador, quantidade;               /*identificador = numero do produto para sua computação no software interno*/
};

struct cadastro_prod *dados_prod;

void recebe_inf(){                          /*function para receber as infos de um produto novo e armazenar em um arquivo binario*/
    int i;
    FILE *arq;
    if((arq=fopen("dados_farmacia.txt", "rb+"))==NULL){    /*verifica se o arquivo abre corretamente*/
        printf("Erro ao abrir o arquivo!");
    }
    for(i=0; i<1; i++){              /*laço for que pede as infos de um novo produto para cadastro*/

        printf("\nDigite as informacoes para o cadastro do produto:\n");
        fflush(stdin);
        printf("\nFornecedor[%d]:", i+1);
        gets(dados_prod[i].fornecedor);

        printf("Tipo do produto[%d]:", i+1);
        gets(dados_prod[i].tipo);

        printf("Identificador do produto[%d]:", i+1);
        scanf("%d", &dados_prod[i].identificador);
        fflush(stdin);

        printf("Nome do produto[%d]:", i+1);
        gets(dados_prod[i].nome);

        printf("Quantidade[%d]:", i+1);
        scanf("%d", &dados_prod[i].quantidade);
        fflush(stdin);

        printf("Preco[%d]:", i+1);
        scanf("%f", &dados_prod[i].preco);
        fflush(stdin);
    }
    fseek(arq, 0, SEEK_CUR);               /*armazenagem das infos no arquivo*/
    fwrite(dados_prod, sizeof(struct cadastro_prod), 1, arq);
    fclose(arq);
}
void busca_prod(){                       /*function de busca por produto já cadastrado no arquivo*/

    int i,j=0, verificador=0;

    FILE *arq;                            /*verifica se o arquivo abre corretamente*/
    if((arq=fopen("dados_farmacia.txt", "rb+"))==NULL){
        printf("Erro ao abrir o arquivo!");
    }
    fflush(stdin);                        /*limpa o buffer e recebe o codigo do produto para busca no arquivo*/
    printf("Digite o codigo identificador do produto para alterar a quantidade:\n");
    scanf("%d", &verificador);

    fseek(arq, 0, SEEK_SET);       /*procura pelo produto no arquivo*/
    fread(dados_prod, sizeof(struct cadastro_prod), 1, arq);

    for(i=0; i<max; i++){           /*laço for para alterar a quantidadde do produto já cadastrado*/
        if(verificador == dados_prod[i].identificador){
            printf("Altere a quantidade do produto (atual = %d):\n", dados_prod->quantidade);
            scanf("%d", &dados_prod->quantidade);
            j++;
            }
        }
        if(j == 0){                 /*laço de resposta para caso o produto não seja encontrado (não cadastrado ainda)*/
            printf("Produto nao encontrado!\n\n");
        }
        fseek(arq, 0, SEEK_SET);
        fwrite(dados_prod, sizeof(struct cadastro_prod), 1, arq);
        fclose(arq);
    }
void altera_prod(){                 /*function para fazer qualquer alteração num dado produto já cadastrado*/
    int i, codigo;

    FILE *arq;                        /*verifica se o arquivo abre corretamente*/
    if((arq=fopen("dados_farmacia.txt", "rb+"))==NULL){
            printf("Erro ao abrir o arquivo!");
    }                                          /*lê e procura no arquivo o codigo do produto a ser alterado*/
    printf("Digite o codigo do produto a ser alterado:\n");
    scanf("%d", &codigo);

    fseek(arq, 0, SEEK_SET);
    fread(dados_prod, sizeof(struct cadastro_prod), 2, arq);

    for(i=0; i<max; i++){                        /*entrada dos novos dados do produto já computado*/
        if(codigo == dados_prod[i].identificador){
            fflush(stdin);
            printf("\nFornecedor[%d]:", i+1);
            gets(dados_prod[i].fornecedor);

            printf("Tipo do produto[%d]:", i+1);
            gets(dados_prod[i].tipo);

            printf("Identificador do produto[%d]:", i+1);
            scanf("%d", &dados_prod[i].identificador);
            fflush(stdin);

            printf("Nome do produto[%d]:", i+1);
            gets(dados_prod[i].nome);

            printf("Quantidade[%d]:", i+1);
            scanf("%d", &dados_prod[i].quantidade);
            fflush(stdin);

            printf("Preco[%d]:", i+1);
            scanf("%f", &dados_prod[i].preco);
            fflush(stdin);

            fseek(arq, 0, SEEK_SET);
            fwrite(dados_prod, sizeof(struct cadastro_prod), 1, arq);
            fclose(arq);
        }
    }
}
void painel(){                          /*function do 'menu' do programa*/
    char verificador[5], anulador[5];
    int j, k;

    gets(verificador);
    fflush(stdin);

    if(stricmp(verificador, "nao")==0){           /*limpa a tela conforme a vontade do usuário*/
        recebe_inf();
        printf("Para limpar a tela digite:[1]\n");
        scanf("%d", &j);
                }
    if(j == 1){
        system("cls");
    }
    else{                             /*exibe as opções do usuario e espera por uma resposta, reagindo a qualquer entrada possivel*/
        for(k=1;k<max;k++){
            printf("Para alterar a quantidade do produto:[1]\n");
            printf("Para alterar o produto digite:       [2]\nPara limpar a tela digite:           [3]\n");
            scanf("%d", &j);

            if(j == 1){
                busca_prod();
            }
            if(j == 2){
                altera_prod();
            }
            if(j == 3){
                system("cls");
            }
            else if(j>3 || j<1){
                printf("\nEntrada inválida!\n");
                k--;
            }
        }
    }
            printf("O produto ja tem cadastro?\n");
            gets(anulador);
            stricmp("verficador", "anulador");
        }
int main(){      /*function main que chama e realiza as functions já declaradas, alocando dinamicamente espaço na memoria para cadastrar os produtos*/
    int j=1;
    dados_prod=(struct cadastro_prod *)malloc(100*sizeof(struct cadastro_prod));
    printf("O produto ja tem cadastro?\n");
    while(j > 0){
        painel();
        printf("Para encerrar o programa digite[0]\n");
        scanf("%d", &j);
    }
    free(dados_prod);
    return 0;
}
