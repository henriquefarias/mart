#include "martlib.h"

int main(void)
{
    setlocale(LC_ALL, "");
    system("cls");
    
    login();
    getch();
    
    main_menu();
}