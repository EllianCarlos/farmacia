#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CLIENTES 1000

typedef struct {
char nome[30], telefone[22], cpf[12];  //struct com os dados dos clientes a serem cadastrados no sistema da farmacia.
} usuario;

usuario *alocar_cliente(int nclientes);
usuario *inserir_cliente();
usuario *buscar_cliente();
void menu_usuario();
void arquivar_cliente(usuario *);    // prototipo de funçoes utilizadas no menu de cadastro dos clientes.
void lista_clientes();
void arq_num_clientes(int );
void menu_alterar_cliente();
void alterar_nome_cliente();
void alterar_telefone_cliente();
void alterar_cpf_cliente();
void excluir_cliente();

int main (){
menu_usuario();
return 0;

}

/*--------------------------------------*/

void menu_usuario(){
    usuario *cliente_cadastro;

    int opcao=0, i, nclientes=1;
    while (opcao!=7 || opcao<7){

    printf("\t \t \t \t \t \n _________________________________________Cadastro de Clientes_________________________________________ \n ");
    printf("\n\t \t \t \t \t1. Novo Cadastro.\n");
    printf("\t \t \t \t \t2. Lista de Clientes.\n");
    printf("\t \t \t \t \t3. Procurar um Cliente.\n");
    printf("\t \t \t \t \t4. Editar Cadastro.\n");
    printf("\t \t \t \t \t5. Excluir Cadastro.\n");
    printf("\t \t \t \t \t6. Voltar ao Menu Principal.\n");
    printf("\t \t \t \t \t7. Sair do Sistema.\n");
    printf(" Selecione uma opcao, por favor:\n");

    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    	case 1:
            system("cls");
            cliente_cadastro = alocar_cliente(nclientes); //aloca um ponteiro usuario para cadastro.
            cliente_cadastro = inserir_cliente(); //armazena as informações de entrada de cadastro.
            arquivar_cliente(cliente_cadastro);  // salva as informações do ponteiro no arquivo binário.
            arq_num_clientes(nclientes);  // atualiza o número de cadastros em um arquivo txt.
            system("cls");
            break;

     	case 2:
            system("cls");
            lista_clientes(); //lista todos os clientes armazenados até o momento no arquivo.
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
            excluir_cliente(); // exclui um cliente do arquivo binário e atualiza o número total de cadastros no txt.
            system("cls");
			break;

    	case 6:
             printf("\n\n\n\n\t\t\t  Saindo do Menu de Cadastro de Clientes. \n\n\n\n\n");
             break;

    	case 7:
             system("cls");
             printf("\n\n\n\n\t\t\t  Saindo do Sistema. \n\n\n\n\n");
             exit(0);

   	 	default:	{

            printf("Opcao invalida, favor pressione <ENTER> para voltar ao menu principal");
            getchar();
            system("cls");
       		}
        }
	}
}

/* aloca um ponteiro struct usuario para entrada de um novo cadastro*/

usuario *alocar_cliente(int nclientes){
usuario *c;

c = (usuario *)calloc(nclientes, sizeof(usuario));
if (c == NULL){
    printf("Erro memoria insuficiente");
    return NULL;
    }

    return c;

}

/* insere os dados de entrada de cadastro e retorna o ponteiro preenchido. */

