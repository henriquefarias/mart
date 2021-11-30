#include "martlib.h"

void test_DAT(void)
{
    printf("Criando arquivo USUARIOS.DAT\n");
    make_user_dat();

    if (file_exists("USUARIOS.DAT"))
        printf("Arquivo USUARIOS.DAT criado com sucesso.\n");
    else
        printf("Erro ao criar arquivo USUARIOS.DAT\n");

    // dump_user_info();
}


void test_user_list(void)
{
    int list_size = 29;
    USER_LIST *test_list;

    test_list = build_user_list(list_size);

    validate_allocation(test_list);
    printf("\nLista alocada com sucesso.\n");
    printf("Total: %d registros na lista\n\n", get_size(test_list));
    
    load_users_dat("USUARIOS.DAT", test_list);
    print_users(test_list);
}


void test_run(void)
{
    char prontuario_teste[PRONTUARIO_SIZE];

    /* Troca a posição dos 2 primeiros registros */
    printf("\n\n*** TESTANDO FUNÇÃO DE SWAP ***\n\n");
    printf("Status antes do swap:\n");
    printf("\nusuário 1: %s\nusuário 2: %s\n", user_list[0].username, user_list[1].username);

    swap_users(&user_list[0], &user_list[1]);

    printf("\nStatus após swap:\n");
    printf("\nusuário 1: %s\nusuário 2: %s\n", user_list[0].username, user_list[1].username);

    /* Teste das funções de busca */
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

int main(void)
{
    setlocale(LC_ALL, "");
    system("cls");
    printf("****************************************\n");
    printf("INICIANDO ROTINAS DE TESTE\n");
    printf("****************************************\n\n");

    test_DAT();
    printf("\n\n");
    test_user_list();

    // test_run();

    getch();
    return(0);
}