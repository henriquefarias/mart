#include <stdio.h>
#include <stdlib.h>
#include <conio.h.>
#include <locale.h>
#include <string.h>


// Define o tamanho dos campos de texto
#define TAMANHO_NOME 50
#define TAMANHO_PRONTUARIO 10


// Dados de usuários
typedef struct
{
    char username[TAMANHO_NOME];
    char prontuario[TAMANHO_PRONTUARIO];
} USUARIO;


// Usuários pré-definidos
USUARIO user_list[] =
{
    {"Domingos Lucas Latorre de Oliveira", "CJ146456"},
    {"Leandro Pinto Santana", "CP220383"},
    {"Rodrigo Ribeiro de Oliveira", "RG134168"},
    {"Andre Luiz da Silva", "SP030028"},
    {"Claudia Miyuki Werhmuller", "SP030041"},
    {"Claudete de Oliveira Alves", "SP03020X"},
    {"Francisco Verissimo Luciano", "SP030247"},
    {"Luk Cho Man", "SP060380"},
    {"Ivan Francolin Martinez", "SP060835"},
    {"Joao Vianei Tamanini", "SP060914"},
    {"Jose Oscar Machado Alexandre", "SP070038"},
    {"Jose Braz de Araujo", "SP070385"},
    {"Paulo Roberto de Abreu", "SP070816"},
    {"Eurides Balbino da Silva", "SP07102X"},
    {"Domingos Bernardo Gomes Santos", "SP090888"},
    {"Andre Evandro Lourenco", "SP100092"},
    {"Miguel Angelo Tancredi Molina", "SP102763"},
    {"Antonio Airton Palladino", "SP112197"},
    {"Luis Fernando Aires Branco Menegueti", "SP145385"},
    {"Antonio Ferreira Viana", "SP200827"},
    {"Leonardo Bertholdo", "SP204973"},
    {"Marcelo Tavares de Santana", "SP20500X"},
    {"Daniel Marques Gomes de Morais", "SP220097"},
    {"Alexandre Beletti Ferreira", "SP226117"},
    {"Vladimir Camelo Pinto", "SP240291"},
    {"Leonardo Andrade Motta de Lima", "SP24031X"},
    {"Aldo Marcelo Paim", "SP240497"},
    {"Cesar Lopes Fernandes", "SP890534"},
    {"Josceli Maria Tenorio", "SZ124382"}
};


// ============= PROTÓTIPOS DE FUNÇÕES =======================

void not_implemented(void);

void finaliza_programa(void);

void main_menu(void);

void login(void);

void valida_arquivo(FILE *arquivo);

void gera_arquivo_dat(void);

void get_dat_info(void);


// ============= FUNÇÕES =======================

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
    exit(0);
}

// Exibe menu principal
void main_menu(void)
{
    int choice;

    do
    {
        system("cls");
        printf("SISTEMA GERENCIADOR DE SUPERMERCADO\n\n");
        printf("1. Abastecer gôndolas\n");
        printf("2. Caixa/PDV\n");
        printf("3. Gerenciar usuários\n\n");
        printf("0. Sair\n\n");
        printf("Selecione a opção:");

        fflush(stdin);
        choice = getch();

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

            default:
                continue;
        }
    } while(choice != '0');
}

// Gerencia login de usuário
void login(void)
{
    char username[TAMANHO_NOME];
    char prontuario[TAMANHO_PRONTUARIO];

    system("cls");
    printf("Informe seu nome:\n");
    gets(username);

    printf("\n\nInforme seu prontuário:\n");
    gets(prontuario);

    printf("\nNome: %s\n", username);
    printf("Prontuário: %s", prontuario);

    getch();
}

// Verifica se o arquivo foi escrito corretamente
void valida_arquivo(FILE *arquivo)
{
    if (arquivo == NULL || ferror(arquivo))
    {
        printf("Erro ao ler/gravar arquivo!\n");
        getch();
        exit(0);
    }
}

// Gera arquivo DAT
void gera_arquivo_dat(void)
{
    int i;
    FILE *arquivoDAT;

    arquivoDAT = fopen("USUARIOS.DAT", "w");
    valida_arquivo(arquivoDAT);
    fclose(arquivoDAT);
}

// Exibe informações sobre o tamanho de um registro
void get_dat_info(void)
{
    system("cls");
    printf("Tamanho total dos registros: %d bytes\n", sizeof(user_list));
    printf("Tamanho de cada registro indididual: %d bytes\n", sizeof(USUARIO));
    printf("Total de registros na lista: %d", (sizeof(user_list)/sizeof(USUARIO)));
    getch();
}