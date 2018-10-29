WFLAGS = -Wwrite-strings -Werror -Wall -Wextra -Wformat=2 -Winit-self -Wswitch-enum -Wstrict-aliasing=2 -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wdisabled-optimization -Wunused-macros -Wno-unused
warnings =  -Wunused-macros -Wno-unused
src =  src
libs = include
grammer = grammer
grammer_out = grammer/out
obj = obj 

main: main-objects
	gcc *.o -o oddo.exe 

main-objects: bison
	gcc  -g -c -Wall -I${libs}  ${grammer_out}/rules.tab.c ${grammer_out}/lex.yy.c ${src}/*.c 

bison: flex
	bison -dv ${grammer}/rules.y -o ${grammer_out}/rules.tab.c

flex:
	flex -o ${grammer_out}/lex.yy.c ${grammer}/tokens.l 

clean:
	rm *.exe 
	rm *.o
	rm  ${grammer_out}/*
	

# tests 
testsymboltable:
	gcc -g  -I${libs} tests/test_symtable.c \
	${src}/vstr.c ${src}/symboltable.c ${src}/object.c ${src}/hashtable.c ${src}/hash.c -o testsymboltable

testhash:
	gcc -g -I${libs} tests/test_hash.c ${src}/hash.c -o testhash


testhashtable:
	gcc -g -Wall -I${libs} tests/test_hashtable.c \
	${src}/hash.c ${src}/object.c ${src}/vstr.c ${src}/hashtable.c -o testhashtable

testvalue:
	gcc -g -I${libs} tests/test_value.c ${src}/object.c ${src}/vstr.c -o testvalue

testvstr: 
	gcc -g  -I${libs} tests/test_vstr.c  ${src}/vstr.c -o test_vstr

testvstr_per:
	gcc -g -O3 -I${libs} tests/test_vstr_perf.c -o test_vstr_perf
