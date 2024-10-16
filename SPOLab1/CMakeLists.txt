# Устанавливаем минимальную версию CMake, необходимую для сборки проекта
cmake_minimum_required(VERSION 3.28)

# Устанавливаем название проекта и язык
project(SPOLab1 C)

# Устанавливаем значение стандарта
set(CMAKE_C_STANDARD 11)

# Создаем переменную ${MODULE_NAME} и устанавливаем ей значение
set(MODULE_NAME "Module")

# Указываем какие файлы должны быть в сборке
add_executable(
        ${PROJECT_NAME}
        main.c
#        module/grammar/lexer/GrammarLexer.c
#        module/grammar/parser/GrammarParser.c
#        module/struct/ast/Ast.c
#        module/struct/error/ErrorContainer.c
#        module/struct/result/Result.c
)

# Указываем директиву, в которой находится ${MODULE_NAME}
add_subdirectory("module")

# Добавляем ${MODULE_NAME} в качестве библиотеки
target_link_libraries(${PROJECT_NAME} PRIVATE ${MODULE_NAME})