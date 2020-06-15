/*	Projeto da farmácia genérica 	*/


#include <stdio.h>			// 	Inclusão de bibliotecas
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

		//	Definição de constantes e variáveis globais

#define max 1000	//	Define o número máximo de produtos e clientes cadastrados no sistema //
int n = 1;			//Usada p/ id a quantidade de usuarios já cadastrados e iniciar o vetor na posição livre atual el na função lista //

#define maxo 2		//	Usada na parte de produtos
#define maxi 30

	/*	Definição das structs usadas 	*/

struct cadastro_prod{								//	Os produtos possuem um tipo, um nome, um fornecedor, um preço
    char tipo[maxi], nome[maxi], fornecedor[maxi];		//	Um numero identificador e uma quantidade em estoque
    float preco;
    int identificador, quantidade;
};

struct usuario{										//	Os clientes possuem um dado de cpf, um nome e um telefone; todos como strings.
    char cpf[12], nome[30], telefone[17];
};

struct usuario cadastro_cliente[max];			//	Definição das estruturas de dados.
struct cadastro_prod dados_prod[max];			//	Estão como variáveis globais, enquanto ainda não usamos arquivos de texto

		//	Protótipos das funções

void lista (struct usuario *p);
void inserir (struct usuario *p);
struct usuario pesquisa_cliente (struct usuario *cadastro_cliente);
void menu_usuario (struct usuario *cadastro_cliente);
void menu_produtos ();
void menu_fluxo ();
int busca_de_produtos (char *p);
void entrada_de_produto();
void saida_de_produto();
void emitir_nota (struct cadastro_prod *produto_vendido, int numvendido, char *cpfzinho);

	/*	Menu geral/principal	*/

int main () {

	int controller = 0;

	printf ("Bem vindo ao sistema gerencial da farmacia.\n\nQual menu deseja utilizar?\n\n");
	printf ("1. Clientes \n2. Produtos \n3. Fluxo de mercadorias\n\n0. Sair do programa\n\n");
	scanf ("%d", &controller);
	fflush (stdin);

	while (1) {
		switch (controller) {
			case 1:
				menu_usuario(&cadastro_cliente[0]);
				break;
			case 2:
				menu_produtos();
				break;
			case 3:
				menu_fluxo();
				break;
			case 0:
				return 0;
			default:
				printf ("\n\nEntrada de dado invalida.\n\nRetornando ao menu...");
		}
	}

	return 0;
}

					/*	Parte de produtos;	Flavio e Thales	*/

