from parser.grammar import *
from queue import Queue
import pygraphviz as pgv

class Node:
    def __init__(self, val, children = None):
        self.val = val
        self.children = children

    def add_child(self, new_child):
        if not self.children:
            self.children = []
        self.children.insert(0, new_child)

    def print_children(self):
        children_str = ""
        if self.children:
            for child in self.children:
                children_str += child.val
        print(children_str)

    def __str__(self):
        return f"{self.val}"


def RenderTree(root):
    bfs = Queue()
    bfs.put((root, 0))
    G = pgv.AGraph(strict=False, directed=True)
    max_id = 0
    while not bfs.empty():
        curr = bfs.get()
        G.add_node(curr[1], label=curr[0])
        if curr[0].children:
            child_id = max_id + 1
            for child in curr[0].children:
                # añadimos el nodo y sus hijos al grafo
                bfs.put((child, child_id))
                G.add_node(child_id, label=child.val)
                # unimos al id del padre con el id del hijo
                G.add_edge(curr[1], child_id)
                child_id += 1
            max_id = child_id
    
    G.layout(prog = "dot")
    G.draw("parsing_tree.png")