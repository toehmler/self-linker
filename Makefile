self-linker: self-linker.c
	gcc -Wall -ldl -g -pedantic -o self-linker self-linker.c
	
.PHONY: clean 
clean:
	rm -rf self-linker

