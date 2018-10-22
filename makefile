all: lambda

lambda.tab.c : lambda.y
	bison -d lambda.y

lambda.tab.h: lambda.tab.c
	:

lex.yy.c: lambda.tab.h lambda.l
	flex -o lex.yy.c lambda.l

lambda: lex.yy.c ast.c
	gcc -g -O0 -o lambda lambda.tab.c lex.yy.c ast.c

clean:
	rm lambda lambda.tab.c lex.yy.c lambda.tab.h
