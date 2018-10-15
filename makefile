

main: bison
	gcc -g *.c 

bison: flex
	bison -dv rules.y

flex:
	flex tokens.l

clean:
	rm rules.tab.c rules.tab.h lexyy.c


testsymboltable:
	gcc -g  tests/test_symtable.c symboltable.c object.c hashtable.c hash.c

testhash:
	gcc -g tests/test_hash.c hash.c


testhashtable:
	gcc -g -Wall tests/test_hashtable.c hash.c object.c hashtable.c

testvalue:
	gcc -g tests/test_value.c object.c
