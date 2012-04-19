CC = gcc
RM = rm

all:
	${CC} -o main main.c -lm

cleanall:
	${RM} main