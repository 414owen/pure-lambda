all: lambda

lambda.tab.c : lambda.y
	bison -d lambda.y

lambda.tab.h: lambda.tab.c
	:

lex.yy.c: lambda.tab.h lambda.l
	flex -o lex.yy.c lambda.l

lambda: main.c lambda.tab.c lex.yy.c ast.c eval.c ast.h eval.h stack.c stack.h
	gcc -g -O0 -o lambda main.c lambda.tab.c lex.yy.c ast.c eval.c stack.c -lreadline

clean:
	rm -i lambda lambda.tab.c lex.yy.c lambda.tab.h
