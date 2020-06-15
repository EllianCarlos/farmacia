#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 1000

int n=1;
struct usuario{
    int cpf;
    char nome[30], telefone[17];
};

void lista (struct usuario *);
void inserir (struct usuario *);
void pesquisa (struct usuario *);
void menu_usuario (struct usuario *);

int main (){
    struct usuario cadastro_cliente[max];
    menu_usuario(cadastro_cliente);

    return 0;
}

void menu_usuario(struct usuario *cadastro_cliente){
    int opcao=0, i;
    while (opcao!=6 || opcao<6){
        printf("\t \t \t \t \t \n _________________________________________Cadastro de Clientes_________________________________________ \n ");
        printf("\n \t 1. Novo Cadastro.\n\t 2. Lista de Clientes.\n\t 3. Procurar um cliente.\n\t 4. Editar um cadastro.\n\t 5. Excluir cadastro.\n\t 6. Sair.\n\n");
        printf(" Selecione uma opcao por favor: ");
        scanf("%d",&opcao);
        system("cls");

        if(opcao==1){
            system("cls");
            printf("\n\n\n");
            inserir(cadastro_cliente);
            system("cls");
        }
        else if (opcao==2){
             lista(cadastro_cliente);
             system("pause");
             system("cls");
        }
        else if(opcao==3){
             pesquisa(cadastro_cliente);
             system("cls");
        }
        if(opcao==4){
            system("cls");
            printf("\n\n\n");
            // precisa de registro
            system("cls");
        }
        if(opcao==5){
            system("cls");
            printf("\n\n\n");
            // precisa de registro
            system("cls");
        }

        if (opcao ==6){
            printf("\n\n\n\n\t\t\t  Saindo do Menu de Cadastro de Clientes \n\n\n\n\n");
            break;
        }
        else{
            printf("Opcao invalida, favor pressione <ENTER> para voltar ao menu principal");
            getchar();
            system("cls");
        }
    }

}

void inserir (struct usuario *cadastro_cliente){
    int i, j, sair;
    for(i=n;i<=max;i++){
        fflush(stdin);
        printf("\t \t \t Realize o cadastro de um novo cliente \n \n");
        printf("\n Nome: ");
        gets((cadastro_cliente+i)->nome);
        fflush(stdin);
        printf("\n CPF (somente numeros): ");
        scanf("%d", &(cadastro_cliente+i)->cpf);
        fflush(stdin);
        printf("\n Telefone para contato: ");
        gets((cadastro_cliente+i)->telefone);
        fflush(stdin);
        n++;

        printf("\n \n Tecle 1 para novo cadastro ou 0 para sair. \n");
        scanf("%d", &sair);
        system("cls");
        if(sair==0) break;
        else continue;
    }
}


void lista (struct usuario *cadastro_cliente){
    int i;
    printf("\t \t ***************LISTA DE CLIENTES*****************\n \n");

    for(i=1;i<n;i++){
      printf("\n _______________Cadastro[%d]:_______________ \n", i);
      printf("\n Nome: %s", cadastro_cliente[i].nome);
      printf("\n CPF: %d", cadastro_cliente[i].cpf);
      printf("\n Telefone: %s", cadastro_cliente[i].telefone);
      printf("\n \n");
    }
}

void pesquisa (struct usuario *cadastro_cliente){
    int opesquisa, num, i, sair=1;

    while(sair!=0){
        printf("INSIRA O CPF DO CLIENTE PARA ACESSAR SEU CADASTRO: \n");
        scanf("%d", &num);
        fflush(stdin);

        for(i=1;i<=n;i++){
            if(num==cadastro_cliente[i].cpf){
                printf("\n _______________Cadastro[%d]:_______________ \n", i);
                printf("\n Nome: %s", cadastro_cliente[i].nome);
                printf("\n CPF: %d", cadastro_cliente[i].cpf);
                printf("\n Telefone: %s", cadastro_cliente[i].telefone);
                printf("\n \n");
                system("pause");
                system("cls");
            }
            else if (num!=cadastro_cliente[i].cpf){
                printf("\n CPF nao encontrado. \n \n");
                break;
            }
        }

        printf("\n \n Tecle 1 para nova busca ou 0 para sair. \n");
        scanf("%d", &sair);
        system("cls");
    }
}
