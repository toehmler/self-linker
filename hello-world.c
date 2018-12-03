/*
 * hello-world.c
 */

#include <stdio.h>
#include <dlfcn.h>

extern void *_GLOBAL_OFFSET_TABLE_;

int
main(int argc, char *argv[])
{
    puts("hello");
    puts("world");
	printf("The first entry of the global offset table is %p\n", _GLOBAL_OFFSET_TABLE_);
	printf("The GOT starts at address %p\n", &_GLOBAL_OFFSET_TABLE_);
}
