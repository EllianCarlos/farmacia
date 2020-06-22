#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h> // Usamos a funcao log10 para gerar notas

#define MAX_CLIENTES 1000
#define maxi 30
#define max 100
#define MAX_ITENS_CARRINHO 30

#define DBG printf("estou aqui\n")
#define DBGs(s) printf("\n%s\n", s);
#define DBGi(i) printf("\n%d\n", i);

int n = 1; //Usada p/ id a quantidade de usuarios ja cadastrados e iniciar o vetor na posicao livre atual na funcao lista //


// Criacao dos tipos que serao utilizados
typedef struct cadastro_prod
{                                                  /*struct com as infos do produto*/
    char tipo[maxi], nome[maxi], fornecedor[maxi]; /*tipo = natureza do produto*/
    float preco;
    int identificador, quantidade; /*identificador = numero do produto para sua computacao no software interno*/
} cadastro_prod;

typedef struct usuario
{
    char nome[30], telefone[22], cpf[12]; //struct com os dados dos clientes a serem cadastrados no sistema da farmacia.
} usuario;

typedef struct compra {	// Struct utilizada na funcionalidade do carrinho e emissao de nota
    int codigoProd;
    int quantidadeProd;
    float valorProd;
    char nomeProd[maxi];
    char nomeUser[maxi];
    char cpf[12];
} compra;

typedef struct carrinho {
    int numeroDeCompras;
    compra compras[MAX_ITENS_CARRINHO];
} carrinho;

// Declaracao das funcoes que serão utilizados
usuario *alocar_cliente(int nclientes);
usuario *inserir_cliente();
usuario *buscar_cliente();

void menu_usuario();
void arquivar_cliente(usuario *);    // prototipo de funcoes utilizadas no menu de cadastro dos clientes.
void lista_clientes();
void lista_produtos();
void altera_prod();
void arq_num_produtos(int nprodutos);
void arq_num_clientes(int nclientes);
void menu_alterar_cliente();
void alterar_nome_cliente();
void mostrar_prod(int verificador, int quantx);
void alterar_telefone_cliente();
void alterar_cpf_cliente();
void excluir_cliente();
void remover_prod();
usuario pesquisa_cliente(usuario *cadastro_cliente);
void menu_usuario();
void recebe_inf();
// void menu_usuario(usuario *cadastro_cliente);
void menu_produto();
void menu_fluxo();
void busca_prod();
int busca_de_produtos(char *p);
void entrada_de_produto();
void saida_de_produto();
void emitir_nota(compra *cp);
carrinho *iniciar_carrinho();
void menu_carrinho();

usuario cadastro_cliente[max]; //	Definicao das estruturas de dados.
cadastro_prod dados_prod[max]; //	Estao como variaveis globais para facilitar o uso, mas houve bastante cuidado no uso.


int main() {
    // Funcao principal

    int controller = 0;


    while (1)	//	Menu principal, exibe as opcoes principais entre as funcionalidades do programa
    {

        printf("Bem vindo ao sistema gerencial da farmacia.\n\nQual menu deseja utilizar?\n\n");
        printf("1. Clientes \n2. Produtos \n3. Fluxo de mercadorias \n4. Iniciar Carrinho\n\n0. Sair do programa\n\n");
        scanf("%d", &controller);
        fflush(stdin);
        switch (controller)
        {
            case 1:
                menu_usuario();		//	Cada opcao selecionada refere o respectivo menu
                break;
            case 2:
                menu_produto();
                // painel();
                break;
            case 3:
                menu_fluxo();
                break;
            case 4:
                menu_carrinho();
                break;
            case 0:
                return 0;
            default:
                printf("\n\nEntrada de dado invalida.\n\nRetornando ao menu...");
        }
    } while(1);

    return 0;
}

/*--------------------------------------*/
/* PARTE DA GIOVANA */
void menu_usuario()
{
    usuario *cliente_cadastro;

    int opcao = 0, i, nclientes = 1;
    while (opcao < 6)
    {

        printf("\t \t \t \t \t \n _________________________________________Cadastro de Clientes_________________________________________ \n ");
        printf("\t \t \t \t \t1. Novo Cadastro.\n");
        printf("\t \t \t \t \t2. Lista de Clientes.\n");
        printf("\t \t \t \t \t3. Procurar um Cliente.\n");
        printf("\t \t \t \t \t4. Editar Cadastro.\n");
        printf("\t \t \t \t \t5. Excluir Cadastro.\n");
        printf("\t \t \t \t \t6. Voltar ao Menu Principal.\n");
        printf("\t \t \t \t \t7. Sair do Sistema.\n");
        printf(" Selecione uma opcao, por favor:\n");

        scanf("%d", &opcao);
        system("cls");

        switch (opcao)
        {
            case 1:
                system("cls");
                cliente_cadastro = alocar_cliente(nclientes); //aloca um ponteiro usuario para cadastro.
                cliente_cadastro = inserir_cliente();         //armazena as informacoes de entrada de cadastro.
                arquivar_cliente(cliente_cadastro);           // salva as informacoes do ponteiro no arquivo binario.
                arq_num_clientes(nclientes);                  // atualiza o numero de cadastros em um arquivo txt.
                system("cls");
                break;

            case 2:
                system("cls");
                lista_clientes(); //lista todos os clientes armazenados ate o momento no arquivo.
                system("pause");
                system("cls");
                break;

            case 3:
                system("cls");
                buscar_cliente(); // busca um cliente pelo cpf e retorna um ponteiro que aponta para cliente especificado.
                system("pause");
                system("cls");
                break;

            case 4:
                system("cls");
                menu_alterar_cliente(); //menu que permite alterar o cadastro de um cliente.
                system("cls");
                break;

            case 5:
                system("cls");
                excluir_cliente(); // exclui um cliente do arquivo binario e atualiza o numero total de cadastros no txt.
                system("cls");
                break;

            case 6:
                printf("\n\n\n\n\t\t\t  Saindo do Menu de Cadastro de Clientes. \n\n\n\n\n");
                break;

            case 7:
                system("cls");
                printf("\n\n\n\n\t\t\t  Saindo do Sistema. \n\n\n\n\n");
                exit(0);

            default:
            {

                printf("Opcao invalida, favor pressione <ENTER> para voltar ao menu principal");
                getchar();
                system("cls");
            }
        }
    }
}

usuario *alocar_cliente(int nclientes)	/* aloca um ponteiro struct usuario para entrada de um novo cadastro*/
{
    usuario *c;

    c = (usuario *)calloc(nclientes, sizeof(usuario));

    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return NULL;
    }

    return c;
}

