#include <stdio.h>

/* Global variable inside shared library */
static int counter = 0;

/* Modify global variable */
void increment(void)
{
    counter++;
}

/* Display global variable */
void display(void)
{
    printf("Counter value: %d\n", counter);
}

/* Reset global variable */
void reset(void)
{
    counter = 0;
}
