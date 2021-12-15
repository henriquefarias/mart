#include <stdio.h>
#include <stdlib.h>
#include <conio.h.>
#include <locale.h>
#include <string.h>

/* Define o tamanho dos campos de texto +1 para o null terminator */
#define USERNAME_SIZE 60+1
#define PRONTUARIO_SIZE 8+1
#define PROD_NAME_SIZE 60+1
#define PROD_DESCR_SIZE 100+1

/* Tipos booleanos */
#define TRUE (!NULL)
#define FALSE NULL

/* Gera mensagens de debug */
#define DEBUG_MODE TRUE


/* Armazena informa��es dos usu�rios */
typedef struct
{
    char username[USERNAME_SIZE];
    char prontuario[PRONTUARIO_SIZE];

} USER;


/* Armazena informa��es sobre os produtos */
typedef struct
{
    int cod_prod;
    char nome[PROD_NAME_SIZE];
    char descricao[PROD_DESCR_SIZE];
    float peso;
    float custo;

} PRODUCT;


/* Armazena um n� individual da lista de usu�rios */
 struct USER_NODE
{
    int position; /* Posi��o que o n� ocupa na lista */
    USER data; /* Armazena um registro de usu�rio individual */
    struct USER_NODE *next; /* Endere�o do pr�ximo n�. O �ltimo n� da lista deve apontar para NULL */
};


/* Armazena um n� individual da lista de produtos */
struct PROD_NODE
{
    int position;
    PRODUCT data;
    struct PROD_NODE *next;
};


/* Lista de usu�rios */
typedef struct
{
    struct USER_NODE *head;
    struct USER_NODE *users;

} USER_LIST;


/* Lista de produtos */
typedef struct
{
    struct PROD_NODE *head;
    struct PROD_NODE *products;

} PROD_LIST;


/* ======================== PRODUTOS DISPON�VEIS ======================== */

PRODUCT prod_list[] =
{
    /* C�DIGO       NOME            DESCRI��O            PESO (KG) PRE�O */
    {   1,    "Contra fil�",        "Pre�o por kg",      1.0,      39.99},
    {   2,    "Ovo Caipira",        "12 unidades",       0.6,      7.50},
    {   3,    "Leite integral",     "Garrafa 1L",        1.0,      5.99},
    {   4,    "P�o franc�s",        "Pre�o por kg",      1.0,      5.55},
    {   5,    "Abacaxi",            "Pre�o por unidade", 0.8,      6.50},
    {   6,    "�lcool gel 70%",     "Frasco 500ml",      0.5,      7.25},
    {   7,    "Biscoito recheado",  "Pacote 200g",       0.2,      2.99},
    {   8,    "Chocolate ao leite", "Barra 200g",        0.2,      5.80}
};


/* ======================== VARI�VEIS GLOBAIS ======================== */

USER_LIST *users; /* Lista encadeada com registros de usu�rio */


/* ============= PROT�TIPOS DE FUN��ES ======================= */


void build_user_dat(void);

void load_users_dat(char *filename, USER_LIST *list);

void write_users_dat(char *filename, USER_LIST *list);

USER_LIST *build_user_list(int list_size);

// void busca_prontuario(char *prontuario, char tipo_busca);

void exit_program(void);

int file_exists(char *filename);

long int file_size(char *filename);

int get_size(USER_LIST *list);

struct USER_NODE *get_tail(USER_LIST *list);

void login(void);

void main_menu(void);

void not_implemented(void);

void print_users(USER_LIST *list);

int search(USER *list, char *username, char *prontuario, int pos_inicial, int pos_final);

void sort_list(USER_LIST *list);

void swap_users(USER *user1, USER *user2);

void validate_allocation(void *object);

void validate_file(FILE *file);


/* ============= CONSTRU��O DE FUN��ES ======================= */

/*  Cria uma lista encadeada e retorna um ponteiro para ela
    OBS: talvez seja poss�vel usar ponteiros gen�ricos, assim n�o � necess�rio fazer uma fun��o separada para a lista de produtos. */
