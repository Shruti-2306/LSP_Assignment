#include <stdio.h>
#include "mystring.h"

int main()
{
    char buffer[256];
    int len;

    printf("Enter a string: ");
    fgets(buffer, sizeof(buffer), stdin);

    /* Remove newline added by fgets */
    buffer[strcspn(buffer, "\n")] = '\0';

    len = MyStrlen(buffer);

    if (len == -1) {
        printf("Error: NULL string passed\n");
    } else {
        printf("Length of string: %d\n", len);
    }

    return 0;
}
