#include <stdio.h>
#include <stdlib.h>
#include <conio.h.>
#include <locale.h>
#include <string.h>

// Define o tamanho dos campos de texto +1 para o null terminator
#define TAMANHO_NOME 60+1
#define TAMANHO_PRONTUARIO 8+1

// Tipos booleanos
#define TRUE 1
#define FALSE NULL

// Gera arquivos de log
#define DEBUG_MODE TRUE

// Dados de usuários
typedef struct
{
    char username[TAMANHO_NOME];
    char prontuario[TAMANHO_PRONTUARIO];
} USUARIO;


// ============= USUÁRIOS PRÉ-DEFINIDOS =============
// OBS: Talvez seja melhor mover isso pra função make_dat

USUARIO user_list[] =
{
    /*          NOME                            PRONTUÁRIO */

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

// ============= PROTÓTIPOS DE FUNÇÕES =======================

void not_implemented(void);

void finaliza_programa(void);

void main_menu(void);

void login(void);

void valida_arquivo(FILE *arquivo);

void make_user_dat(void);

int user_list_size(void);

void get_user_list_stats(void);

void dump_user_info(void);

void busca_prontuario(char *prontuario, char tipo_busca);

int file_exists(char *filename);

void test_run(void);

void swap_users(int pos1, int pos2);


// ============= CONSTRUÇÃO DE FUNÇÕES =======================

// Mensagem temporária
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
    printf("_|___|   |___|___|___|___|___|___|ÇÃO|___|___|___|__             |___|\n");
    printf("___|       |___|___|___|___|___|___|___|___|___|___|______        |__|\n");
    printf("_|__         |___|___|___|___|___|___|___|___|___|___|___|_________|_|\n");
    printf("___|______   __|___|___|___|___|___|___|___|___|___|___|___|___|___|_|\n");
    printf("_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|\n");
    printf("___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|_|\n");
    printf("\n\n");
    getch();
    system("cls");
}


// Exibe mensagem de despedida e encerra o programa
void finaliza_programa(void)
{
    system("cls");
    printf("Obrigado por usar nosso software!");
    getch();
    exit(EXIT_SUCCESS);
}


// Exibe menu principal
void main_menu(void)
{
    char choice;

    do
    {
        system("cls");
        printf("SISTEMA GERENCIADOR DE SUPERMERCADO - VERSÃO BETA\n\n");
        if (DEBUG_MODE == TRUE)
            printf("======== OPERANDO EM MODO DEBUG ==============\n\n");
        printf("1. Abastecer gôndolas\n");
        printf("2. Caixa/PDV\n");
        printf("3. Gerenciar usuários\n\n");
        printf("0. Sair\n\n");
        if (DEBUG_MODE == TRUE)
            printf("X. EXECUTAR ROTINA DE TESTES\n\n");
        printf("Selecione uma opção: ");

        fflush(stdin);
        choice = getche();

        switch(choice)
        {
            case '0':
                finaliza_programa();

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

            case 'X': case 'x':
                if (DEBUG_MODE == TRUE)
                    test_run();
                else
                    continue;

            default:
                continue;
        }

    } while(choice != '0');
}


// Gerencia login de usuário.
void login(void)
{
    char username[TAMANHO_NOME];
    char prontuario[TAMANHO_PRONTUARIO];

    system("cls");
    printf("Informe seu nome de usuário:\n");
    printf("(O nome de usuário padrão é seu primeiro nome em letras maiúsculas)\n");
    gets(username);
    printf("\n\nInforme seu prontuário:\n");
    gets(prontuario);

    if (DEBUG_MODE == TRUE)
    {
        printf("\nNome informado: %s\n", username);
        printf("Prontuário informado: %s\n", prontuario);
    }

    busca_prontuario(prontuario, 'L');
}


// Verifica se o arquivo foi escrito corretamente
void valida_arquivo(FILE *arquivo)
{
    if (arquivo == NULL || ferror(arquivo))
    {
        printf("\n*** ERRO AO LER/GRAVAR ARQUIVO! ***\n");
        getch();
        exit(EXIT_FAILURE);
    }
}


// Gera arquivo DAT com usuários pré-definidos
void make_user_dat(void)
{
    int i;
    FILE *userDAT;

    // Cria arquivo caso não exista
    if (!file_exists("USUARIOS.DAT"))
    {
        userDAT = fopen("USUARIOS.DAT", "w");
        valida_arquivo(userDAT);

        for (i = 0; i < user_list_size(); i++)
        {
            fwrite(&user_list[i], sizeof(user_list[i]), 1, userDAT);
            valida_arquivo(userDAT);
        }

        fclose(userDAT);
    }
}


// Retorna o número de registros de usuário carregados na memória
int user_list_size(void)
{
    return((sizeof(user_list)/sizeof(USUARIO)));
}


