#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CLIENTES 1000
#define maxi 30
#define max 2

int n = 1; //Usada p/ id a quantidade de usuarios já cadastrados e iniciar o vetor na posi��o livre atual el na fun��o lista //


// Criacao dos tipos que serao utilizados
typedef struct cadastro_prod
{                                                  /*struct com as infos do produto*/
    char tipo[maxi], nome[maxi], fornecedor[maxi]; /*tipo = natureza do produto*/
    float preco;
    int identificador, quantidade; /*identificador = numero do produto para sua computa��o no software interno*/
} cadastro_prod;

typedef struct usuario
{
    char nome[30], telefone[22], cpf[12]; //struct com os dados dos clientes a serem cadastrados no sistema da farmacia.
} usuario;


// Declaracao das funcoes que serão utilizados
usuario *alocar_cliente(int nclientes);
usuario *inserir_cliente();
usuario *buscar_cliente();
void menu_usuario();
void arquivar_cliente(usuario *);    // prototipo de fun�oes utilizadas no menu de cadastro dos clientes.
void lista_clientes();
void arq_num_clientes(int );
void menu_alterar_cliente();
void alterar_nome_cliente();
void alterar_telefone_cliente();
void alterar_cpf_cliente();
void excluir_cliente();
usuario pesquisa_cliente(usuario *cadastro_cliente);
void menu_usuario();
// void menu_usuario(usuario *cadastro_cliente);
void menu_produto();
void menu_fluxo();
int busca_de_produtos(char *p);
void entrada_de_produto();
void saida_de_produto();
void emitir_nota(cadastro_prod *produto_vendido, int numvendido, char *cpfzinho);

usuario cadastro_cliente[max]; //	Defini��o das estruturas de dados.
cadastro_prod dados_prod[max]; //	Est�o como vari�veis globais, enquanto ainda n�o usamos arquivos de texto


