#include "martlib.h"

void test_DAT(void)
{
    printf("Criando arquivo USUARIOS.DAT\n");

    make_user_dat();

    if (file_exists("USUARIOS.DAT"))
    {
        printf("Arquivo USUARIOS.DAT criado com sucesso.\n");
        printf("Tamanho do USUARIOS.DAT: %d bytes", file_size("USUARIOS.DAT"));
    }

    else
        printf("Erro ao criar arquivo USUARIOS.DAT\n");
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
    setlocale(LC_ALL, "");
    system("cls");
    printf("****************************************\n");
    printf("INICIANDO ROTINAS DE TESTE\n");
    printf("****************************************\n\n");

    test_DAT();
    test_user_list();

    getch();
    return(0);
}