usuario *inserir_cliente(){

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

void arquivar_cliente(usuario *cliente_salvar){

FILE *arq;

if((arq=fopen("dados_clientes.bin", "ab+"))==NULL)
printf("\nErro abrindo arquivo.\n");


fseek(arq, 0, SEEK_END);
fwrite(cliente_salvar, sizeof(usuario), 1, arq);
fclose(arq);
}

/* esse arquivo em txt grava o numero de clientes cadastrados e é
usado por outras funções abaixo, ele se faz necessário para que se
saiba a quantidade de cadastros já salvos mesmo se o programa
for fechado e aberto novamente. */

void arq_num_clientes(int nclientes){

FILE *arq;
unsigned int tamcliente=0;
arq = fopen("num_clientes.txt", "r+");

fseek(arq, 0, SEEK_SET);
fscanf(arq, "%d", &tamcliente);

tamcliente = tamcliente+nclientes;

fseek(arq, 0, SEEK_SET);
fprintf(arq, "%d", tamcliente);
fclose(arq);
nclientes++;
}

/* Lista todos os clientes cadastrados no banco de dados.*/

void lista_clientes(){

FILE *num, *arq;

int numclientes;

num = fopen("num_clientes.txt", "r+");
if (num == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

fscanf(num, "%d", &numclientes);

//a variavel numclientes lê a quantidade de cadastros e irá especificar o tamanho de memória necessário a ser alocado.
fclose(num);


arq = fopen("dados_clientes.bin", "rb+"); //abre o arq binario para leitura.
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

usuario *c;

c = (usuario *)calloc(numclientes, sizeof(usuario)); //aloca o ponteiro conforme o número de cadastrados no arquivo.
if (c == NULL){
    printf("Erro memoria insuficiente");
    return NULL;
    }

fseek(arq, 0, SEEK_SET);
fread(c, sizeof(usuario), numclientes, arq);

 if(numclientes==0) printf("\n\n Sem usuarios cadastrados para exibir.\n");

else{
printf("\t \t ***************LISTA DE CLIENTES CADASTRADOS*****************\n \n");

for(int i=0; i<numclientes; i++){

  printf("\n _______________Cadastro[%d]:_______________ \n", i+1);
  printf("\n Nome: %s", (c+i)->nome);
  printf("\n CPF: %s", (c+i)->cpf);
  printf("\n Telefone: %s", (c+i)->telefone);
  printf("\n \n");
        }
    }
fclose(arq);
free(c); // libera o ponteiro ao término da execução da função.
}

/* função para encontrar um cliente a partir do cpf. */

usuario *buscar_cliente(){

    int numclientes, negativo=0;
    char cpf[12];

    FILE *num, *arq;

num = fopen("num_clientes.txt", "r+");
if (num == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

fscanf(num, "%d", &numclientes);
fclose(num);

/* Abre o arquivo e lê o número de cadastros armazenados
no banco de dados até o momento. */

arq = fopen("dados_clientes.bin", "rb+");
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

usuario *c, *p = NULL;

/* o ponteiro p salva as informações do usuário procurado e é
retornado pela função. */

c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.
if (c == NULL){
    printf("Erro memoria insuficiente");
    return NULL;
    }

fseek(arq, 0, SEEK_SET);
fread(c, sizeof(usuario), numclientes, arq); //lê o arquivo binário contendo os cadastros dos clientes e armazena no ponteiro c.

    printf ("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for(int i=0; i<numclientes; i++){
        if(strcmp(((c+i)->cpf), cpf) == 0){
        printf("\n \n Usuario Encontrado. \n\n\n");
        printf("\n _______________Cadastro[%d]:_______________ \n", i+1);
        printf("\n Nome: %s", (c+i)->nome);
        printf("\n CPF: %s", (c+i)->cpf);
        printf("\n Telefone: %s", (c+i)->telefone);
        printf("\n \n");
        p = &c[i];
        negativo = 1;
        }
    }

fclose(arq);
if(negativo==0) printf("\n \nNao encontramos o CPF informado.");
        return p;
/* Como a função retorna p que armazena um endereço de c, não podemos liberar a
memória alocada pelo ponteiro nessa função em específico. */
}

/*--------------------------------------*/

void menu_alterar_cliente(){

int opcao=0;
    while (opcao!=5 || opcao<5){

    printf("\t \t \t \t \t \n _______________________________________Alterar Cadastro de Clientes_______________________________________ \n ");
    printf("\n\t\t\t\t\t1. Alterar Nome.\n");
    printf("\t \t \t \t \t2. Alterar CPF.\n");
    printf("\t \t \t \t \t3. Alterar Telefone de Contato.\n");
    printf("\t \t \t \t \t4. Voltar ao Menu de Cadastro de Clientes.\n");
    printf("\t \t \t \t \t5. Sair do Sistema.\n\n");
    printf(" Selecione uma opcao, por favor:\n");

    scanf("%d", &opcao);
    system("cls");

    switch (opcao) {
    	case 1:
            system("cls");
            alterar_nome_cliente(); //função para alterar somente o nome do cliente no cadastro.
            system("cls");
            break;

     	case 2:
            system("cls");
            alterar_cpf_cliente(); //função para alterar somente o cpf do cliente no cadastro.
		    system("pause");
		    system("cls");
		    break;

      	case 3:
            system("cls");
            alterar_telefone_cliente(); //função para alterar o telefone do cliente no cadastro.
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

   	 	default:	{

            printf("Opcao invalida, favor pressione <ENTER> para voltar ao menu principal");
            getchar();
            system("cls");
       		}
        }
	}
}

/* função que altera o nome de um cadastro de cliente. */

void alterar_nome_cliente(){

    int numclientes, negativo=0;
    char cpf[12], nome[30];

    FILE *num, *arq;

num = fopen("num_clientes.txt", "r+");
if (num == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

fscanf(num, "%d", &numclientes);
fclose(num);

/* Abre o arquivo e lê o número de cadastros armazenados
no banco de dados até o momento. */

arq = fopen("dados_clientes.bin", "rb+");
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

usuario *c;

c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

if (c == NULL){
    printf("Erro memoria insuficiente");
    return NULL;
    }

fseek(arq, 0, SEEK_SET);
fread(c, sizeof(usuario), numclientes, arq); //lê o arquivo binário contendo os cadastros dos clientes e armazena no ponteiro c.
fclose(arq);

    printf ("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for(int i=0; i<numclientes; i++){
        if(strcmp(((c+i)->cpf), cpf) == 0){

        printf("\n \n Usuario Encontrado. \n\n\n");
        printf("\n _______________Cadastro[%d]:_______________ \n", i+1);
        printf("\n Nome: %s", (c+i)->nome);
        printf("\n CPF: %s", (c+i)->cpf);
        printf("\n Telefone: %s", (c+i)->telefone);
        printf("\n \n");
        printf("Digite o novo nome: ");
        fflush(stdin);
        gets(nome);
        fflush(stdin);
        strcpy(((c+i)->nome), nome);
        negativo = 1;
        printf("\n\n Alteracao realizada com sucesso!\n");
        break;
        }
    }

if(negativo==0) printf("\n \nNao encontramos o CPF informado.");

arq = fopen("dados_clientes.bin", "wb+"); //abre o arquivo e subscreve o ponteiro c com o cadastro atualizado.
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}
fwrite(c, sizeof(usuario), numclientes, arq);
fclose(arq);
free(c); //libera a memória alocada pelo ponteiro c.
}

/* função que altera o telefone no cadastro de um cliente. */

void alterar_telefone_cliente(){

    int numclientes, negativo=0;
    char cpf[12], telefone[22];

    FILE *num, *arq;

num = fopen("num_clientes.txt", "r+");
if (num == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

fscanf(num, "%d", &numclientes);
fclose(num);

/* Abre o arquivo e lê o número de cadastros armazenados
no banco de dados até o momento. */

arq = fopen("dados_clientes.bin", "rb+");
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

usuario *c;

c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

if (c == NULL){
    printf("Erro memoria insuficiente");
    return NULL;
    }

fseek(arq, 0, SEEK_SET);
fread(c, sizeof(usuario), numclientes, arq); //lê o arquivo binário contendo os cadastros dos clientes e armazena no ponteiro c.
fclose(arq);

    printf ("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for(int i=0; i<numclientes; i++){
        if(strcmp(((c+i)->cpf), cpf) == 0){

        printf("\n \n Usuario Encontrado. \n\n\n");
        printf("\n _______________Cadastro[%d]:_______________ \n", i+1);
        printf("\n Nome: %s", (c+i)->nome);
        printf("\n CPF: %s", (c+i)->cpf);
        printf("\n Telefone: %s", (c+i)->telefone);
        printf("\n \n");
        printf("Digite o novo telefone: ");
        fflush(stdin);
        gets(telefone);
        fflush(stdin);
        strcpy(((c+i)->telefone), telefone);
        negativo = 1;
        printf("\n\n Alteracao realizada com sucesso!\n");
        break;
        }
    }

if(negativo==0) printf("\n \nNao encontramos o CPF informado.");

arq = fopen("dados_clientes.bin", "wb+"); //abre o arquivo e subscreve o ponteiro c com o cadastro atualizado.
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}
fwrite(c, sizeof(usuario), numclientes, arq);
fclose(arq);
free(c); //libera a memória alocada pelo ponteiro c.
}

/* função que altera o CPF no cadastro de um cliente. */

void alterar_cpf_cliente(){

    int numclientes, negativo=0;
    char cpf[12], novocpf[12];

    FILE *num, *arq;

num = fopen("num_clientes.txt", "r+");
if (num == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

fscanf(num, "%d", &numclientes);
fclose(num);

/* Abre o arquivo e lê o número de cadastros armazenados
no banco de dados até o momento. */

arq = fopen("dados_clientes.bin", "rb+");
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

usuario *c;

c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

if (c == NULL){
    printf("Erro memoria insuficiente");
    return NULL;
    }

fseek(arq, 0, SEEK_SET);
fread(c, sizeof(usuario), numclientes, arq); //lê o arquivo binário contendo os cadastros dos clientes e armazena no ponteiro c.
fclose(arq);

    printf ("Digite o CPF do cliente a ser buscado: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);
    for(int i=0; i<numclientes; i++){
        if(strcmp(((c+i)->cpf), cpf) == 0){

        printf("\n \n Usuario Encontrado. \n\n\n");
        printf("\n _______________Cadastro[%d]:_______________ \n", i+1);
        printf("\n Nome: %s", (c+i)->nome);
        printf("\n CPF: %s", (c+i)->cpf);
        printf("\n Telefone: %s", (c+i)->telefone);
        printf("\n \n");
        printf("Digite o novo CPF: ");
        fflush(stdin);
        gets(novocpf);
        fflush(stdin);
        strcpy(((c+i)->cpf), novocpf);
        negativo = 1;
        printf("\n\n Alteracao realizada com sucesso!\n");
        break;
        }
    }

if(negativo==0) printf("\n \nNao encontramos o CPF informado.");

arq = fopen("dados_clientes.bin", "wb+"); //abre o arquivo e subscreve o ponteiro c com o cadastro atualizado.
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}
fwrite(c, sizeof(usuario), numclientes, arq);
fclose(arq);
free(c); //libera a memória alocada pelo ponteiro c.
}

/* função que exclui o cadastro de um cliente. */

void excluir_cliente(){

    int numclientes, negativo=0;
    char cpf[12];

    FILE *num, *arq;

num = fopen("num_clientes.txt", "r+");
if (num == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

fscanf(num, "%d", &numclientes);
fclose(num);

/* Abre o arquivo e lê o número de cadastros armazenados
no banco de dados até o momento. */

arq = fopen("dados_clientes.bin", "rb+");
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}

usuario *c;

c = (usuario *)calloc(numclientes, sizeof(usuario)); // aloca um ponteiro para armazenar os cadastros lidos do arquivo.

if (c == NULL){
    printf("Erro memoria insuficiente");
    return NULL;
    }

fseek(arq, 0, SEEK_SET);
fread(c, sizeof(usuario), numclientes, arq); //lê o arquivo binário contendo os cadastros dos clientes e armazena no ponteiro c.
fclose(arq);

    printf ("Digite o CPF do cliente a ser excluido: ");
    fflush(stdin);
    gets(cpf);
    fflush(stdin);

    for(int i=0; i<numclientes; i++){
        if(strcmp(((c+i)->cpf), cpf) == 0){

        printf("\n \n Usuario Encontrado. \n\n\n");
        printf("\n _______________Cadastro[%d]:_______________ \n", i+1);
        printf("\n Nome: %s", (c+i)->nome);
        printf("\n CPF: %s", (c+i)->cpf);
        printf("\n Telefone: %s", (c+i)->telefone);
        printf("\n \n");
        negativo = 1;
        system("pause");
        while(i < numclientes-1){
            c[i] = c[i+1];
            i++;
        }
/* Subscreve todos os cadastros posteriores àquele informado. */

        printf("\n\n Alteracao realizada com sucesso!\n");
        break;
        }
    }
numclientes--;

if(negativo==0) printf("\n \nNao encontramos o CPF informado.");

arq = fopen("dados_clientes.bin", "wb+");
if (arq == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}
fseek(arq, 0, SEEK_SET);
fwrite(c, sizeof(usuario), numclientes, arq); //subscreve e atualiza o banco de dados de cadastro de clientes.
fclose(arq);

num = fopen("num_clientes.txt", "w+");
if (num == NULL){
    printf("Erro na abertura do arquivo.\n");
    exit(0);
}
fseek(num, 0, SEEK_SET);
fprintf(num, "%d", numclientes); //atualiza o número de cadastros salvos no banco de dados.
fclose(num);
free(c);
}