USER_LIST *build_user_list(int list_size)
{
    int i;
    USER_LIST *list;
    struct USER_NODE *temp_user;

    if (list_size > 0)
    {
        /* Aloca a lista propriamente dita */
        list = (USER_LIST *) malloc(sizeof(USER_LIST));
        validate_allocation(list);

        /* Aloca os n�s da lista */
        list->users = (struct USER_NODE *) malloc(list_size * sizeof(struct USER_NODE));
        validate_allocation(list->users);

        /*  Ajusta a posi��o inicial.
            Protip: O nome de um array em C � o endere�o do primeiro elemento (ou seja, vect == &vect[0]). */
        list->head = list->users;

        /* Ajusta os �ndices e ponteiros */
        temp_user = list->head;

        for (i = 0; i < list_size; i++)
        {
            temp_user->position = i;

            /* Ao atingir o �ltimo item da lista, ajustamos seu ponteiro para NULL */
            if (i == list_size - 1)
                temp_user->next = NULL;

            /* Do contr�rio, incrementamos o endere�o. Como estamos lidando com valores cont�nuos na mem�ria, basta somar 1 ao endere�o anterior. */
            else
                temp_user->next = temp_user + 1;

            /* Aqui seria poss�vel usar temp_user++, mas � melhor seguir o ponteiro criado anteriormente. */
            temp_user = temp_user->next;
        }

        return(list);
    }
}


/* Carrega dados em mem�ria e inicializa o programa */
void initialize(void)
{
    int list_size;  /* Tamanho da lista de usu�rios. Este valor depende do tamanho do arquivo USU�RIOS.DAT. */

    /* Verifica se o arquivo USUARIOS.DAT j� existe. Caso contr�rio, cria um novo arquivo com os registros padr�o. */
    if (!file_exists("USUARIOS.DAT"))
    {
        printf("Criando arquivo USUARIOS.DAT com registros padr�o.\n");
        build_user_dat();

        /* Verifica se o arquivo foi gerado corretamente */
        if (file_exists("USUARIOS.DAT"))
        {
            printf("Arquivo USUARIOS.DAT criado com sucesso.\n");
            printf("Tamanho do USUARIOS.DAT: %d bytes\n", file_size("USUARIOS.DAT"));
        }

        else
        {
            system("cls");
            printf("*** Erro ao criar arquivo USUARIOS.DAT ***");
            getch();
            exit(EXIT_FAILURE);
        }
    }

    /* Aloca lista e carrega dados do arquivo USUARIOS.DAT na mem�ria */
    list_size = (file_size("USUARIOS.DAT")/sizeof(USER));

    users = build_user_list(list_size);
    validate_allocation(users);

    load_users_dat("USUARIOS.DAT", users);
    validate_allocation(users);

    print_users(users);
}

/* Retorna o tamanho de uma lista */
/* TODO: passar um void pointer e o tipo da lista. Dessa forma n�o � preciso fazer outra fun��o para a lista de produtos.
    ex: int get_size(void *list, char list_type) */

int get_size(USER_LIST *list)
{
    int size = 0;
    struct USER_NODE *current_node = list->head;

    while (TRUE)
    {

        if (current_node == NULL) /* Lista possui zero elementos */
            /* Aqui � poss�vel usar um break ao inv�s de return. Como o valor size foi inicializado como 0, ao sair do loop a fun��o automaticamente retorna 0.*/
            // return(0);
            break;

        else
        {
            size++;

            /* Sai do loop ao atingir o fim da lista */
            if (current_node->next == NULL)
                break;

            else
                current_node = current_node->next;
        }
    }

    return(size);
}


