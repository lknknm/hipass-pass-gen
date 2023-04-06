# Make
hipass: hipass.o
	gcc hipass.c ./lib/clipboard.c ./lib/generator.c -o hipass

clean: 
	rm hipass.o