all: app

app: geometry.c
	gcc -Wall geometry.c -o geometry -lm
run:
	./geometry example
