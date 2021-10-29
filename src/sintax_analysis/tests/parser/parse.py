"""Parse using the LL(1) table."""
from queue import LifoQueue

from parser.anyTree import Node, RenderTree

from parser.functions import parse_bnf


class Stack(LifoQueue):
    """Symbol stack."""
    def peek(self):
        """Returns top of stack."""
        if len(self.queue) == 0:
            return None
        return self.queue[len(self.queue) - 1]

def parse(grammar, words):
    """
    Parse function
    grammar: una gramática LL(1)
    words: una lista de palabras (tokens), a ser parseado
    """
    # primero leemos la gramática
    grammar = parse_bnf(grammar) 
    # generamos la tabla y verificamos si es ambigua
    table, ambiguous = grammar.parsing_table(is_clean=True)
    if ambiguous:
        # en caso de ser una gramática ambigua lanzamos una advertencia
        print("Ambiguous grammar")
        raise Warning("Ambiguous grammar")


    error_list = []
    # solo se agrega si la cadena no tiene incluido el símbolo terminal
    if words[-1] != '$':
        words.append("$")
    word = words.pop(0)
    stack = Stack()
    
    # el nodo padre no tiene hijos
    root = Node(grammar.start)
    # cada elemento del stack contiene el formato (símbolo de la gramática, nodo del árbol)
    stack.put(("$", None))
    stack.put((grammar.start, root))

    top_stack = stack.peek()
    while True:
        print(f"Current_word:{word},  Stack:{stack.queue}")
        if top_stack[0] == "$" and word == "$":
            if not error_list:
                return True, root, None
            else:
                return False, root, error_list

        if grammar.is_terminal(top_stack[0]):
            if top_stack[0] == word:
                print(f"Consume input: {word}")
                stack.get()
                word = words.pop(0)
            else:
                error_list.append(f"Expected {top_stack[0]}")
                while word != top_stack[0]:
                    if word == "$":
                        return False, root, error_list
                    word = words.pop(0)
        else:
            rule = table.get((top_stack[0], word))
            stack.get() # pop() del stack
            if rule:
                print(f"Rule: {rule}")
                # aquí se invierte la tupla
                symbols = rule.body[::-1]
                for symbol in symbols:
                    node = Node(symbol)
                    top_stack[1].add_child(node)
                    if symbol != "ε":
                        stack.put((symbol, node))
            else:
                error_list.append(f"Unexpected character:{word}. Expected: {grammar.first(top_stack[0])}")
                follow = grammar.follow(top_stack[0]) + ["$"]
                print(f"Error! Sync set: {follow}")
                while word not in follow:
                    print(f"Skipped: {word}")
                    word = words.pop(0)
                
        top_stack = stack.peek()

"""
def parse_tree(grammar, words):
    result, tree, errors = parse(grammar, words)
    if not result:
        return
    for pre, fill, node in RenderTree(tree):
        print(f"{pre}{node.name}")
"""