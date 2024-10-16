CC=gcc
CFLAGS=-c
ANTLR3_FLAGS=/usr/local/lib/libantlr3c.a
LDFLAGS=
SOURCES=main.c module/module.c module/struct/ast/Ast.c module/struct/error/ErrorContainer.c module/struct/result/Result.c module/grammar/parser/GrammarParser.c module/grammar/lexer/GrammarLexer.c
OBJECTS=${patsubst %.c,build/%.o,${SOURCES}}
BUILD_DIR=build
RESULT_DIR=result
EXECUTABLE=SPOLab1

all: clean build run

build: main.o module.o Result.o GrammarLexer.o GrammarParser.o ErrorContainer.o Ast.o
	${CC} -o ${EXECUTABLE} ${OBJECTS} /usr/local/lib/libantlr3c.a -lgvc -lcgraph

main.o: main.c
	mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} main.c -o ${BUILD_DIR}/main.o

module.o: module/module.c
	mkdir -p ${BUILD_DIR}/module
	${CC} ${CFLAGS} module/module.c -o ${BUILD_DIR}/module/module.o #${ANTLR3_FLAGS} -lgvc -lcgraph

Result.o: module/struct/result/Result.c
	mkdir -p ${BUILD_DIR}/module/struct/result
	${CC} ${CFLAGS} module/struct/result/Result.c -o ${BUILD_DIR}/module/struct/result/Result.o #${ANTLR3_FLAGS}

GrammarLexer.o: module/grammar/lexer/GrammarLexer.c
	mkdir -p ${BUILD_DIR}/module/grammar/lexer
	${CC} ${CFLAGS} module/grammar/lexer/GrammarLexer.c -o ${BUILD_DIR}/module/grammar/lexer/GrammarLexer.o #${ANTLR3_FLAGS}

GrammarParser.o: module/grammar/parser/GrammarParser.c
	mkdir -p ${BUILD_DIR}/module/grammar/parser
	${CC} ${CFLAGS} module/grammar/parser/GrammarParser.c -o ${BUILD_DIR}/module/grammar/parser/GrammarParser.o #${ANTLR3_FLAGS}

ErrorContainer.o: module/struct/error/ErrorContainer.c
	mkdir -p ${BUILD_DIR}/module/struct/error
	${CC} ${CFLAGS} module/struct/error/ErrorContainer.c -o ${BUILD_DIR}/module/struct/error/ErrorContainer.o

Ast.o: module/struct/ast/Ast.c
	mkdir -p ${BUILD_DIR}/module/struct/ast
	${CC} ${CFLAGS} module/struct/ast/Ast.c -o ${BUILD_DIR}/module/struct/ast/Ast.o

run: ${EXECUTABLE}.exe
	for i in 1 2; do \
    	./${EXECUTABLE} tests/test$$i.txt ${RESULT_DIR}; \
    done

clean:
	rm -rf ${BUILD_DIR}
	rm -rf ${RESULT_DIR}
	rm -rf ${EXECUTABLE}.exe
