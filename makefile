
program=./test.scaf

main: main.c
	gcc -lncurses *.c \
		./scaffolding/fileHandling.c \
		./scaffolding/Head.c \
		./scaffolding/helperFunctions.c \
		./scaffolding/interpreter.c \
		./scaffolding/Lines.c

run:
	make
	./a.out ${program}
