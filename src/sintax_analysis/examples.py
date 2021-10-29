# -*- coding: utf-8 -*-
from parse import do_the_whole_thing as do_it
from parser.functions import parse_bnf, pprint_table
from parser.grammar import Grammar
from parser.parse import *
from parser.anyTree import *

bnf_text = "E -> T E'\n" \
           "E' -> + T E' | ε\n" \
           "T -> F T'\n" \
           "T' -> * F T' | ε\n" \
           "F -> ( E ) | id"

indirect_recursive = "S -> A a | b\n" \
                     "A -> A c | S d | ε"

bnf_recursive = "E -> E + T | T\n" \
                "T -> T * F | F\n" \
                "F -> ( E ) | id"

ambigous_text = "S -> A | B\n" \
                "A -> a A b | ε\n" \
                "B -> a B b b | ε"

second_text = "E -> pa Q R | pa Q S | pa T\n" \
              "U -> e"

third_text = "S -> i E t S | i E t S e S | a\n" \
             "E -> b"

final_test = "X -> a A\n" \
             "A -> x X"

extra_test = "S -> ( A ) | ε\n" \
             "A -> T E\n" \
             "E -> & T E | ε\n" \
             "T -> ( A ) | a | b | c"

bonus_test = "L -> % w D | U#\n" \
             "U -> ! w D U | ε\n" \
             "D -> : w D | w L"

additional_test = "S -> A B e\n" \
                  "A -> d B | a S | c\n" \
                  "B -> a S | c"

free_test = "Exp -> Exp + Exp2 | Exp - Exp2 | Exp2\n" \
            "Exp2 -> Exp2 * Exp3 | Exp2 / Exp3 | Exp3\n" \
            "Exp3 -> num | ( Exp )"

courtesy_test = "E -> T + E | T\n" \
                "T -> int | int * T | ( E )"

final_grammar = "Program -> Block\n"\
                "Block -> { Decls Stmts }\n"\
                "Decls -> Decls1\n"\
                "Decls1 -> Decl Decls1 | ε\n"\
                "Decl -> Type id ;\n"\
                "Type -> int | float | bool | string\n"\
                "Stmts -> Stmts1\n"\
                "Stmts1 -> Stmt Stmts1 | ε\n"\
                "Stmt ->	Loc assign Bool ; |	if Fif | while ( Bool ) Stmt endwhile | break ; | Block\n"\
                "Fif ->	( F(\n"\
                "F( ->	Bool FBool\n"\
                "FBool -> ) F)\n"\
                "F) ->	Stmt FStmt\n"\
                "FStmt -> endif | else Stmt endif\n"\
                "Loc -> id\n"\
                "Bool -> Join Bool1\n"\
                "Bool1 -> or Join Bool1 | ε\n"\
                "Join -> Equality Join1\n"\
                "Join1 -> && Equality Join1 | ε\n"\
                "Equality -> Rel Equality1\n"\
                "Equality1 -> == Rel Equality1 | != Rel Equality1 | ε\n"\
                "Rel -> Expr FExpr\n"\
                "FExpr -> < Expr | <= Expr | >= Expr | > Expr | ε\n"\
                "Expr -> Term Expr1\n"\
                "Expr1 -> + Term Expr1 | - Term Expr1 | ε\n"\
                "Term -> Unary Term1\n"\
                "Term1 -> * Unary Term1 | / Unary Term1 | ε\n"\
                "Unary -> ! Unary |	Factor\n"\
                "Factor -> ( Bool ) | Loc | num | real | true | false | string\n" 

"""
do_it(bnf_recursive)

do_it(ambigous_text)

do_it(second_text)

do_it(third_text)

do_it(indirect_recursive)

do_it(final_test)

do_it(extra_test)

do_it(bonus_test)

do_it(additional_test)

do_it(free_test)

do_it(courtesy_test)
"""
#do_it(final_grammar, epsilon='ε', eof='$', output="grammar.txt", verbose=True)

input = ["{", "num", "+", "num", ";", "}"]

result, tree, errors = parse(final_grammar, input, False)
print(f"Acc?: {result} , errors?: {errors}")
RenderTree(tree, "final_parse.png")

# mygram = parse_bnf(extra_test)
# table, ambiguous = mygram.parsing_table()
# print(f"Ambiguous {ambiguous}")
# print(table)
# pprint_table(mygram, table)

