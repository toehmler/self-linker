# self-linker | Assignment 4

## Authors
Trey Oehmler 
CS315 Fall 2018

## Known bugs

## References

[Global Offset Tables](http://bottomupcs.sourceforge.net/csbu/x3824.htm)

[GOT and PLT for pwning](https://systemoverlord.com/2017/03/19/got-and-plt-for-pwning.html)

## Annotated GDB session

We can examine the GOT entry for puts() when the following lines are commented out:

```c 
void *got = (&_GLOBAL_OFFSET_TABLE_) + (3 / sizeof(void *));
*(void **)got = func_ptr;
```

When the first call to puts() is made we can see that the GOT for puts() hasn't been updated to its real address.

```
Dump of assembler code for function puts@plt:
=> 0x0000555555555030 <+0>:	jmpq   *0x2fe2(%rip)        # 0x555555558018 <puts@got.plt>
   0x0000555555555036 <+6>:	pushq  $0x0
   0x000055555555503b <+11>:	jmpq   0x555555555020
End of assembler dump.
(gdb) x/gx 0x55555555018[K[K[K8018
0x555555558018 <puts@got.plt>:	0x0000555555555036
```

On the second call to puts() we can see that the GOT has been updated.

```
Dump of assembler code for function puts@plt:
=> 0x0000555555555030 <+0>:	jmpq   *0x2fe2(%rip)        # 0x555555558018 <puts@got.plt>
   0x0000555555555036 <+6>:	pushq  $0x0
   0x000055555555503b <+11>:	jmpq   0x555555555020
End of assembler dump.
(gdb) x/gx 0x555555558018
0x555555558018 <puts@got.plt>:	0x00007ffff7e63a40
```

Once the lines in self-linker.c are commented we can see that on the first call to puts(), the GOT entry already contains the proper address.

```
gdb) run
Starting program: /mnt/cs315/assignment4/self-linker 

Breakpoint 1, main (argc=1, argv=0x7fffffffe9b8) at self-linker.c:48
48	    puts("hello");
(gdb) disas[K[K[K[K[Kxg[K/gx 0x[K[K[K[K[K[K[Ksi
0x000055555555524b	48	    puts("hello");
(gdb) 
0x0000555555555030 in puts@plt ()
(gdb) disas
Dump of assembler code for function puts@plt:
=> 0x0000555555555030 <+0>:	jmpq   *0x2fe2(%rip)        # 0x555555558018 <puts@got.plt>
   0x0000555555555036 <+6>:	pushq  $0x0
   0x000055555555503b <+11>:	jmpq   0x555555555020
End of assembler dump.
(gdb) x/gx 0x555555558018
0x555555558018 <puts@got.plt>:	0x00007ffff7e63a40
```