/* Gera arquivo DAT com usu�rios pr�-definidos. */
void build_user_dat(void)
{
    int i, list_size;
    FILE *userDAT;
    USER default_users[] =
    {
        /*          NOME                            PRONTU�RIO */

        {"Domingos Lucas Latorre de Oliveira",      "CJ146456"},
        {"Leandro Pinto Santana",                   "CP220383"},
        {"Rodrigo Ribeiro de Oliveira",             "RG134168"},
        {"Andre Luiz da Silva",                     "SP030028"},
        {"Claudia Miyuki Werhmuller",               "SP030041"},
        {"Claudete de Oliveira Alves",              "SP03020X"},
        {"Francisco Verissimo Luciano",             "SP030247"},
        {"Luk Cho Man",                             "SP060380"},
        {"Ivan Francolin Martinez",                 "SP060835"},
        {"Joao Vianei Tamanini",                    "SP060914"},
        {"Jose Oscar Machado Alexandre",            "SP070038"},
        {"Jose Braz de Araujo",                     "SP070385"},
        {"Paulo Roberto de Abreu",                  "SP070816"},
        {"Eurides Balbino da Silva",                "SP07102X"},
        {"Domingos Bernardo Gomes Santos",          "SP090888"},
        {"Andre Evandro Lourenco",                  "SP100092"},
        {"Miguel Angelo Tancredi Molina",           "SP102763"},
        {"Antonio Airton Palladino",                "SP112197"},
        {"Luis Fernando Aires Branco Menegueti",    "SP145385"},
        {"Antonio Ferreira Viana",                  "SP200827"},
        {"Leonardo Bertholdo",                      "SP204973"},
        {"Marcelo Tavares de Santana",              "SP20500X"},
        {"Daniel Marques Gomes de Morais",          "SP220097"},
        {"Alexandre Beletti Ferreira",              "SP226117"},
        {"Vladimir Camelo Pinto",                   "SP240291"},
        {"Leonardo Andrade Motta de Lima",          "SP24031X"},
        {"Aldo Marcelo Paim",                       "SP240497"},
        {"Cesar Lopes Fernandes",                   "SP890534"},
        {"Josceli Maria Tenorio",                   "SZ124382"}
    };


    /* Verifica se o arquivo USUARIOS.DAT j� existe. Caso positivo, exibe um alerta. */
    if (file_exists("USUARIOS.DAT"))
    {
        printf("Arquivo USUARIOS.DAT j� existe!\nDeseja sobrescrever?\n");
        printf("S = Sim\nN = N�o\nEscolha uma op��o:\t");

        if (getche() != 'S')
        {
            printf("\nOpera��o de escrita cancelada\n");
            getch();
            return;
        }

        else
            printf("\nSobrescrevendo arquivo USUARIOS.DAT com dados pr�-definidos\n\n");
    }

    /* Cria arquivo e grava os registros padr�o nele */
    userDAT = fopen("USUARIOS.DAT", "w");
    validate_file(userDAT);

    list_size = (sizeof(default_users)/sizeof(USER));

    for (i = 0; i < list_size; i++)
    {
        fwrite(&default_users[i], sizeof(USER), 1, userDAT);
        validate_file(userDAT);
    }

    fclose(userDAT);
}


/* Carrega dados do arquivo DAT para uma lista pr�-alocada */
void load_users_dat(char *filename, USER_LIST *list)
{
    FILE *dat_file;
    struct USER_NODE *current_user;
    USER temp_user;
    int current_node_index = 0;
    int last_node_index = (get_size(list) - 1);

    if (file_exists(filename))
    {
        dat_file = fopen(filename, "r");
        validate_file(dat_file);

        current_user = list->head; /* Primeiro n� da lista */

        while (!feof(dat_file))
        {

            fread(&temp_user, sizeof(USER), 1, dat_file);

            if (!feof(dat_file))
            {
                strcpy(current_user->data.username, temp_user.username);
                strcpy(current_user->data.prontuario, temp_user.prontuario);
                /* printf("%s - %s\n", current_user->data.username, current_user->data.prontuario); */
                current_user = current_user->next;

                /*  Testa se h� espa�o de mem�ria alocada. Isso � �til caso o DAT seja maior que o tamanho alocado. */
                current_node_index++;
                if (current_node_index > last_node_index)
                    break;
            }
        }
    }

    else
    {
        system("cls");
        printf("ERRO: Arquivo n�o encontrado: %s", filename);
    }
}


