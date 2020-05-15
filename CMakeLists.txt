project(MiniJava)
cmake_minimum_required(VERSION 3.0)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
            COMMAND brew --prefix bison
            RESULT_VARIABLE BREW_BISON
            OUTPUT_VARIABLE BREW_BISON_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_BISON EQUAL 0 AND EXISTS "${BREW_BISON_PREFIX}")
        message(STATUS "Found Bison keg installed by Homebrew at ${BREW_BISON_PREFIX}")
        set(BISON_EXECUTABLE "${BREW_BISON_PREFIX}/bin/bison")
    endif ()

    execute_process(
            COMMAND brew --prefix flex
            RESULT_VARIABLE BREW_FLEX
            OUTPUT_VARIABLE BREW_FLEX_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_FLEX EQUAL 0 AND EXISTS "${BREW_FLEX_PREFIX}")
        message(STATUS "Found Flex keg installed by Homebrew at ${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE "${BREW_FLEX_PREFIX}/bin/flex")
        include_directories(${BREW_FLEX_PREFIX}/include)
    endif ()
endif ()

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MiniJava_SOURCE_DIR}/bin)


set(
    HEADERS
    ${MiniJava_SOURCE_DIR}/driver.hh
    ${MiniJava_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    MyParser
    parser.y
    ${MiniJava_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${MiniJava_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.l
    ${MiniJava_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
    MiniJava
    main.cpp
    driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
        ASTNode.h
        Program.h
        expressions/BaseExpression.h
        expressions/BinaryExpression.h
        expressions/Plus.h
        statements/BaseStatement.h
        statements/Main.cpp
        statements/Main.h
        visitors/BaseVisitor.h
        visitors/PrintVisitor.cpp
        visitors/PrintVisitor.h
        visitors/elements.h statements/StatementsList.cpp statements/StatementsList.h expressions/Constant.cpp expressions/Constant.h statements/Print.cpp statements/Print.h expressions/Minus.h expressions/Division.h expressions/Multiplication.h expressions/Modulo.h expressions/OrBinary.h expressions/AndBinary.h expressions/Greater.h expressions/Less.h expressions/Equal.h statements/VariableDeclaration.cpp statements/VariableDeclaration.h statements/Assert.cpp statements/Assert.h statements/IfStatement.cpp statements/IfStatement.h statements/WhileLoop.cpp statements/WhileLoop.h statements/Assignment.cpp statements/Assignment.h statements/Return.cpp statements/Return.h expressions/NotBinary.cpp expressions/NotBinary.h expressions/Identifier.cpp expressions/Identifier.h)
target_include_directories(MiniJava PRIVATE ${MiniJava_SOURCE_DIR})



