 /*
  * self-linker.c
  * Trey Oehmler
  * CS315 Assignment 4 Fall 2018
  * 
  */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>



extern void *_GLOBAL_OFFSET_TABLE_;

int
main(int argc, char *argv[]) 
{
    // Load shared library file for libc
    void *handle = dlopen(LIBC_SO, RTLD_LAZY);

    // Check for dlopen error
    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    dlerror(); // Clear existing errors

    // Get addr of symol in shared object
    void *func_ptr = dlsym(handle, "puts");
    
    // Check for dlsym error
    if (!func_ptr)
    {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    // Update GOT entry with that returned by dlsym
    // Offset of 3 found my examining GDB output without lines 44 / 45
    void *got = (&_GLOBAL_OFFSET_TABLE_) + 3;
    *(void **)got = func_ptr;

    // Function call to demonstrate behavior
    puts("hello");
    puts("world");
  
    dlclose(handle); // Close shared object

    return 0;
    
}