/* Escreve dados da mem�ria no arquivo DAT */
void write_users_dat(char *filename, USER_LIST *list)
{
    FILE *userDAT;
    struct USER_NODE *current_user = list->head;
    USER *user_data;
    // char choice;

    /* Informa o usu�rio caso o arquivo j� exista */
    if (file_exists(filename))
    {
        printf("Arquivo %s j� existe!\nDeseja sobrescrever?\n", filename);
        printf("S = Sim\nN = N�o\n\n");
        // choice = getche();

        if (getche() != 'S')
        {
            printf("\nOpera��o de escrita cancelada\n");
            getch();
            return;
        }

        else
            printf("\nSobrescrevendo arquivo %s\n\n", filename);
    }

    userDAT = fopen(filename, "w");
    validate_file(userDAT);

    /* Percorre os items da lista e grava no arquivo DAT */
    while(TRUE)
    {
        /* Sai do loop ao atingir o fim da lista */
        if (current_user == NULL)
            break;

        else
        {
            user_data = &current_user->data;
            fwrite(user_data, sizeof(USER), 1, userDAT);
            validate_file(userDAT);
        }

        current_user = current_user->next;
    }

    fclose(userDAT);
}


/* Exibe os registros de usu�rio carregados na lista fornecida. */
void print_users(USER_LIST *list)
{
    struct USER_NODE *current_user = list->head;

    printf("Exibindo lista de usu�rios:\n\n");

    while(TRUE)
    {
        printf("%d. %s - %s\n", current_user->position, current_user->data.username, current_user->data.prontuario);

        if (current_user->next == NULL)
        {
            printf("\nFim da lista!\n\n");
            break;
        }

        else
            current_user = current_user->next;
    }
}


/* Mensagem tempor�ria */
void not_implemented(void)
{
    system("cls");
    printf("\n\n");
    printf("______________________________                                        \n");
    printf("___|___|___|___|___|___|___|_|                                        \n");
    printf("_|___|___|___|___|___|___|___|__________________                      \n");
    printf("___|___|___|___|___|___|___|___|___|___|___|___|__                    \n");
    printf("_|___|___|___|___|___|___|___|___|___|___|___|___|__                  \n");
    printf("___|___|___|___|___|___|___|___|___|___|___|___|___|_________________ \n");
    printf("_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|\n");
    printf("___|___|___|___|____|___|___|___|___|___|___|___|___|___|___|___|____|\n");
    printf("_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|\n");
    printf("___|___|___|___|_EM|___|___|___|___|___|___|___|___|___|___|___|___|_|\n");
    printf("_|___|___|___|___|___|CONS|___|___|___|___|___|___|___|   |___|___|__|\n");
    printf("___|___|___|___|___|___|___|TRU|___|___|___|___|___|           |___|_|\n");
    printf("_|___|   |___|___|___|___|___|___|��O|___|___|___|__             |___|\n");
    printf("___|       |___|___|___|___|___|___|___|___|___|___|______        |__|\n");
    printf("_|__         |___|___|___|___|___|___|___|___|___|___|___|_________|_|\n");
    printf("___|______   __|___|___|___|___|___|___|___|___|___|___|___|___|___|_|\n");
    printf("_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|\n");
    printf("___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|_|\n");
    printf("\n\n");
    getch();
    system("cls");
}


/* Exibe mensagem de despedida e encerra o programa */
void exit_program(void)
{
    system("cls");
    printf("Obrigado por usar nosso software!");
    getch();
    exit(EXIT_SUCCESS);
}


