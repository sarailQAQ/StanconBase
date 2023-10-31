#!/bin/bash
flex --outfile ./src/observer/sql/parser/lex_sql.cpp --header-file=./src/observer/sql/parser/lex_sql.h ./src/observer/sql/parser/lex_sql.l
`which bison` -d --output ./src/observer/sql/parser/yacc_sql.cpp ./src/observer/sql/parser/yacc_sql.y

