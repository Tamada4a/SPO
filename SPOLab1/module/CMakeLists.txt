# Устанавливаем минимальную версию CMake, необходимую для сборки проекта
cmake_minimum_required(VERSION 3.28)

# Устанавливаем значение стандарта
set(CMAKE_C_STANDARD 11)

# Объявляем ${MODULE_NAME} библиотекой
add_library(${MODULE_NAME}
        module.c
        grammar/lexer/GrammarLexer.c
        grammar/parser/GrammarParser.c
        struct/ast/Ast.c
        struct/error/ErrorContainer.c
        struct/result/Result.c
)

# Импортируем установленный ANTLR3
add_library(antlr3c STATIC IMPORTED)
set_property(TARGET antlr3c PROPERTY IMPORTED_LOCATION /usr/local/lib/libantlr3c.a)

# Подключаем необходимые библиотеки к ${MODULE_NAME}
target_link_libraries(${MODULE_NAME} PUBLIC cgraph gvc antlr3c)