void recebe_inf(){

    int i;

    for(i = 0; i < maxo; i++){

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

void busca_prod(){	/*	Possivelmente, é interessante que deixemos essa função mais completa... Com opções de editar qualquer dado do produto	*/

    int i;
    char compara_nome[maxi];

    printf("Digite o nome do produto:");
    gets(compara_nome);

    for(i=0; i<maxo; i++){
        if(compara_nome == dados_prod[i].nome){

            printf("Altere a quantidade do produto (atual = %d): ", dados_prod->quantidade);
       		scanf("%d", &dados_prod->quantidade);

        }
    }
}

void menu_produto() {

   	char verificador[5];
    int i;

    printf("\nO produto ja tem cadastro?\n");
    gets(verificador);

    if(stricmp(verificador, "nao") == 0){
        recebe_inf();
    }
	else{
        busca_prod();
    }
}


					/*	Parte de usuários;	Giovanna	*/


void menu_usuario(struct usuario *cadastro_cliente){

    int opcao=0, i;

    while (opcao!=6 || opcao<6){

    printf("\t \t \t \t \t \n _________________________________________Cadastro de Clientes_________________________________________ \n ");
    printf("\n \t 1. Novo Cadastro.\n\t 2. Lista de Clientes.\n\t 3. Procurar um cliente.\n\t 4. Editar um cadastro.\n\t 5. Excluir cadastro.\n\t 6. Sair.\n\n");
    printf(" Selecione uma opcao, por favor:\n");

    scanf("%d", &opcao);
    fflush(stdin);

    system("cls");

    switch (opcao) {
        case 1:
            system("cls");
            printf("\n\n\n");
            inserir(cadastro_cliente);
            system("cls");
            break;

        case 2:
            lista(cadastro_cliente);
            system("pause");
            system("cls");
            break;

        case 3:
            pesquisa(cadastro_cliente);
            system("cls");
            break;

        case 4:
            system("cls");
            printf("\n\n\n");
            // precisa de arquivo (não finalizado ainda)
            system("cls");
            break;

        case 5:
            system("cls");
            printf("\n\n\n");
            // precisa de arquivo (não finalizado ainda)
            system("cls");
            break;

        case 6:
             printf("\n\n\n\n\t\t\t  Saindo do Menu de Cadastro de Clientes \n\n\n\n\n");
             break;

        default:	{
            printf("Opcao invalida, favor pressione <ENTER> para voltar ao menu principal");
            getchar();
            system("cls");
            }
        }
    }
}

/*	Vamos ter que alterar essa função para uma função que cadastra um único cliente, e criar outra função que chama essa várias vezes	*/

void inserir(struct usuario *cadastro_cliente){

	int i, j, sair;

	for(i=n;i<=max;i++){

	    fflush(stdin);
	    printf("\t \t \t Realize o cadastro de um novo cliente \n \n");
	    printf("\n Nome: ");
	    gets((cadastro_cliente+i)->nome);
	    fflush(stdin);

	    printf("\n CPF (somente numeros): \n");
	    gets((cadastro_cliente+i)->cpf);
	    fflush(stdin);

	    printf("\n Telefone para contato: ");
	    gets((cadastro_cliente+i)->telefone);
	    fflush(stdin);

	    n++; // atualiza o num total de clientes no sistema

	    printf("\n \n Tecle 1 para novo cadastro ou 0 para sair. \n");
	    scanf("%d", &sair);
	    system("cls");

	    if (sair==0) break;
	    else continue;
	}
}


void lista (struct usuario *cadastro_cliente){

    int i;
    printf("\t \t ***************LISTA DE CLIENTES*****************\n \n");

	for(i=1;i<n;i++){
	  printf("\n _______________Cadastro[%d]:_______________ \n", i);
	  printf("\n Nome: %s", cadastro_cliente[i].nome);
	  printf("\n CPF: %s", cadastro_cliente[i].cpf);
	  printf("\n Telefone: %s", cadastro_cliente[i].telefone);
	  printf("\n \n");

	}
}

struct usuario pesquisa_cliente (struct usuario *cadastro_cliente){

	int opesquisa, i, sair=1;
	char num_cpf[12];

    while(sair!=0){

        printf("INSIRA O CPF DO CLIENTE PARA ACESSAR SEU CADASTRO: \n");
        fflush(stdin);
        gets(num_cpf);
        fflush(stdin);

        for(i = 1; i <= n; i++){

	        if (strcmp (num_cpf, cadastro.cliente[i].cpf) == 0) {

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
        fflush (stdin);
        system("cls");
    }
}

		/*	Parte de fluxo (entrada e saída de produtos)	(João Vitor)	*/
		//	Falta a parte do carrinho de compras...

void menu_fluxo () {

	int controller = 0;


	printf ("\n\nO que deseja fazer? \n\n1. Registrar entrada de produtos \n")
	printf ("2. Registrar saída (venda) de produtos \n0. Retornar ao menu principal.\n\n");
	scanf ("%d", &controller);

	switch (controller) {
		case 1:
			entrada_de_produto();
			break;

		case 2:
			saida_de_produto();
			break;

		case 0:
			break;

		default:
			printf ("Entrada de dados invalida. Retornando ao menu principal...");
	}
}

void saida_de_produto() {

	char stringzinha[30], controller, controller2 = '0', cpf_do_cliente[12];
	int posicao_do_produto, quantia, restante;

	printf ("\n O cliente a quem a venda esta sendo realizada, possui cadastro?\n");
	gets (controller);

	if (stricmp(controller, "nao") != 0) {
		/* 	Cadastra o cliente	*/
	}

	else {

		printf ("\n\nDigite o CPF do cliente a que foi vendido.\n");
		gets (cpf_do_cliente);

		system ("cls");
		printf ("Digite o nome do produto que foi vendido\n\n");
		gets (stringzinha);


		posicao_do_produto = busca_de_produtos (stringzinha);
		if (posicao_do_produto != NULL) {	//	Verificação de sucesso ao encontrar o produto com determinado nome

			printf ("\nQuantas unidades desse produto devem ser retiradas do sistema?\n");
			scanf ("%d", &quantia);
			fflush (stdin);

			if (dados_prod[posicao_do_produto].quantidade < quantia) {
				printf ("\nNao ha produtos o suficiente em estoque para concluir a venda. \n");
				printf ("Atualmente, existem apenas %d produtos em estoque.\n\n1. Vender o estoque inteiro.\n2. Retornar ao menu\n", dados_prod[posicao_do_produto].quantidade);
				scanf ("%c", &controller2);
				fflush (stdin);

				switch (controller2) {
					case '1':
						restante = dados_prod[posicao_do_produto].quantidade;
						dados_prod[posicao_do_produto].quantidade = 0;
					break;
					case '2':
						//	Apenas atribuindo um valor diferente de 0 ao controller2, para que ele nao entre na verificação abaixo e não seja impressa uma nota.
					break;
				}

			}
			dados_prod[posicao_do_produto].quantidade -= quantia;

			printf ("\nOperacao concluida com sucesso. \n");
			printf ("Agora, a quantia de %s em estoque e: %d", dados_prod[posicao_do_produto].nome, dados_prod[posicao_do_produto].quantidade);
		}
	}
	else {
		printf ("\n\nRetornando ao menu...\n\n");
		Sleep (2000);
		system ("cls");

	}

	if (controller2 == '0') {	//	Controller2 é a variável usada no caso em que não há produtos em estoque o suficiente para efetuar a venda.
								//	Logo, se houver algo nela, temos de emitir uma nota com a quantia que foi vendida, e não a total pedida previamente

		emitir_nota (&dados_prod[posicao_do_produto], quantia, cpf_do_cliente);	/*	envia como argumentos, o endereço do vetor em que está o produto,
																				a quantia vendida e o cpf do cliente, para a inserção na nota.*/
	}
	else if (controller 2 == '1') {		//	Dessa vez, envia como argumento a quantia que foi vendida. (Que havia em estoque)
		emitir_nota (&dados_prod[posicao_do_produto], restante, cpf_do_cliente);
	}
	//	Se o controller for 2, significa que simplesmente retornamos ao menu e nao houve venda, logo, sem nota.
}

void entrada_de_produto() {		/*	A função de saída de produtos busca por um produto já existente/cadastrado e subtrai da quantidade
									em estoque, o valor digitado. Funções intermediarias: busca_de_produtos.
									Fiz a função de busca retornando o valor int correspondente à posição do produto no vetor de produtos.	*/

	char stringzinha[30];
	int posicao_do_produto, quantia;

	system ("cls");
	printf ("Digite o nome do produto que chegou aos estoques\n\n");
	gets (stringzinha);

	posicao_do_produto = busca_de_produtos (stringzinha);
	if (posicao_do_produto != NULL) {	//	Verificação de sucesso ao encontrar o produto com determinado nome

		printf ("\nQuantas unidades desse produto devem ser adicionadas ao sistema?\n");
		scanf ("%d", &quantia);
		fflush (stdin);

		dados_prod[posicao_do_produto].quantidade += quantia;

		printf ("\nOperacao concluida com sucesso. \n");
		printf ("Agora, a quantia de %s em estoque e: %d", dados_prod[posicao_do_produto].nome, dados_prod[posicao_do_produto].quantidade);
	}

	else {
		printf ("\n\nRetornando ao menu...\n\n");
		Sleep (2000);
		system ("cls");
	}

}

int busca_de_produtos (char *p) {	/*	*p é o parametro que receberá a string enviada como argumento à função	*/

	int posicao, i, controller = 0;

	for (i = 0; i < max; i++) {		//	Inicia-se a verificação pelo vetor de produtos, procurando algum produto do nome recebido por parametro pela funcao
		if (stricmp(dados_prod[i].nome, p) == 0) {
			posicao = i;			//	A variavel posicao recebe a posicao do vetor em que esta o produto de nome procurado
			controller = 1;
			break;
		}
	}

	if (controller == 0) {
		printf ("\nNao ha nenhum produto cadastrado com o nome: %s\n\n", p);
		Sleep (2000);
		return NULL;
	}

	return posicao;					//	A posicao do vetor é retornada
}