usuario *inserir_cliente()	/* insere os dados de entrada de cadastro e retorna o ponteiro preenchido. */
{

    usuario *cadastro;

    printf("\t \t \t *Realize o cadastro de um novo cliente!* \n \n");
    printf("\n Nome: ");
    fflush(stdin);
    gets(cadastro->nome);
    fflush(stdin);
    printf("\n CPF (somente numeros): ");
    gets(cadastro->cpf);
    fflush(stdin);
    printf("\n Telefone para contato: ");
    gets(cadastro->telefone);
    fflush(stdin);
    return cadastro;
    system("pause");
}

/* função para arquivar o ponteiro com os dados do cliente cadastrado
no arquivo binario que funciona como o banco de dados de clientes */

void arquivar_cliente(usuario *cliente_salvar)
{

    FILE *arq;

    if ((arq = fopen("dados_clientes.bin", "ab+")) == NULL)
        printf("\nErro abrindo arquivo.\n");

    fseek(arq, 0, SEEK_END);
    fwrite(cliente_salvar, sizeof(usuario), 1, arq);
    fclose(arq);
}

/* esse arquivo em txt grava o numero de clientes cadastrados e e
usado por outras funcoes abaixo, ele se faz necessario para que se
saiba a quantidade de cadastros ja salvos mesmo se o programa
for fechado e aberto novamente. */

void arq_num_clientes(int nclientes)
{

    FILE *arq;
    unsigned int tamcliente = 0;
    arq = fopen("num_clientes.txt", "r+");

    fseek(arq, 0, SEEK_SET);
    fscanf(arq, "%d", &tamcliente);

    tamcliente = tamcliente + nclientes;

    fseek(arq, 0, SEEK_SET);
    fprintf(arq, "%d", tamcliente);
    fclose(arq);
    nclientes++;
}

/* Lista todos os clientes cadastrados no banco de dados.*/

void lista_clientes()
{

    FILE *num, *arq;

    int i, numclientes;

    num = fopen("num_clientes.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numclientes);

    //a variavel numclientes lê a quantidade de cadastros e ira especificar o tamanho de memoria necessario a ser alocado.
    fclose(num);

    arq = fopen("dados_clientes.bin", "rb+"); //abre o arq binario para leitura.
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c;

    c = (usuario *)calloc(numclientes, sizeof(usuario)); //aloca o ponteiro conforme o numero de cadastrados no arquivo.
    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        exit(0);
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq);

    if (numclientes == 0)
        printf("\n\n Sem usuarios cadastrados para exibir.\n");
    else
    {
        printf("\t \t ***************LISTA DE CLIENTES CADASTRADOS*****************\n \n");

        for (i = 0; i < numclientes; i++)
        {
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);
            printf("\n Nome: %s", (c + i)->nome);
            printf("\n CPF: %s", (c + i)->cpf);
            printf("\n Telefone: %s", (c + i)->telefone);
            printf("\n \n");
        }
    }
    fclose(arq);
    free(c); // libera o ponteiro ao termino da execucao da funcao.
}

/* função para encontrar um cliente a partir do cpf. */

usuario *buscar_cliente()
{

    int i, numclientes, negativo = 0;
    char cpf[12];

    FILE *num, *arq;

    num = fopen("num_clientes.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numclientes);
    fclose(num);

    /* Abre o arquivo e le o numero de cadastros armazenados
    no banco de dados ate o momento. */

    arq = fopen("dados_clientes.bin", "rb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c, *p = NULL;

    /* o ponteiro p salva as informacoes do usuario procurado e e
    retornado pela funcao. */

    c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.
    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //le o arquivo binario contendo os cadastros dos clientes e armazena no ponteiro c.

    printf("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for (i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)
        {
            printf("\n \n Usuario Encontrado. \n\n\n");
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);
            printf("\n Nome: %s", (c + i)->nome);
            printf("\n CPF: %s", (c + i)->cpf);
            printf("\n Telefone: %s", (c + i)->telefone);
            printf("\n \n");
            p = &c[i];
            negativo = 1;
        }
    }

    fclose(arq);

    if (negativo == 0)
        printf("\n \nNao encontramos o CPF informado.");

    return p;
    /* Como a funcao retorna p que armazena um endereco de c, nao podemos liberar a
    memoria alocada pelo ponteiro nessa funcao em especifico. */
}

/*--------------------------------------*/

void menu_alterar_cliente()
{
    int opcao = 0;
    while (opcao != 4 )
    {

        printf("\t \t \t \t \t \n _______________________________________Alterar Cadastro de Clientes_______________________________________ \n ");
        printf("\n\t\t\t\t\t1. Alterar Nome.\n");
        printf("\t \t \t \t \t2. Alterar CPF.\n");
        printf("\t \t \t \t \t3. Alterar Telefone de Contato.\n");
        printf("\t \t \t \t \t4. Voltar ao Menu de Cadastro de Clientes.\n");
        printf("\t \t \t \t \t5. Sair do Sistema.\n\n");
        printf(" Selecione uma opcao, por favor:\n");

        scanf("%d", &opcao);
        system("cls");

        switch (opcao)
        {
        case 1:
            system("cls");
            alterar_nome_cliente(); //funcao para alterar somente o nome do cliente no cadastro.
            system("cls");
            break;

        case 2:
            system("cls");
            alterar_cpf_cliente(); //funcao para alterar somente o cpf do cliente no cadastro.
            system("pause");
            system("cls");
            break;

        case 3:
            system("cls");
            alterar_telefone_cliente(); //funcao para alterar o telefone do cliente no cadastro.
            system("pause");
            system("cls");
            break;

        case 4:
            system("cls");
            printf("\n\n\n\n\t\t\t  Saindo do Menu de Alteracao de Clientes \n\n\n\n\n");
            system("cls");
            menu_usuario();
            break;

        case 5:
            system("cls");
            printf("\n\n\n\n\t\t\t  Saindo do Sistema. \n\n\n\n\n");
            exit(0);

        default:
        {

            printf("Opcao invalida, favor pressione <ENTER> para voltar ao menu principal");
            getchar();
            system("cls");
        }
        }
    }
}

/* função que altera o nome de um cadastro de cliente. */

void alterar_nome_cliente()
{

    int i, numclientes, negativo = 0;
    char cpf[12], nome[30];

    FILE *num, *arq;

    num = fopen("num_clientes.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numclientes);
    fclose(num);

    /* Abre o arquivo e le o numero de cadastros armazenados
    no banco de dados ate o momento. */

    arq = fopen("dados_clientes.bin", "rb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c;

    c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return (void)NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); // le o arquivo binario contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for (i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)
        {

            printf("\n \n Usuario Encontrado. \n\n\n");	//	Interacao com o usuario (Imprimindo o cliente que 
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);	//	sofrera alteracoes no cadastro)
            printf("\n Nome: %s", (c + i)->nome);
            printf("\n CPF: %s", (c + i)->cpf);
            printf("\n Telefone: %s\n\n", (c + i)->telefone);
            printf("Digite o novo nome: ");
            fflush(stdin);
            gets(nome);
            fflush(stdin);
            strcpy(((c + i)->nome), nome);
            negativo = 1;
            printf("\n\n Alteracao realizada com sucesso!\n");
            break;
        }
    }

    if (negativo == 0)		//	Informando o erro de pesquisa no CPF do cliente
        printf("\n \nNao encontramos o CPF informado.");

    arq = fopen("dados_clientes.bin", "wb+"); //abre o arquivo e subscreve o ponteiro c com o cadastro atualizado.
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }
    fwrite(c, sizeof(usuario), numclientes, arq);
    fclose(arq);
    free(c); //libera a memória alocada pelo ponteiro c.
}

