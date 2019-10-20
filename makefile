
program=./test.scaf

main: main.c
	gcc -Wall -Wextra -lncurses *.c \
		./scaffolding/fileHandling.c \
		./scaffolding/Head.c \
		./scaffolding/helperFunctions.c \
		./scaffolding/interpreter.c \
		./scaffolding/Lines.c

prod:
	gcc -Wall -lncurses -O3 *.c \
		./scaffolding/fileHandling.c \
		./scaffolding/Head.c \
		./scaffolding/helperFunctions.c \
		./scaffolding/interpreter.c \
		./scaffolding/Lines.c

run:
	make
	./a.out ${program}