// Exibe informações sobre a lista de usuários
void get_user_list_stats(void)
{
    printf("\nTamanho total dos registros: %d bytes\n", sizeof(user_list));
    printf("Tamanho de cada registro indididual: %d bytes\n", sizeof(USUARIO));
    printf("Total de registros na lista: %d\n", user_list_size());
}


// Imprime os dados dos registros na tela
// TODO: flag para dumpar essa info em um txt
void dump_user_info(void)
{
    USUARIO *user_pointer = user_list; // Aponta para o primeiro registro de usuário

    // Percorre o array usando ponteiros.
    for(; user_pointer < &user_list[user_list_size()]; user_pointer++)
    {
        printf("%s - %s\n", user_pointer->username, user_pointer->prontuario);
    }
}


// Busca um prontuário na lista de registros
void busca_prontuario(char *prontuario, char tipo_busca)
{
    /*  TIPOS DE BUSCA:

        L: Busca linear
        B: Busca binária (não implementado)
    */

    USUARIO *user_pointer = user_list; // Aponta para o primeiro registro de usuário
    int found = FALSE; // Flag para indicar se o prontuario foi encontrado

    switch(tipo_busca)
    {
        case 'L': // Busca linear
        {

            for(; user_pointer < &user_list[user_list_size()]; user_pointer++)
            {
                if (strcmp(prontuario, user_pointer->prontuario) == 0)
                {
                    printf("Prontuário encontrado: %s pertence à %s\n",
                        user_pointer->prontuario, user_pointer->username);
                    found = TRUE;
                    break;
                }
            }

            if (found == FALSE)
                printf("Prontuário não encontrado: %s\n", prontuario);
            break;
        }

        default:
        {
            printf("ERRO - Parâmetro inválido na função de busca [%c]", tipo_busca);
            getch();
            exit(EXIT_FAILURE);
        }
    }
}


// Retorna TRUE caso o arquivo exista no disco, do contrário retorna FALSE;
int file_exists(char *filename)
{
    FILE *file;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        fclose(file);
        return(FALSE);
    }

    else
    {
        fclose(file);
        return(TRUE);
    }
}


// Executa teste de diversas funções
void test_run(void)
{
    char prontuario_teste[TAMANHO_PRONTUARIO]; // Armazena prontuário temporário para teste manual

    system("cls");
    printf("****************************************\n");
    printf("INICIANDO ROTINAS DE TESTE\n");
    printf("****************************************\n\n");

    printf("Criando arquivo USUARIOS.DAT\n");
    make_user_dat();

    if (file_exists("USUARIOS.DAT"))
        printf("Arquivo USUARIOS.DAT criado com sucesso.\n");
    else
        printf("Erro ao criar arquivo USUARIOS.DAT\n");

    get_user_list_stats();

    printf("\n*** EXIBINDO DADOS DE USUÁRIOS ***\n\n");
    dump_user_info();

    // Troca a posição dos 2 primeiros registros
    printf("\n\n*** TESTANDO FUNÇÃO DE SWAP ***\n\n");
    printf("Status antes do swap:\n");
    printf("\nusuário 1: %s\nusuário 2: %s\n", user_list[0].username, user_list[1].username);

    swap_users(0, 1);

    printf("\nStatus após swap:\n");
    printf("\nusuário 1: %s\nusuário 2: %s\n", user_list[0].username, user_list[1].username);

    // Teste das funções de busca
    printf("\n\n*** TESTANDO FUNÇÃO DE BUSCA DO PRONTUÁRIO COM VALOR PRÉ-DEFINIDO (SP07102X) ***\n\n");
    busca_prontuario("SP07102X", 'L');

    printf("\n\n*** TESTANDO FUNÇÃO DE BUSCA COM VALOR MANUAL ***\n\n");
    printf("Digite o prontuário que deseja consultar:\n");
    gets(prontuario_teste);
    busca_prontuario(prontuario_teste, 'L');

    printf("\n\n****************************************\n");
    printf("FIM DA ROTINA DE TESTES!\n");
    printf("****************************************\n");
    getch();
}


// Troca os usuários nas posições indicadas
void swap_users(int pos1, int pos2)
{
    USUARIO temp_user;

    // Verifica se os valores informados estão dentro dos limites
    if (pos1 >= 0 && pos1 < user_list_size() && pos2 >= 0 && pos2 < user_list_size())
    {
        temp_user = user_list[pos1];
        user_list[pos1] = user_list[pos2];
        user_list[pos2] = temp_user;
    }
    else if (DEBUG_MODE == TRUE)
        printf("\nERRO na função swap_users: índices informados estão fora dos limites [%d, %d]. Swap abortado.", pos1, pos2);
}