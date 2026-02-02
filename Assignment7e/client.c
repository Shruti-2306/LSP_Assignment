#include <stdio.h>
#include "mystring.h"
#include "mymath.h"

int main()
{
    int choice;
    char str1[100], str2[100], buffer[200];
    int a, b;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1.String Length\n2.String Copy\n3.String Concat\n");
        printf("4.String Compare\n5.String Reverse\n");
        printf("6.Abs\n7.Max/Min\n8.Factorial\n9.GCD/LCM\n");
        printf("10.Power\n11.Sqrt\n0.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            fgets(str1, 100, stdin);
            printf("Length: %d\n", MyStrlen(str1) - 1);
            break;

        case 2:
            fgets(str1, 100, stdin);
            MyStrcpy(buffer, str1);
            printf("Copied: %s", buffer);
            break;

        case 3:
            fgets(str1, 100, stdin);
            fgets(str2, 100, stdin);
            MyStrcpy(buffer, str1);
            MyStrcat(buffer, str2);
            printf("Result: %s", buffer);
            break;

        case 4:
            fgets(str1, 100, stdin);
            fgets(str2, 100, stdin);
            printf("Compare: %d\n", MyStrcmp(str1, str2));
            break;

        case 5:
            fgets(str1, 100, stdin);
            MyStrrev(str1);
            printf("Reversed: %s\n", str1);
            break;

        case 6:
            scanf("%d", &a);
            printf("Abs: %d\n", MyAbs(a));
            break;

        case 7:
            scanf("%d%d", &a, &b);
            printf("Max:%d Min:%d\n", MyMax(a,b), MyMin(a,b));
            break;

        case 8:
            scanf("%d", &a);
            printf("Factorial: %ld\n", MyFactorial(a));
            break;

        case 9:
            scanf("%d%d", &a, &b);
            printf("GCD:%d LCM:%d\n", MyGCD(a,b), MyLCM(a,b));
            break;

        case 10:
            scanf("%d%d", &a, &b);
            printf("Power: %.2f\n", MyPow(a, b));
            break;

        case 11:
            scanf("%d", &a);
            printf("Sqrt: %.4f\n", MySqrt(a));
            break;

        case 0:
            return 0;
        }
    }
}