/* função que altera o telefone no cadastro de um cliente. */

void alterar_telefone_cliente()
{

    int i, numclientes, negativo = 0;
    char cpf[12], telefone[22];

    FILE *num, *arq;

    num = fopen("num_clientes.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numclientes);
    fclose(num);

    /* Abre o arquivo e le o numero de cadastros armazenados
    no banco de dados ate o momento. */

    arq = fopen("dados_clientes.bin", "rb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c;

    c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return (void)NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //le o arquivo binario contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for (i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)			//	Interacao com o usuario: Imprimindo o 
        {							//	cliente encontrado e solicitando novos dados

            printf("\n \n Usuario Encontrado. \n\n\n");
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);
            printf("\n Nome: %s", (c + i)->nome);
            printf("\n CPF: %s", (c + i)->cpf);
            printf("\n Telefone: %s", (c + i)->telefone);
            printf("\n \n");
            printf("Digite o novo telefone: ");
            fflush(stdin);
            gets(telefone);
            fflush(stdin);
            strcpy(((c + i)->telefone), telefone);
            negativo = 1;
            printf("\n\n Alteracao realizada com sucesso!\n");
            break;
        }
    }

    if (negativo == 0)
        printf("\n \nNao encontramos o CPF informado.");

    arq = fopen("dados_clientes.bin", "wb+"); //abre o arquivo e subscreve o ponteiro c com o cadastro atualizado.
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }
    fwrite(c, sizeof(usuario), numclientes, arq);
    fclose(arq);
    free(c); //libera a memória alocada pelo ponteiro c.
}

/* função que altera o CPF no cadastro de um cliente. */

void alterar_cpf_cliente()
{

    int i, numclientes, negativo = 0;
    char cpf[12], novocpf[12];

    FILE *num, *arq;

    num = fopen("num_clientes.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numclientes);
    fclose(num);

    /* Abre o arquivo e le o numero de cadastros armazenados
    no banco de dados ate o momento. */

    arq = fopen("dados_clientes.bin", "rb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c;

    c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //le o arquivo binario contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for (i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)
        {

            printf("\n \n Usuario Encontrado. \n\n\n");			//	Interacao com o usuario: 
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);	
            printf("\n Nome: %s", (c + i)->nome);	//	Imprimindo o cliente encontrado e solicitando novos dados
            printf("\n CPF: %s", (c + i)->cpf);
            printf("\n Telefone: %s", (c + i)->telefone);
            printf("\n \n");
            printf("Digite o novo CPF: ");
            fflush(stdin);
            gets(novocpf);
            fflush(stdin);
            strcpy(((c + i)->cpf), novocpf);
            negativo = 1;
            printf("\n\n Alteracao realizada com sucesso!\n");
            break;
        }
    }

    if (negativo == 0)
        printf("\n \nNao encontramos o CPF informado.");

    arq = fopen("dados_clientes.bin", "wb+"); //abre o arquivo e subscreve o ponteiro c com o cadastro atualizado.
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }
    fwrite(c, sizeof(usuario), numclientes, arq);
    fclose(arq);
    free(c); 				//libera a memoria alocada pelo ponteiro c.
}

/* função que exclui o cadastro de um cliente. */

