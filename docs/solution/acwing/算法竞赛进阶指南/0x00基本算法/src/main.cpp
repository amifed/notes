#include <stdio.h>
int main() {
    int y;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t");
    for (y = 0; y <= 47; y++) {
        Sleep(60);
        int a, b;
        a = 0;
        while (a <= 70) {
            system("cls");
            b = 1;
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
            while (b <= a) {
                printf(" ");
                b++;
            }
            printf("┌════════┐...┌════════┐...┌.═════════┐   ╭═════╮\n");
            b = 1;
            while (b <= a) {
                printf(" ");
                b++;
                ;
            }
            printf("║        ║ ═ ║        ║ ═ ║          ║═  ║ 　  ║\n");
            b = 1;
            while (b <= a) {
                printf(" ");
                b++;
            }
            printf("└⊙═⊙═⊙═⊙ ⊙═⊙═⊙═⊙  └⊙═⊙═⊙═⊙~~ ╰⊙═⊙╯\n");
            Sleep(1);
            a = a + 1;
        }
    }