/* Exibe menu principal

    OBS: As op��es de abastecer g�ndolas e gerenciar usu�rios deve aparecer apenas para o usu�rio master.
*/
void main_menu(void)
{
    char choice;

    do
    {
        system("cls");
        printf("SISTEMA GERENCIADOR DE SUPERMERCADO - VERS�O BETA\n\n");
        if (DEBUG_MODE)
            printf("======== OPERANDO EM MODO DEBUG ==============\n\n");

        printf("1. Abastecer g�ndolas\n");
        printf("2. Caixa/PDV\n");
        printf("3. Gerenciar usu�rios\n\n");
        printf("0. Sair\n\n");
        printf("Selecione uma op��o: ");

        fflush(stdin);
        choice = getche(); // OBS: testar o getche() diretamente ao inv�s de declarar vari�vel. ex: switch(getche())


        switch(choice)
        {
            case '0':
                exit_program();

            case '1':
            {
                not_implemented();
                continue;
            }

            case '2':
            {
                not_implemented();
                continue;
            }

            case '3':
            {
                not_implemented();
                continue;
            }

            default:
                continue;
        }

    } while(choice != '0'); /* OBS: Seria poss�vel usar um (while TRUE) aqui para garantir que o programa s� encerre ap�s o input do usu�rio? */
}


/* Gerencia login de usu�rio.
Sugest�o: ler parametros ao inv�s de usar gets(). */
void login(void)
{
    USER *temp_user_list;
    struct USER_NODE *current_node = users->head;
    char username[USERNAME_SIZE];
    char prontuario[PRONTUARIO_SIZE];
    int i;
    int list_size = get_size(users);

    /*  Para facilitar a busca bin�ria recursiva, � melhor alocar um vetor est�tico. Dessa forma � poss�vel fazer a busca usando �ndices ao inv�s de lidar com os ponteiros da lista din�mica */

    temp_user_list = (USER *) malloc(list_size * sizeof(USER));

    for (i = 0; i < list_size; i++)
    {
        temp_user_list[i] = current_node->data;
        current_node = current_node->next;

        if (DEBUG_MODE)
            printf("Usu�rio copiado: %s - %s\n", temp_user_list[i].username, temp_user_list[i].prontuario);
    }

    system("cls");

    printf("Informe seu nome de usu�rio:\n");
    gets(username);

    printf("\n\nInforme seu prontu�rio:\n");
    gets(prontuario);

    if (search(temp_user_list, username, prontuario, 0, (list_size - 1)))
        printf("Registro encontrado: %s - %s", username, prontuario);

    else
        printf("Registro N�O ENCONTRADO: %s - %s", username, prontuario);

    /* Ap�s as opera��es, libera a mem�ria ocupada pela lista tempor�ria. */
    free(temp_user_list);
}


/* Verifica se um arquivo foi escrito ou lido corretamente. Caso negativo, encerra o programa. */
void validate_file(FILE *file)
{
    if (file == NULL || ferror(file))
    {
        system("cls");
        printf("*** ERRO AO LER/GRAVAR ARQUIVO! ***");
        getch();
        exit(EXIT_FAILURE);
    }
}


/* Testa se aloca��o de mem�ria foi bem sucedida. Caso negativo, encerra o programa. */
void validate_allocation(void *object)
{
    if (object == NULL)
    {
        system("cls");
        printf("*** ERRO AO ALOCAR MEM�RIA! ***");
        getch();
        exit(EXIT_FAILURE);
    }
}


/* Busca um registro de usu�rio usando busca bin�ria recursiva. Caso encontrado, returna TRUE; do contr�rio retorna FALSE. */
int search(USER *list, char *username, char *prontuario, int pos_inicial, int pos_final)
{
    int meio = (pos_inicial + pos_final) / 2;
    int strcmp_result;

    /* Primeiro testamos o prontu�rio. Caso exista, testamos o username. */
    if (list[meio].prontuario == prontuario)
    {
        if (list[meio].username == username)
            return(TRUE);
    }

    else
    {
        /* Comparamos o valor do meio com o nome fornecido. Se strcmp retornar um valor positivo, a segunda string vem antes da primeira. */
        strcmp_result = strcmp(list[meio].username, username);

        /* Caso tenhamos chegado ao fim do vetor e n�o encontramos o valor, retorna FALSE */
        if (pos_inicial > pos_final)
            return(FALSE);

        /* Se o usu�rio procurado est� ANTES do meio, procuramos � esquerda (de 0 at� meio - 1) */
        else if (strcmp_result > 0)
            search(list, username, prontuario, 0, (meio - 1));

        /* Se o usu�rio procurado est� DEPOIS do meio, procuramos � direita (de meio + 1 at� posi��o final) */
        else if (strcmp_result < 0)
            search(list, username, prontuario, (meio + 1), pos_final);
    }
}


