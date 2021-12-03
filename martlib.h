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


/* ============= PROT�TIPOS DE FUN��ES ======================= */

USER_LIST *build_user_list(int list_size);

int get_size(USER_LIST *list);

void load_users_dat(char *filename, USER_LIST *list);

void print_users(USER_LIST *list);

void not_implemented(void);

void exit_program(void);

void main_menu(void);

void login(void);

void validate_file(FILE *file);

void validate_allocation(void *object);

void make_user_dat(void);

int user_list_size(void);

void busca_prontuario(char *prontuario, char tipo_busca);

int file_exists(char *filename);

long int file_size(char *filename);

int get_size(USER_LIST *list);

void swap_users(USER *user1, USER *user2);


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
            Protip: O nome de um array em C � o endere�o do primeiro elemento (ou seja, vect � igual a &vect[0]). */
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


/* Retorna o tamanho de uma lista */
int get_size(USER_LIST *list)
{
    int size = 0;
    struct USER_NODE *current_node = list->head;

    while (1)
    {

        if (current_node == NULL) /* Lista possui zero elementos */
            return(0);

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


/* Exibe os registros de usu�rio carregados na lista fornecida. */
void print_users(USER_LIST *list)
{
    struct USER_NODE *current_user = list->head;

    printf("Valores na lista:\n\n");
    while(1)
    {
        printf("%d. %s - %s\n", current_user->position, current_user->data.username, current_user->data.prontuario);

        if (current_user->next == NULL)
        {
            printf("Fim da lista!\n\n");
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


/* Exibe menu principal */
void main_menu(void)
{
    char choice;

    do
    {
        system("cls");
        printf("SISTEMA GERENCIADOR DE SUPERMERCADO - VERS�O BETA\n\n");
        /*if (DEBUG_MODE == TRUE)
        {
            printf("======== OPERANDO EM MODO DEBUG ==============\n\n");
            printf("X. EXECUTAR ROTINA DE TESTES\n\n");
        } */
        printf("1. Abastecer g�ndolas\n");
        printf("2. Caixa/PDV\n");
        printf("3. Gerenciar usu�rios\n\n");
        printf("0. Sair\n\n");
        printf("Selecione uma op��o: ");

        fflush(stdin);
        choice = getche();

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

    } while(choice != '0');
}


/* Gerencia login de usu�rio.
Sugest�o: ler parametros ao inv�s de usar scanf. */
void login(void)
{
    char username[USERNAME_SIZE];
    char prontuario[PRONTUARIO_SIZE];

    system("cls");
    printf("Informe seu nome de usu�rio:\n");
    printf("(O nome de usu�rio padr�o � seu primeiro nome em letras mai�sculas)\n");
    gets(username);
    printf("\n\nInforme seu prontu�rio:\n");
    gets(prontuario);

    if (DEBUG_MODE == TRUE)
    {
        printf("\nNome informado: %s\n", username);
        printf("Prontu�rio informado: %s\n", prontuario);
    }
}


/* Verifica se o arquivo foi escrito corretamente. */
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


/* Gera arquivo DAT com usu�rios pr�-definidos. */
void make_user_dat(void)
{
    int i;
    int list_size = 29; /* Valor harcoded para simplificar testes */
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

    /* Cria arquivo caso n�o exista */
    if (!file_exists("USUARIOS.DAT"))
    {
        userDAT = fopen("USUARIOS.DAT", "w");
        validate_file(userDAT);

        for (i = 0; i < list_size; i++)
        {
            fwrite(&default_users[i], sizeof(USER), 1, userDAT);
            validate_file(userDAT);
        }

        fclose(userDAT);
    }
}


/*  Busca um prontu�rio na lista de registros
    OBS: FUN��O OBSOLETA. � necess�rio adaptar para uso com lista encadeada */

// void busca_prontuario(char *prontuario, char tipo_busca)
// {
    /*  TIPOS DE BUSCA:

        L: Busca linear
        B: Busca bin�ria (n�o implementado)
    */

    // USER *user_pointer = user_list; /* Aponta para o primeiro registro de usu�rio */
    // int found = FALSE; /* Flag para indicar se o prontuario foi encontrado */

    // switch(tipo_busca)
    // {
        // case 'L': /* Busca linear */
        // {

            // for(; user_pointer < &user_list[user_list_size()]; user_pointer++)
            // {
                // if (strcmp(prontuario, user_pointer->prontuario) == 0)
                // {
                    // printf("Prontu�rio encontrado: %s pertence � %s\n",
                        // user_pointer->prontuario, user_pointer->username);
                    // found = TRUE;
                    // break;
                // }
            // }

            // if (found == FALSE)
                // printf("Prontu�rio n�o encontrado: %s\n", prontuario);
            // break;
        // }

        // default:
        // {
            // printf("ERRO - Par�metro inv�lido na fun��o de busca [%c]", tipo_busca);
            // getch();
            // exit(EXIT_FAILURE);
        // }
    // }
// }


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

/* Troca os usu�rios indicados de posi��o */
void swap_users(USER *user1, USER *user2)
{
    USER temp_user;

    temp_user = *user1;
    *user1 = *user2;
    *user2 = temp_user;
}