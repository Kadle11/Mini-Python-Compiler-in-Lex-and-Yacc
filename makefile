Test.out : lex.yy.c y.tab.c y.tab.h 
	gcc lex.yy.c y.tab.c -ll -o Test.out

lex.yy.c : grammar.l
	lex grammar.l

y.tab.c : grammar.y
	yacc -d grammar.y

clean :
	rm lex.yy.c y.tab.c y.tab.h Test.out
