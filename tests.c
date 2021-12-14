#include "martlib.h"

#define gondola_size 10

void test_DAT(void)
{
    printf("Criando arquivo USUARIOS.DAT\n");

    build_user_dat();

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


void test_user_list(void)
{
    int list_size = 29; /* Valor hardcoded para testes. Corresponde ao número de registros default. */
    USER_LIST *test_list;

    test_list = build_user_list(list_size);

    validate_allocation(test_list);
    printf("\nLista alocada com sucesso.\n");
    printf("Total: %d registros na lista\n", get_size(test_list));

    load_users_dat("USUARIOS.DAT", test_list);
    print_users(test_list);
    printf("Tamanho do USUARIOS.DAT: %d bytes", file_size("USUARIOS.DAT"));
}


int main(void)
{
    int list_size = 29; /* Valor hardcoded para testes. Corresponde ao número de registros default. */
    USER_LIST *users;

    setlocale(LC_ALL, "");
    system("cls");
    printf("****************************************\n");
    printf("INICIANDO ROTINAS DE TESTE\n");
    printf("****************************************\n\n");

    /* Cria o arquivo DAT */
    test_DAT();

    /* Aloca uma lista de usuários e carrega dados do DAT para a memória */
    users = build_user_list(list_size);
    validate_allocation(users);

    load_users_dat("USUARIOS.DAT", users);
    validate_allocation(users);

    printf("Conteúdo de USUARIOS.DAT:\n\n");
    print_users(users);

    /* Ordena os dados na memória e grava no DAT */
    sort_list(users);
    printf("Gravando dados após ordenação.\n\n");
    write_users_dat("USUARIOS.DAT", users);

    /* Recarrega o arquivo DAT e imprime seu conteúdo  */
    printf("\n\n");
    printf("Recarregando arquivo USUARIOS.DAT\n");
    load_users_dat("USUARIOS.DAT", users);

    validate_allocation(users);
    printf("Conteúdo de USUARIOS.DAT após ordenação:\n\n");
    print_users(users);

    getch();
    return(0);
}