#!/usr/bin/env python
import sys
import os
import shutil
from parser.grammar import Grammar
from parser.parse import parse, RenderTree


def main(input_parsing, parse_tree_filename, results_parsing_filename, grammar = "utils/grammar.txt"):
    # primero debemos retornar una lista de token usados
    input_for_grammar = input_parsing.split(",")
    S_lang_grammar = open("utils/grammar.txt", "r")
    S_lang_grammar_content = S_lang_grammar.read()
    S_lang_grammar.close()

    accepted_input, parse_tree, log_errors = parse(S_lang_grammar_content, input_for_grammar, False)

    parse_results = open(f"results/{results_parsing_filename}", "w+")
    if accepted_input:
        parse_results.write(f"Status: Accepted Input\n")
        parse_results.write(f"Open file [parse_tree.png] to see the resulting parse tree\n")
        RenderTree(parse_tree, f"{parse_tree_filename}")
        # moving picture to results page
        os.rename(f"{parse_tree_filename}", f"results/{parse_tree_filename}")
        os.replace(f"{parse_tree_filename}", f"results/{parse_tree_filename}")
        shutil.move(f"{parse_tree_filename}", f"results/{parse_tree_filename}")
    else:
        parse_results.write(f"Status: Non Accepted Input\n")
        parse_results.write(f"Log errors: {log_errors}\n")
    
    parse_results.close()

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