void excluir_cliente()
{

    int i, numclientes, negativo = 0;
    char cpf[12];

    FILE *num, *arq;

    num = fopen("num_clientes.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numclientes);
    fclose(num);

    /* Abre o arquivo e lê o número de cadastros armazenados
    no banco de dados até o momento. */

    arq = fopen("dados_clientes.bin", "rb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c;

    c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //le o arquivo binario contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o CPF do cliente a ser excluido: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);

    for (i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)		//	Interacao com o usuario: Imprimindo o cliente encontrado 
        {						//	e solicitando novos dados
            printf("\n \n Usuario Encontrado. \n\n\n");
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);
            printf("\n Nome: %s", (c + i)->nome);
            printf("\n CPF: %s", (c + i)->cpf);
            printf("\n Telefone: %s", (c + i)->telefone);
            printf("\n \n");
            negativo = 1;
            system("pause");

            while (i < numclientes - 1)
            {
                c[i] = c[i + 1];
                i++;
            }
            /* Subscreve todos os cadastros posteriores aquele informado. */
            printf("\n\n Alteracao realizada com sucesso!\n");
            break;
        }
    }

    numclientes--;

    if (negativo == 0)			//	Interacao com o usuario, informando que nao foi encontrado o CPF solicitado
        printf("\n \nNao encontramos o CPF informado.");

    arq = fopen("dados_clientes.bin", "wb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fseek(arq, 0, SEEK_SET);
    fwrite(c, sizeof(usuario), numclientes, arq); 	//subscreve e atualiza o banco de dados de cadastro de clientes.
    fclose(arq);

    num = fopen("num_clientes.txt", "w+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fseek(num, 0, SEEK_SET);
    fprintf(num, "%d", numclientes); //atualiza o numero de cadastros salvos no banco de dados.
    fclose(num);
    free(c);
}


/* FINAL DA PARTE DA GIOVANA */

/* INICIO DA PARTE DO THALES E DO FLAVIO */

void menu_produto()
{

    int verificador = 0;
    int i;


    while(verificador != 6) {		//	Menu de produtos, com as funcionalidades dessa parte
        printf("\t \t \t \t \t \n _________________________________________Menu de Produtos_________________________________________ \n ");
        printf("\t \t \t \t \t1. Inserir Produto Novo.\n");
        printf("\t \t \t \t \t2. Buscar Produto.\n");
        printf("\t \t \t \t \t3. Listar Produtos.\n");
        printf("\t \t \t \t \t4. Editar Produto.\n");
        printf("\t \t \t \t \t5. Excluir Cadastro.\n");
        printf("\t \t \t \t \t6. Voltar ao Menu Principal.\n");
        printf("\t \t \t \t \t7. Sair do Sistema.\n");
        printf(" Selecione uma opcao, por favor:\n");

        scanf(" %d", &verificador);
        switch (verificador)
        {
            case 1:
                system("cls");
                recebe_inf();
                break;
            case 2:
                system("cls");
                busca_prod();
                break;
            case 3:
                system("cls");
                lista_produtos();
                break;
            case 4:
                system("cls");
                altera_prod();
                break;
            case 5:
                system("cls");
                remover_prod();
                break;
            case 6:
                system("cls");
                printf("\n\n\n\n\t\t\t  Saindo do Menu de Produtos. \n\n\n\n\n");
                break;
            case 7:
                system("cls");
                printf("\n\n\n\n\t\t\t  Saindo do Sistema. \n\n\n\n\n");
                exit(0);
            default:
                system("cls");
                printf("\n\n\n\n\t\t\t  Operacao nao reconhecida. \n\n\n\n\n");
                break;
        }
    }
}

void criar_produto(cadastro_prod *prod) {	//	Cadastra um produto no sistema.

    printf("\nDigite as informacoes para o cadastro do produto:\n");	//	As informacoes solicitadas sao:
    fflush(stdin);
    printf("\nFornecedor:\t");					/*	Fornecedor 	*/
    gets(prod->fornecedor);

    printf("Tipo do produto:\t");				//	Tipo do produto
    gets(prod->tipo);

    printf("Identificador do produto(inteiro):\t");		//	Um numero de identificacao
    scanf("%d", &(prod->identificador));
    while ((prod->identificador) < 0 ) {				//	Regra de negocio: 
        printf("Identificador do produto deve ser um inteiro maior que 0:\t");	//	Verificacao do numero de identificacao
        scanf("%d", &(prod->identificador));
    }

    fflush(stdin);

    printf("Nome do produto:\t");					//	Solicita o nome do produto
    gets(prod->nome);

    printf("Quantidade:\t");						//	A quantidade que ja entrou em estoque, caso haja
    scanf("%d", &(prod->quantidade));
    fflush(stdin);

    printf("Preco (decimal com ponto):\t");			//	Preco do produto registrado
    scanf("%f", &(prod->preco));
    fflush(stdin);
}

void recebe_inf()
{ /*function para receber as infos de um produto novo e armazenar em um arquivo binario*/
    int i;
    FILE *arq;

    if ((arq = fopen("dados_farmacia.txt", "ab+")) == NULL)
    { /*verifica se o arquivo abre corretamente*/
        printf("Erro ao abrir o arquivo!");
    }

    cadastro_prod *prod = (cadastro_prod *)calloc(1, sizeof(cadastro_prod));
    criar_produto(prod);

    fseek(arq, 0, SEEK_END); /* armazenagem das infos no arquivo */
    fwrite((void *)prod, sizeof(cadastro_prod), 1, arq);
    fclose(arq);
    free(prod);
    arq_num_produtos(1);
}

void busca_prod()
{ /* function de busca por produto ja cadastrado no arquivo */

    int i, j = 0, verificador = 0, quantx;

    FILE *arq; /* verifica se o arquivo abre corretamente */
    FILE *numprod = fopen ("num_produtos.txt", "r+");


	if (numprod == NULL) {
    	printf ("\nErro ao abrir o arquivo!\n");
    }

    if ((arq = fopen("dados_farmacia.txt", "rb+")) == NULL)
    {
        printf("Erro ao abrir o arquivo!");
    }

    fseek (numprod, 0, SEEK_SET);
	fscanf (numprod, "%d", &quantx);
	fclose (numprod);

    fflush(stdin); /* limpa o buffer e recebe o codigo do produto para busca no arquivo */
    printf("Digite o codigo identificador do produto para buscar:\t");
    scanf("%d", &verificador);
    fflush(stdin);
    printf("\n\n");

    fseek(arq, 0, SEEK_SET); /* procura pelo produto no arquivo */
    fread(dados_prod, sizeof(cadastro_prod), quantx, arq);

    mostrar_prod(verificador, quantx);

    for (i = 0; i < quantx; i++)
    { /* laco for para alterar a quantidadde do produto ja cadastrado */
        if (verificador == dados_prod[i].identificador)
        {
            printf("Altere a quantidade do produto (atual = %d):\n", dados_prod[i].quantidade);
            scanf("%d", &dados_prod->quantidade);
            j++;
        }
    }
    if (j == 0)
    { /* laço de resposta para caso o produto não seja encontrado (não cadastrado ainda) */
        printf("Produto nao encontrado!\n\n");
    }
    fseek(arq, 0, SEEK_SET);
    fwrite(dados_prod, sizeof(struct cadastro_prod), 1, arq);
    fclose(arq);
}

void mostrar_prod(int verificador, int quantx)
{
    /* function de busca por produto já cadastrado no arquivo */
    FILE *arq; /* verifica se o arquivo abre corretamente */
    int j = 0, i = 0;
    if ((arq = fopen("dados_farmacia.txt", "rb+")) == NULL)
    {
        printf("Erro ao abrir o arquivo!");
    }

    fseek(arq, 0, SEEK_SET); /* procura pelo produto no arquivo */
    fread(dados_prod, sizeof(cadastro_prod), quantx, arq);

    for (i = 0; i < quantx; i++)
    { /* laço for para alterar a quantidadde do produto ja cadastrado */
        DBGi(dados_prod[i].identificador);
        if (verificador == dados_prod[i].identificador)
        {
            // printf("Altere a quantidade do produto (atual = %d):\n", dados_prod->quantidade);
            // scanf("%d", &dados_prod->quantidade);
            printf("\n _______________Produto:_______________ \n", i + 1);
            printf("\n Nome: %s", (dados_prod[i]).nome);
            printf("\n Fornecedor: %s", dados_prod[i].fornecedor);
            printf("\n Tipo: %s", dados_prod[i].tipo);
            printf("\n Identificador: %d", dados_prod[i].identificador);
            printf("\n Quantidade: %d", dados_prod[i].quantidade);
            printf("\n Preco: %.2f", dados_prod[i].preco);
            printf("\n \n");
            j++;
        }
    }
    if (j == 0)
    { /* laco de resposta para caso o produto não seja encontrado (não cadastrado ainda) */
        printf("Produto nao encontrado!\n\n");
    }
    fseek(arq, 0, SEEK_SET);
    fwrite(dados_prod, sizeof(cadastro_prod), 1, arq);
    fclose(arq);
}

void remover_prod() {
    int i, numprodutos, negativo = 0;
    int verificador;

    FILE *num, *arq;

    num = fopen("num_produtos.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo 1.\n");
        exit(0);
    }

    fscanf(num, "%d", &numprodutos);
    fclose(num);

    /* Abre o arquivo e lê o número de cadastros armazenados
    no banco de dados até o momento. */

    arq = fopen("dados_farmacia.txt", "rb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo 2.\n");
        exit(0);
    }

    cadastro_prod *c;

    c = (cadastro_prod *)calloc(numprodutos, sizeof(cadastro_prod)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(cadastro_prod), numprodutos, arq); 		//	lê o arquivo binário contendo os cadastros dos clientes e 
    fclose(arq);						//	armazena no ponteiro c

    printf("Digite o verificador do produto a ser totalmente excluido: ");
    fflush(stdin);
    scanf(" %d", &verificador);
    fflush(stdin);

    for (i = 0; i < numprodutos; i++)
    {
        if (c[i].identificador == verificador)
        {
            printf("\n _______________Produto:_______________ \n", i + 1);
            printf("\n Nome: %s", (c[i]).nome);
            printf("\n Fornecedor: %s", c[i].fornecedor);
            printf("\n Tipo: %s", c[i].tipo);
            printf("\n Identificador: %d", c[i].identificador);
            printf("\n Quantidade: %d", c[i].quantidade);
            printf("\n Preco: %.2f", c[i].preco);
            printf("\n \n");
            negativo = 1;
            system("pause");
            while (i < numprodutos - 1)
            {
                c[i] = c[i + 1];
                i++;
            }
            /* Subscreve todos os cadastros posteriores aquele informado. */
            printf("\n\n Alteracao realizada com sucesso!\n");
            break;
        }
    }

    numprodutos--;

    if (negativo == 0)
        printf("\n \nNao encontramos o CPF informado.");

    arq = fopen("dados_farmacia.txt", "wb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fseek(arq, 0, SEEK_SET);
    fwrite(c, sizeof(cadastro_prod), numprodutos, arq); //subscreve e atualiza o banco de dados de cadastro de clientes.
    fclose(arq);

    num = fopen("num_produtos.txt", "w+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fseek(num, 0, SEEK_SET);
    fprintf(num, "%d", numprodutos); //atualiza o número de cadastros salvos no banco de dados.
    fclose(num);
    free(c);
}

void altera_prod()
{ /*function para fazer qualquer alteração num dado produto já cadastrado*/
    int i, codigo;

    FILE *arq; /*verifica se o arquivo abre corretamente*/
    if ((arq = fopen("dados_farmacia.txt", "rb+")) == NULL)
    {
        printf("Erro ao abrir o arquivo!");
    } /*le e procura no arquivo o codigo do produto a ser alterado*/
    printf("Digite o codigo do produto a ser alterado:\n");
    scanf("%d", &codigo);

    fseek(arq, 0, SEEK_SET);
    fread(dados_prod, sizeof(struct cadastro_prod), 2, arq);

    for (i = 0; i < max; i++)
    { /*entrada dos novos dados do produto ja computado*/
        if (codigo == dados_prod[i].identificador)
        {
            fflush(stdin);
            printf("\nFornecedor[%d]:", i + 1);
            gets(dados_prod[i].fornecedor);

            printf("Tipo do produto[%d]:", i + 1);
            gets(dados_prod[i].tipo);

            printf("Identificador do produto[%d]:", i + 1);
            scanf("%d", &dados_prod[i].identificador);
            fflush(stdin);

            printf("Nome do produto[%d]:", i + 1);
            gets(dados_prod[i].nome);

            printf("Quantidade[%d]:", i + 1);
            scanf("%d", &dados_prod[i].quantidade);
            fflush(stdin);

            printf("Preco[%d]:", i + 1);
            scanf("%f", &dados_prod[i].preco);
            fflush(stdin);

            fseek(arq, 0, SEEK_SET);
            fwrite(dados_prod, sizeof(struct cadastro_prod), 1, arq);
            fclose(arq);
        }
    }
}

void painel()
{
    /*function do 'menu' do programa*/
    char verificador[5], anulador[5];
    int j, k;

    gets(verificador);
    fflush(stdin);

    if (stricmp(verificador, "nao") == 0)
    { /*limpa a tela conforme a vontade do usu�rio*/
        recebe_inf();
        printf("Para limpar a tela digite:[1]\n");
        scanf("%d", &j);
    }
    if (j == 1)
    {
        system("cls");
    }
    else
    { /*exibe as opções do usuario e espera por uma resposta, reagindo a qualquer entrada possivel*/
        for (k = 1; k < max; k++)
        {
            printf("Para alterar a quantidade do produto:[1]\n");
            printf("Para alterar o produto digite:       [2]\nPara limpar a tela digite:           [3]\n");
            scanf("%d", &j);

            if (j == 1)
            {
                busca_prod();
            }
            if (j == 2)
            {
                altera_prod();
            }
            if (j == 3)
            {
                system("cls");
            }
            else if (j > 3 || j < 1)
            {
                printf("\nEntrada inv�lida!\n");
                k--;
            }
        }
    }
    printf("O produto ja tem cadastro?\n");
    gets(anulador);
    stricmp("verficador", "anulador");
}

void lista_produtos() {
    FILE *num, *arq;

    int i, numprodutos;

    num = fopen("num_produtos.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numprodutos);
    fclose(num);


    arq = fopen("dados_farmacia.txt", "rb+"); //abre o arq para leitura.
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    cadastro_prod *c;

    c = (cadastro_prod *)calloc(numprodutos, sizeof(cadastro_prod)); //aloca o ponteiro conforme o num de cadastrados no arquivo.
    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(cadastro_prod), numprodutos, arq);

    if (numprodutos == 0)
        printf("\n\n Sem produtos cadastrados para exibir.\n");
    else
    {
        printf("\t \t ***************LISTA DE PRODUTOS CADASTRADOS*****************\n \n");

        for (i = 0; i < numprodutos; i++)
        {
            printf("\n _______________Cadastro:_______________ \n");
            printf("\n Nome: %s", (c + i)->nome);
            printf("\n Fornecedor: %s", (c + i)->fornecedor);
            printf("\n Tipo: %s", (c + i)->tipo);
            printf("\n Identificador: %d", (c + i)->identificador);
            printf("\n Quantidade: %d", (c + i)->quantidade);
            printf("\n Preco: %.2f", (c + i)->preco);
            printf("\n \n");
        }
    }
    fclose(arq);
    free(c); // libera o ponteiro ao término da execução da função.
}

void arq_num_produtos(int nprodutos)
{

    FILE *arq;
    unsigned int tamprodutos = 0;
    arq = fopen("num_produtos.txt", "r+");

    fseek(arq, 0, SEEK_SET);
    fscanf(arq, "%d", &tamprodutos);

    tamprodutos = tamprodutos + 1;

    fseek(arq, 0, SEEK_SET);
    fprintf(arq, "%d", tamprodutos);
    fclose(arq);
}

cadastro_prod *busca_prod_retorno(int identificador){
    int quantx, i, j = 0;

    FILE *arq; /* verifica se o arquivo abre corretamente */
    FILE *numprod = fopen("num_produtos.txt", "r+");

    if (numprod == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
    }


    fseek(numprod, 0, SEEK_SET);
    fscanf(numprod, "%d", &quantx);
    fclose(numprod);
    
    if ((arq = fopen("dados_farmacia.txt", "rb+")) == NULL)
    {
        printf("Erro ao abrir o arquivo!");
    }

    fseek(arq, 0, SEEK_SET); /* procura pelo produto no arquivo */
    fread(dados_prod, sizeof(cadastro_prod), quantx, arq);
    cadastro_prod *produto = (cadastro_prod *)malloc(2*sizeof(cadastro_prod));
    

    for (i = 0; i < quantx; i++)
    { /* laco for para alterar a quantidadde do produto ja cadastrado */
        if (identificador == dados_prod[i].identificador)
        {

            strncpy(produto->fornecedor, dados_prod[i].fornecedor, maxi * sizeof(char));
            strncpy(produto->nome, dados_prod[i].nome, maxi * sizeof(char));
            strncpy(produto->tipo, dados_prod[i].tipo, maxi * sizeof(char));
            produto->identificador = dados_prod[i].identificador;
            produto->preco = dados_prod[i].preco;
            produto->quantidade = dados_prod[i].quantidade;
            j++;
        }
    }

    if (j == 0)
    { /* laço de resposta para caso o produto não seja encontrado (não cadastrado ainda) */
        printf("Produto nao encontrado!\n\n");
        return NULL;
    }
    fseek(arq, 0, SEEK_SET);
    fwrite(dados_prod, sizeof(cadastro_prod), 1, arq);
    fclose(arq);

    return produto;
}

/*	Parte de fluxo (entrada e saída de produtos)	(João Vitor)	*/
//	Falta a parte do carrinho de compras...

void menu_fluxo()
{

    int controller = 0;		//	Variavel de controle e menu referenciando as devidas funcoes selecionadas

    printf("\n\nO que deseja fazer? \n\n1. Registrar entrada de produtos \n");
    printf("2. Registrar saida (venda) de produtos \n0. Retornar ao menu principal.\n\n");
    scanf("%d", &controller);

    switch (controller)
    {
        case 1:
            entrada_de_produto();
            break;

        case 2:
            saida_de_produto();
            break;

        case 0:
        	system ("cls");
            break;

        default:
            printf("Entrada de dados invalida. Retornando ao menu principal...");
    }
}

void saida_de_produto()
{
	usuario *cliente_cadastro;
    char stringzinha[30], controller[4], controller2 = '0', cpf_do_cliente[12];
    int posicao_do_produto, quantia, restante, quantx;
    FILE *arq = fopen("dados_farmacia.txt", "rb+");				//	Abrir o arquivo com os dados dos produtos
    FILE *num_produtos = fopen ("num_produtos.txt", "rb+");		//	Abrir o arquivo com o numero de produtos cadastrados

    if (arq == NULL) {
    	printf ("\nErro ao abrir o arquivo dados_farmacia.txt\n");	//	Verificacoes de abertura
    	exit(1);
    }

    if (num_produtos == NULL) {
    	printf ("\nErro ao abrir o arquivo num_produtos.txt\n");
    	exit(1);
    }

	fseek(num_produtos, 0, SEEK_SET);	//	Lendo o arquivo e armazenando a quantia de produtos na variavel quantx
	fread (&quantx, sizeof(int), 1, num_produtos);
	fclose (num_produtos);				//	Ja fechando o arquivo

    fseek(arq, 0, SEEK_SET);				//	Armazenando os dados dos produtos na variavel dados_prod
    fread (dados_prod, sizeof(cadastro_prod), quantx, arq);
    fclose (arq);							//	Ja fechando o arquivo

	system("cls");
	fflush (stdin);
    printf("\nO cliente comprador possui cadastro? sim/nao\n");
    gets(controller);
	fflush (stdin);

    if (stricmp(controller, "nao") == 0) {		/* 	Cadastra o cliente	*/
    	printf ("\nRealizando o cadastro do cliente, para prosseguir a venda...\n");
        cliente_cadastro = alocar_cliente(1); 		//	aloca um ponteiro usuario para cadastro.
        cliente_cadastro = inserir_cliente();       //	armazena as informacoes de entrada de cadastro.
        arquivar_cliente(cliente_cadastro);         // 	salva as informacoes do ponteiro no arquivo binario.
        arq_num_clientes(1);                  		// 	atualiza o numero de cadastros em um arquivo txt.
        system("cls");

        strcpy (cpf_do_cliente, cliente_cadastro->cpf);	//	Salvando o cpf do cliente recem cadastrado na nossa variavel de cpf

        printf("Digite o nome do produto que foi vendido\n\n");
        gets(stringzinha);

        posicao_do_produto = busca_de_produtos(stringzinha);
        if (posicao_do_produto != (int)NULL)
        { //	Verificacao de sucesso ao encontrar o produto com determinado nome

            printf("\nQuantas unidades desse produto devem ser retiradas do sistema?\n");
            scanf("%d", &quantia);
            fflush(stdin);

            if (dados_prod[posicao_do_produto].quantidade < quantia)	//	Informando sobre a regra de negocio:
            {								//	"Nao ha produtos suficientes para a venda"
                printf("\nNao ha produtos o suficiente em estoque para concluir a venda. \n");
                printf("Atualmente, existem apenas %d produtos em estoque.\n", dados_prod[posicao_do_produto].quantidade);
		printf ("\n1. Vender o estoque inteiro.\n2. Retornar ao menu\n");
                scanf("%c", &controller2);	//	E possivel vender o que se tem ou cancelar a venda.
                fflush(stdin);

                switch (controller2)
                {
                case '1':
                    restante = dados_prod[posicao_do_produto].quantidade;
                    dados_prod[posicao_do_produto].quantidade = 0;
                    break;
                case '2':
                    	//	Apenas atribuindo um valor diferente de 0 ao controller2, para que ele nao entre na verificacao 
			//	abaixo e nao seja impressa uma nota.
                    break;
                }
            }
            dados_prod[posicao_do_produto].quantidade -= quantia;

            printf("\nOperacao concluida com sucesso. \n");
            printf("Agora, a quantia de %s em estoque e: %d\n", 
		   dados_prod[posicao_do_produto].nome, dados_prod[posicao_do_produto].quantidade);

            arq = fopen("dados_farmacia.txt", "wb+");	//	Abrir o arquivo com os dados dos produtos para atualiza-los
            fwrite (dados_prod, quantx, sizeof(cadastro_prod), arq);
            fclose (arq);
        }
        else {
        	printf ("Produto nao encontrado.\n");
        	controller2 = '2';
        }

    }
    else if (stricmp(controller, "sim") == 0) {

        printf("\n\nDigite o CPF do cliente a que foi vendido.\n");	//	Iniciando a venda... (solicitacao de cpf
        gets(cpf_do_cliente);						// 	e nome/quantidade do produto vendido

        system("cls");
        printf("Digite o nome do produto que foi vendido\n\n");
        gets(stringzinha);

        posicao_do_produto = busca_de_produtos(stringzinha);
        if (posicao_do_produto != (int)NULL)
        { //	Verificacao de sucesso ao encontrar o produto com determinado nome

            printf("\nQuantas unidades desse produto devem ser retiradas do sistema?\n");
            scanf("%d", &quantia);
            fflush(stdin);

            if (dados_prod[posicao_do_produto].quantidade < quantia)	//	Informando e solicitando uso da regra de negocio
            {
                printf("\nNao ha produtos o suficiente em estoque para concluir a venda. \n");
                printf("Atualmente, existem apenas %d produtos em estoque.\n", dados_prod[posicao_do_produto].quantidade);
		printf("\n1. Vender o estoque inteiro.\n2. Retornar ao menu\n");
                scanf("%c", &controller2);
                fflush(stdin);

                switch (controller2)
                {
                case '1':
                    restante = dados_prod[posicao_do_produto].quantidade;
                    dados_prod[posicao_do_produto].quantidade = 0;
                    break;
                case '2':
		//	Apenas atribuindo um valor diferente de 0 ao controller2, para que ele nao entre na verificacao 
		//	abaixo e nao seja impressa uma nota.
                    break;
                }
            }
            dados_prod[posicao_do_produto].quantidade -= quantia;

            printf("\nOperacao concluida com sucesso. \n");
            printf("Agora, a quantia de %s em estoque e: %d\n", 
		   dados_prod[posicao_do_produto].nome, dados_prod[posicao_do_produto].quantidade);

			arq = fopen("dados_farmacia.txt", "wb+");	//Abrir o arquivo com os dados dos produtos para atualiza-los
            fwrite (dados_prod, quantx, sizeof(cadastro_prod), arq);
            fclose (arq);
		}
    }

    if (controller2 == '0')
    {   //	Controller2 e a variavel usada no caso em que nao ha produtos em estoque o suficiente para efetuar a venda.
        //	Logo, se houver algo nela, temos de emitir uma nota com a quantia que foi vendida, e nao a total pedida previamente

    	/*   	emitir_nota(&dados_prod[posicao_do_produto], quantia, cpf_do_cliente); 
	    	envia como argumentos, o endereco do vetor em que esta o produto, a quantia vendida e o cpf do cliente, 
		para a insercao na nota.	*/
    }
    else if (controller2 == '1')
    { /*	Dessa vez, envia como argumento a quantia que foi vendida. (Que havia em estoque)
    		emitir_nota(&dados_prod[posicao_do_produto], restante, cpf_do_cliente);	*/
    }
    	//	Se o controller for 2, significa que simplesmente retornamos ao menu e nao houve venda, logo, sem nota.
    else
    {
        printf("\n\nRetornando ao menu...\n\n");
        Sleep(2000);
        system("cls");
    }
}

void entrada_de_produto()
{ /*	A funcao de entrada de produtos busca por um produto ja existente/cadastrado e soma da quantidade
		em estoque, o valor digitado. funcionalidades intermediarias: busca_de_produtos.
		Fiz a funcao de busca retornando o valor int correspondente a posicao do produto no vetor de produtos.	*/

    char stringzinha[30];
    int posicao_do_produto, quantia, quantx;

    FILE *arq = fopen("dados_farmacia.txt", "rb+");	//	Abrir o arquivo com os dados dos produtos
    FILE *num_produtos = fopen ("num_produtos.txt", "rb+");	//	Abrir o arquivo com o numero de produtos cadastrados

    if (arq == NULL) {
    	printf ("\nErro ao abrir o arquivo dados_farmacia.txt\n");	//	Verificacoes de abertura
    	exit(1);
    }

    if (num_produtos == NULL) {
    	printf ("\nErro ao abrir o arquivo num_produtos.txt\n");
    	exit(1);
    }

	fseek(num_produtos, 0, SEEK_SET);		//	Armazenando a quantia de produtos na variavel quantx
	fread (&quantx, sizeof(int), 1, num_produtos);
	fclose (num_produtos);					//	Ja fechando o arquivo

    fseek(arq, 0, SEEK_SET);				//	Armazenando os dados dos produtos na variavel dados_prod
    fread (dados_prod, sizeof(cadastro_prod), quantx, arq);
    fclose (arq);							//	Ja fechando o arquivo

    system("cls");

    fflush (stdin);
    printf("Digite o nome do produto que chegou aos estoques\n\n");
    gets(stringzinha);
    fflush (stdin);

    posicao_do_produto = busca_de_produtos(stringzinha);
    if (posicao_do_produto != (int)NULL)
    { //	Verificacao de sucesso ao encontrar o produto com determinado nome

        printf("\nQuantas unidades desse produto devem ser adicionadas ao sistema?\n");
        scanf("%d", &quantia);
        fflush(stdin);

        dados_prod[posicao_do_produto].quantidade += quantia;

        printf("\nOperacao concluida com sucesso. \n");
        printf("Agora, a quantia de %s em estoque e: %d\n", 
	       dados_prod[posicao_do_produto].nome, dados_prod[posicao_do_produto].quantidade);

    	arq = fopen("dados_farmacia.txt", "wb+");	//	Abrir o arquivo com os dados dos produtos para atualiza-los
        fwrite (dados_prod, quantx, sizeof(cadastro_prod), arq);
        fclose (arq);
	}

    else
    {
        printf("\n\nRetornando ao menu...\n\n");
        Sleep(2000);
        system("cls");
    }
}

int busca_de_produtos(char *p)
{ /*	*p e o parametro que recebera a string enviada como argumento para a funcao	*/

    int posicao, i, controller = 0, quantx;

    FILE *arq = fopen("dados_farmacia.txt", "rb+");	//	Abrir o arquivo com os dados dos produtos
    FILE *num_produtos = fopen ("num_produtos.txt", "rb+");		//	Abrir o arquivo com o numero de produtos cadastrados

    if (arq == NULL) {
    	printf ("\nErro ao abrir o arquivo dados_farmacia.txt\n");	//	Verificacoes de abertura
    	exit(1);
    }

    if (num_produtos == NULL) {
    	printf ("\nErro ao abrir o arquivo num_produtos.txt\n");
    	exit(1);
    }

	fseek(num_produtos, 0, SEEK_SET);		//	Armazenando a quantia de produtos na variavel quantx
	fread (&quantx, sizeof(int), 1, num_produtos);
	fclose (num_produtos);					//	Ja fechando o arquivo

    fseek(arq, 0, SEEK_SET);				//	Armazenando os dados dos produtos do arquivo na variavel dados_prod
    fread (dados_prod, sizeof(cadastro_prod), quantx, arq);
    fclose (arq);							//	Ja fechando o arquivo


    for (i = 0; i < quantx; i++)
    { //	Inicia-se a verificacao pelo vetor de produtos, procurando algum produto do nome recebido por parametro pela funcao
        if (stricmp(dados_prod[i].nome, p) == 0)
        {
            posicao = i; //	A variavel posicao recebe a posicao do vetor em que esta o produto de nome procurado
            controller = 1;
            break;
        }
    }

    if (controller == 0)
    {
        printf("\nNao ha nenhum produto cadastrado com o nome: %s\n\n", p);
        Sleep(2000);
        return (int)NULL;
    }

    return posicao; //	A posicao do vetor e retornada
}
 /*
 Emissao de nota	(Ellian)
 */
void emitir_nota(compra *cp) {
    FILE * arq;
    int i;
    char salvarQuantidade[20], salvarPreco[20], salvarPrecoUnitario[20];

    for(i = 0; i < 5; i++)
        (cp->cpf)[i]='X';

    int hours = (int)time(NULL)/3600; 	// gerar timestamp para nota através das horas contadas desde 1 de janeiro de 1970
    char *timestamp = (char *)malloc(sizeof(char) * (1 + (int)log10(hours)));

    if(timestamp == NULL) {
        printf("Problema ao alocar memoria");
    }

    sprintf(timestamp, "%d", hours);
    if ((arq = fopen( strcat(strcat(strcat("nota-fiscal-", cp->cpf), timestamp), ".txt"), "w")) == NULL) // Erro é aqui(?)
    { // verifica se o arquivo abre corretamente
        printf("Erro ao abrir o arquivo!");
    }
    DBG;


    fseek(arq, 0, SEEK_SET);
    fwrite("NOTA FISCAL DE COMPRA\n Usuario:", sizeof("NOTA FISCAL DE COMPRA\n Usuario:"), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    fwrite(cp->nomeUser, sizeof(cp->nomeUser), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    fwrite("\tCPF:", sizeof("\tCPF:"), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    fwrite(cp->cpf, sizeof(cp->cpf), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    fwrite("\n\n\nProduto:\n\t", sizeof("\n\n\nProduto:\n\t"), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    sprintf(salvarQuantidade, "%d", cp->quantidadeProd);
    fwrite(salvarQuantidade, sizeof(salvarQuantidade), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    fwrite(" x \t", sizeof(" x \t"), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    sprintf(salvarPrecoUnitario, "%f", cp->valorProd);
    fwrite(salvarPrecoUnitario, sizeof(salvarPrecoUnitario), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    fwrite("\n\n\t\ttotal:", sizeof("\n\n\t\ttotal:"), 1, arq);
    fseek(arq, 0, SEEK_CUR);
    sprintf(salvarPreco, "%f", ((float)cp->quantidadeProd * cp->valorProd));
    fwrite(salvarPreco, sizeof(salvarPreco), 1, arq);
    fclose(arq);
}

 /*
 Funcoes relacionadas ao carrinho	(Ellian)
 */

void fazer_compra(usuario *user, cadastro_prod *produto, int quantidade, compra *cp) {
    strncpy(cp->nomeUser, user->nome, sizeof(cp->nomeUser));
    strncpy(cp->cpf, user->cpf, sizeof(cp->cpf));
    strncpy(cp->nomeProd, produto->nome, sizeof(cp->nomeProd));
    DBG;
    cp->codigoProd = produto->identificador;
    cp->valorProd = produto->preco;
    cp->quantidadeProd = quantidade;
}

carrinho *iniciar_carrinho() {
    carrinho *car = (carrinho *)calloc(1, sizeof(carrinho));

    int i;
    char cpfBuscar[12];

    printf("Insira o cpf do usuario: ");
    gets(cpfBuscar);
    int numclientes, negativo = 0;
    FILE *num, *arq;

    num = fopen("num_clientes.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numclientes);
    fclose(num);

    /* Abre o arquivo e le o numero de cadastros armazenados
    no banco de dados ate o momento. */

    arq = fopen("dados_clientes.bin", "rb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c, *p = NULL;

    /* o ponteiro p salva as informacoes do usuario procurado e o
    retornado pela funcao. */

    c = (usuario *)calloc(numclientes+1, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.
    if (c == NULL)
    {
        printf("Erro memoria insuficiente ");
        exit(0);
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //le o arquivo binario contendo os cadastros dos clientes e armazena no ponteiro c.

    for (i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpfBuscar) == 0)
        {
            p = &c[i];
            negativo = 1;
        }
    }

    fclose(arq);

    if (negativo == 0 || p == NULL){
        printf("\n \nNao encontramos o CPF informado. ");
        exit(0);
    }

    int numeroDeItens = 0;
    int identificador = 0;
    int quantidade = 0;
    cadastro_prod *prod = (cadastro_prod *)calloc(1, sizeof(cadastro_prod));
    do {
        if(numeroDeItens >= 30 ) {
            printf("Numero maximo de 30 itens diferentes por carinho\n");
            break;
        }

        printf("Digite o identificador do primeiro item(entre 0 para terminar): ");
        scanf("%d", &identificador);

        if(identificador <= 0){
            printf("Fechando carrinho... \n");
            break;
        }

        printf("Quantos desses item voce deseja? ");
        scanf("%d", &quantidade);

        if(quantidade <= 0)
        {
            printf("Nao e possível ter uma quantidade menor ou igual a 0\n");
            continue;
        }

        prod = busca_prod_retorno(identificador);     
        if(prod == NULL) {
            printf("Houve uma falha ao buscar o produto\n");
            return NULL;
        }
        
        fazer_compra(p, prod, quantidade, &(car->compras[numeroDeItens]) );
        DBG;  
        // strcpy(car->compras[numeroDeItens].nomeUser, p->nome);
        // strcpy(car->compras[numeroDeItens].cpf, p->cpf);
        // strcpy(car->compras[numeroDeItens].nomeProd, p->nome);
        // car->compras[numeroDeItens].codigoProd = prod->identificador;
        // car->compras[numeroDeItens].valorProd = prod->preco;
        // car->compras[numeroDeItens].quantidadeProd = quantidade;
        
        numeroDeItens++;
    } while (identificador != 0);

    car->numeroDeCompras = numeroDeItens;

    free(p);

    return car;
}

void menu_carrinho() {
    carrinho *c = (carrinho *)calloc(1, sizeof(carrinho));
    c = iniciar_carrinho();
    
    if(c == NULL) {
        printf("Erro ao finalizar o carrinho\0");
        return;
    }

    int i = 0;

    for(i = 0; i < c->numeroDeCompras; i++) {
        emitir_nota( &(c->compras[i]) ); //FIXME: erro na geração de nota
    }
}