/* Ordena lista em ordem crescente de nomes usando bubble sort */
void sort_list(USER_LIST *list)
{
    struct USER_NODE *current_user;
    struct USER_NODE *next_user;
    int swapped; /* Flag para determinar se houve troca de posi��o */
    int strcmp_result; /* Armazena o valor retornado por strcmp */

    do
    {
        current_user = list->head;
        next_user = current_user->next;
        swapped = FALSE;

        /* O loop abaixo percorre todos os elementos da lista comparando os valores com seu vizinho, e realiza troca caso necess�rio */

        while(current_user->next != NULL)
        {
            next_user = current_user->next;
            strcmp_result = strcmp(current_user->data.username, next_user->data.username);

            /* strcmp retorna um valor positivo quando a segunda string vem antes da primeira. */
            if (strcmp_result > 0)
            {

                swap_users(&current_user->data, &next_user->data);
                swapped = TRUE;

                /* Ap�s a compara��o, avan�amos para o pr�ximo n� */
                current_user = next_user;
                next_user = current_user->next;
            }

            else
            {
                /* Caso n�o seja necess�rio troca, apenas avan�amos para o pr�ximo n� */
                current_user = next_user;
                next_user = current_user->next;
            }
        }
    }

    while(swapped);
}


/* Adiciona um novo usu�rio a uma lista pr�-alocada */
void add_user(USER_LIST *list)
{
    struct USER_NODE *last_node = get_tail(list);
    struct USER_NODE *new_node;
    char username[USERNAME_SIZE];
    char prontuario[PRONTUARIO_SIZE];

    if (DEBUG_MODE)
        printf("�ltimo registro: %s - %s\n", last_node->data.username, last_node->data.prontuario);

    printf("Adicionando novo registro de usu�rio:\n\n");
    printf("Insira o nome de usu�rio:\t");
    gets(username);

    printf("\nInsira o prontu�rio\t");
    gets(prontuario);

    /* Aloca um novo n� na �ltima posi��o */
    last_node->next = (struct USER_NODE *) malloc(sizeof(USER_NODE));
    validate_allocation(last_node->next);

    /* Aqui seria poss�vel usar last_node = last_node->next ao inv�s de declarar uma nova vari�vel. */
    new_node = last_node->next;

    /* O �ltimo n� deve apontar para NULL. */
    new_node->next = NULL;
    new_node->position = last_node->position + 1;

    /* Copia os valores para o campo relevante */
    strcpy(new_node->data.username, username);
    strcpy(new_node->data.prontuario, prontuario);

    printf("Usu�rio adicionado: %s - %s\n", new_node->data.username, new_node->data.prontuario);

    /* Ap�s adicionar usu�rio, reorganiza a lista */
    sort_list(list);
}


/* Retorna o �ltimo elemento de uma lista */
struct USER_NODE *get_tail(USER_LIST *list)
{
    struct USER_NODE *last_node = list->head;

    while (last_node->next != NULL)
        last_node = last_node->next;

    return(last_node);
}


/* Retorna TRUE caso o arquivo exista no disco, do contr�rio retorna FALSE; */
int file_exists(char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
        return(FALSE);

    else
    {
        fclose(file);
        return(TRUE);
    }
}


/* Retorna o tamanho de um arquivo em bytes */
long int file_size(char *filename)
{
    long int size;
    FILE *file;

    if (file_exists(filename))
    {
        file = fopen(filename, "r");
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fclose(file);

        return(size);
    }

    else
        printf("ERRO - Arquivo n�o encontrado: %s\n", filename);
}

/*  Troca dois registros de usu�rio de posi��o */
void swap_users(USER *user1, USER *user2)
{
    USER temp_user;

    temp_user = *user1;
    *user1 = *user2;
    *user2 = temp_user;
}