int main() {
    // Funcao principal

    int controller = 0;


    while (1)
    {

        printf("Bem vindo ao sistema gerencial da farmacia.\n\nQual menu deseja utilizar?\n\n");
        printf("1. Clientes \n2. Produtos \n3. Fluxo de mercadorias\n\n0. Sair do programa\n\n");
        scanf("%d", &controller);
        fflush(stdin);
        switch (controller)
        {
            case 1:
                menu_usuario(&cadastro_cliente[0]);
                break;
            case 2:
                menu_produto();
                // painel();
                break;
            case 3:
                // menu_fluxo();
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
                cliente_cadastro = inserir_cliente();         //armazena as informa��es de entrada de cadastro.
                arquivar_cliente(cliente_cadastro);           // salva as informa��es do ponteiro no arquivo bin�rio.
                arq_num_clientes(nclientes);                  // atualiza o n�mero de cadastros em um arquivo txt.
                system("cls");
                break;

            case 2:
                system("cls");
                lista_clientes(); //lista todos os clientes armazenados at� o momento no arquivo.
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
                excluir_cliente(); // exclui um cliente do arquivo bin�rio e atualiza o n�mero total de cadastros no txt.
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

/* aloca um ponteiro struct usuario para entrada de um novo cadastro*/

usuario *alocar_cliente(int nclientes)
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

/* insere os dados de entrada de cadastro e retorna o ponteiro preenchido. */

usuario *inserir_cliente()
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

/* esse arquivo em txt grava o numero de clientes cadastrados e �
usado por outras fun��es abaixo, ele se faz necess�rio para que se
saiba a quantidade de cadastros j� salvos mesmo se o programa
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

    int numclientes;

    num = fopen("num_clientes.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numclientes);

    //a variavel numclientes lê a quantidade de cadastros e ir� especificar o tamanho de mem�ria necess�rio a ser alocado.
    fclose(num);

    arq = fopen("dados_clientes.bin", "rb+"); //abre o arq binario para leitura.
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c;

    c = (usuario *)calloc(numclientes, sizeof(usuario)); //aloca o ponteiro conforme o n�mero de cadastrados no arquivo.
    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq);

    if (numclientes == 0)
        printf("\n\n Sem usuarios cadastrados para exibir.\n");
    else
    {
        printf("\t \t ***************LISTA DE CLIENTES CADASTRADOS*****************\n \n");

        for (int i = 0; i < numclientes; i++)
        {
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);
            printf("\n Nome: %s", (c + i)->nome);
            printf("\n CPF: %s", (c + i)->cpf);
            printf("\n Telefone: %s", (c + i)->telefone);
            printf("\n \n");
        }
    }
    fclose(arq);
    free(c); // libera o ponteiro ao t�rmino da execu��o da fun��o.
}

/* função para encontrar um cliente a partir do cpf. */

usuario *buscar_cliente()
{

    int numclientes, negativo = 0;
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

    /* Abre o arquivo e l� o n�mero de cadastros armazenados
    no banco de dados at� o momento. */

    arq = fopen("dados_clientes.bin", "rb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    usuario *c, *p = NULL;

    /* o ponteiro p salva as informa��es do usu�rio procurado e �
    retornado pela fun��o. */

    c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.
    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //l� o arquivo bin�rio contendo os cadastros dos clientes e armazena no ponteiro c.

    printf("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for (int i = 0; i < numclientes; i++)
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
    /* Como a fun��o retorna p que armazena um endere�o de c, n�o podemos liberar a
    mem�ria alocada pelo ponteiro nessa fun��o em espec�fico. */
}

/*--------------------------------------*/

void menu_alterar_cliente()
{
    int opcao = 0;
    while (opcao != 5 || opcao < 5)
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
            alterar_nome_cliente(); //fun��o para alterar somente o nome do cliente no cadastro.
            system("cls");
            break;

        case 2:
            system("cls");
            alterar_cpf_cliente(); //fun��o para alterar somente o cpf do cliente no cadastro.
            system("pause");
            system("cls");
            break;

        case 3:
            system("cls");
            alterar_telefone_cliente(); //fun��o para alterar o telefone do cliente no cadastro.
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

    int numclientes, negativo = 0;
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

    /* Abre o arquivo e l� o n�mero de cadastros armazenados
    no banco de dados at� o momento. */

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
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //l� o arquivo bin�rio contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for (int i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)
        {

            printf("\n \n Usuario Encontrado. \n\n\n");
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);
            printf("\n Nome: %s", (c + i)->nome);
            printf("\n CPF: %s", (c + i)->cpf);
            printf("\n Telefone: %s", (c + i)->telefone);
            printf("\n \n");
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

/* função que altera o telefone no cadastro de um cliente. */

void alterar_telefone_cliente()
{

    int numclientes, negativo = 0;
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

    /* Abre o arquivo e l� o n�mero de cadastros armazenados
    no banco de dados at� o momento. */

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
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //l� o arquivo bin�rio contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for (int i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)
        {

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

    int numclientes, negativo = 0;
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

    /* Abre o arquivo e l� o n�mero de cadastros armazenados
    no banco de dados at� o momento. */

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
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //l� o arquivo bin�rio contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for (int i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)
        {

            printf("\n \n Usuario Encontrado. \n\n\n");
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);
            printf("\n Nome: %s", (c + i)->nome);
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
    free(c); //libera a mem�ria alocada pelo ponteiro c.
}

/* função que exclui o cadastro de um cliente. */

void excluir_cliente()
{

    int numclientes, negativo = 0;
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
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(usuario), numclientes, arq); //l� o arquivo bin�rio contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o CPF do cliente a ser excluido: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);

    for (int i = 0; i < numclientes; i++)
    {
        if (strcmp(((c + i)->cpf), cpf) == 0)
        {
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

    if (negativo == 0)
        printf("\n \nNao encontramos o CPF informado.");

    arq = fopen("dados_clientes.bin", "wb+");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fseek(arq, 0, SEEK_SET);
    fwrite(c, sizeof(usuario), numclientes, arq); //subscreve e atualiza o banco de dados de cadastro de clientes.
    fclose(arq);

    num = fopen("num_clientes.txt", "w+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fseek(num, 0, SEEK_SET);
    fprintf(num, "%d", numclientes); //atualiza o n�mero de cadastros salvos no banco de dados.
    fclose(num);
    free(c);
}


/* FINAL DA PARTE DA GIOVANA */

/* INICIO DA PARTE DO THALES E DO FLAVIO */

void menu_produto()
{

    int verificador = 0;
    int i;


    while(verificador != 6) {
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
                printf("\n\n\n\n\t\t\t  Opção não reconhecida. \n\n\n\n\n");
                break;
        }
    }
}

void criar_produto(cadastro_prod *prod) {

    printf("\nDigite as informacoes para o cadastro do produto:\n");
    fflush(stdin);
    printf("\nFornecedor:\t");
    gets(prod->fornecedor);

    printf("Tipo do produto:\t");
    gets(prod->tipo);

    printf("Identificador do produto(inteiro):\t");
    scanf("%d", &(prod->identificador));
    fflush(stdin);

    printf("Nome do produto:\t");
    gets(prod->nome);

    printf("Quantidade:\t");
    scanf("%d", &(prod->quantidade));
    fflush(stdin);

    printf("Preco (decimal com ponto):\t");
    scanf("%f", &prod->preco);
    fflush(stdin);
}

void recebe_inf()
{ /*function para receber as infos de um produto novo e armazenar em um arquivo binario*/
    int i;
    int numero_de_prod = 0;
    FILE *arq;

    if ((arq = fopen("dados_farmacia.txt", "rb+")) == NULL)
    { /*verifica se o arquivo abre corretamente*/
        printf("Erro ao abrir o arquivo!");
    }

    printf("\nDeseja cadastrar quantos produtos DIFERENTES?\n");
    fflush(stdin);
    scanf("%d", &numero_de_prod);


    for (i = 0; i < numero_de_prod; i++)
    { /*laço for que pede as infos de um novo produto para cadastro*/
        cadastro_prod prod;
        printf("\nCadastrando produto de numero %d:\n", i+1);
        criar_produto(&prod);
        fseek(arq, 0, SEEK_CUR); /* armazenagem das infos no arquivo */
        fwrite((void *)&prod, sizeof(cadastro_prod), 1, arq);
    }

    fclose(arq);
    arq_num_produtos(numero_de_prod);
}

void busca_prod()
{ /* function de busca por produto já cadastrado no arquivo */

    int i, j = 0, verificador = 0;

    FILE *arq; /* verifica se o arquivo abre corretamente */

    if ((arq = fopen("dados_farmacia.txt", "rb+")) == NULL)
    {
        printf("Erro ao abrir o arquivo!");
    }

    fflush(stdin); /* limpa o buffer e recebe o codigo do produto para busca no arquivo */
    printf("Digite o codigo identificador do produto para buscar:\t");
    scanf("%d", &verificador);
    printf("\n\n");

    fseek(arq, 0, SEEK_SET); /* procura pelo produto no arquivo */
    fread(dados_prod, sizeof(struct cadastro_prod), 1, arq);

    mostrar_prod(verificador);

    for (i = 0; i < max; i++)
    { /* laço for para alterar a quantidadde do produto já cadastrado */
        if (verificador == dados_prod[i].identificador)
        {
            printf("Altere a quantidade do produto (atual = %d):\n", dados_prod->quantidade);
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

void mostrar_prod(int verificador)
{
    /* function de busca por produto já cadastrado no arquivo */
    FILE *arq; /* verifica se o arquivo abre corretamente */
    int j = 0, i = 0;
    if ((arq = fopen("dados_farmacia.txt", "rb+")) == NULL)
    {
        printf("Erro ao abrir o arquivo!");
    }

    fseek(arq, 0, SEEK_SET); /* procura pelo produto no arquivo */
    fread(dados_prod, sizeof(cadastro_prod), 1, arq);

    for (i = 0; i < max; i++)
    { /* laço for para alterar a quantidadde do produto já cadastrado */
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
    { /* laço de resposta para caso o produto não seja encontrado (não cadastrado ainda) */
        printf("Produto nao encontrado!\n\n");
    }
    fseek(arq, 0, SEEK_SET);
    fwrite(dados_prod, sizeof(struct cadastro_prod), 1, arq);
    fclose(arq);
}

void remover_prod() {
    int numprodutos, negativo = 0;
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
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(cadastro_prod), numprodutos, arq); //lê o arquivo binário contendo os cadastros dos clientes e armazena no ponteiro c.
    fclose(arq);

    printf("Digite o verificador do produto a ser totalmente excluido: ");
    fflush(stdin);
    scanf(" %d", &verificador);
    fflush(stdin);

    for (int i = 0; i < numprodutos; i++)
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
    } /*l� e procura no arquivo o codigo do produto a ser alterado*/
    printf("Digite o codigo do produto a ser alterado:\n");
    scanf("%d", &codigo);

    fseek(arq, 0, SEEK_SET);
    fread(dados_prod, sizeof(struct cadastro_prod), 2, arq);

    for (i = 0; i < max; i++)
    { /*entrada dos novos dados do produto j� computado*/
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

    int numprodutos;

    num = fopen("num_produtos.txt", "r+");
    if (num == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    fscanf(num, "%d", &numprodutos);

    //a variavel numclientes lê a quantidade de cadastros e irá especificar o tamanho de memória necessario a ser alocado.
    fclose(num);

    arq = fopen("dados_farmacia.txt", "rb+"); //abre o arq para leitura.
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(0);
    }

    cadastro_prod *c;

    c = (cadastro_prod *)calloc(numprodutos, sizeof(cadastro_prod)); //aloca o ponteiro conforme o número de cadastrados no arquivo.
    if (c == NULL)
    {
        printf("Erro memoria insuficiente");
        return NULL;
    }

    fseek(arq, 0, SEEK_SET);
    fread(c, sizeof(cadastro_prod), numprodutos, arq);

    if (numprodutos == 0)
        printf("\n\n Sem produtos cadastrados para exibir.\n");
    else
    {
        printf("\t \t ***************LISTA DE PRODUTOS CADASTRADOS*****************\n \n");

        for (int i = 0; i < numprodutos; i++)
        {
            printf("\n _______________Cadastro[%d]:_______________ \n", i + 1);
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
