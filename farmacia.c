#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 2
#define maxi 30


struct cadastro_prod{
char tipo[maxi], nome[maxi], fornecedor[maxi];
float preco;
int identificador, quantidade;
};
struct cadastro_prod dados_prod[max];


void recebe_inf(){
    int i;
    for(i=0; i<max; i++){

        printf("\nDigite as informacoes para o cadastro do produto:\n");

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
}
void busca_prod(){

    int i;
    char compara_nome[maxi];

    printf("Digite o nome do produto:");
    gets(compara_nome);

    for(i=0; i<max; i++){
        if(compara_nome == dados_prod[i].nome){
                printf("Altere a quantidade do produto (atual = %d): ", dados_prod->quantidade);
        scanf("%d", &dados_prod->quantidade);
 // aqui falta fazer a função seguinte -> altere a quantidade de produto
        }
    }
}

int main()
{   char verificador[5];
    int i;

    printf("O produto ja tem cadastro?\n");
    gets(verificador);

    if(stricmp(verificador, "nao")==0){

                recebe_inf();
        }else{
                busca_prod();
    }
    return 0;
}
