CC = gcc
RM = rm

all:
	${CC} -o main main.c -lm -lpthread

cleanall:
	${RM} main