.PHONY: all clean 

all: task_6

clean:
	rm -rf task_6 *.o

main.o: main.c
	gcc -std=c99 -m32 -c -o main.o main.c

functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm

task_6: main.o functions.o
	gcc -lm -m32 -o task_6 main.o functions.o
