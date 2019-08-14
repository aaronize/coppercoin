/*
结构体中的函数指针
 */
#include <stdio.h>
#include <malloc.h>

typedef struct Stuff
{
    void (*sayHello)(char* name);
} Stuff;

void sayHello(char *name)
{
    printf("Hello, %s\n", name);
}

int main(void)
{
    Stuff *stuff01 = (Stuff*)malloc(sizeof(Stuff));
    printf("sizeof Stuff: %d\n", sizeof(Stuff));
    stuff01->sayHello = sayHello;
    stuff01->sayHello("John");

    return 0;
}
