"""Parse testing"""
import unittest

from parser.parse import *
import test_data
from parser.anyTree import RenderTree


class TestParse(unittest.TestCase):
    """Test parsing"""
    def test_ambiguous_grammar(self):
        """We are not accepting ambiguous grammars."""
        grammar = test_data.unsolved_left_factoring
        words = []
        with self.assertRaises(Warning):
            result = parse(grammar, words)
            assert result is None

    def test_success(self):
        """Test correct inputs."""
        grammar = test_data.book_example
        """list_inputs = [
            ["id"],
            ["id", "+", "id"],
            ["(", "id", "+", "id", ")", "*", "id"],
        ]"""
        list_inputs = [
            ["id"],
            ["id", "+", "id"],
            ["id", "*", "(", "id", "+", "id", ")"]
        ]
        for words in list_inputs:
            result, tree, errors = parse(grammar, words)
            print(result, errors)
            RenderTree(tree)
            assert result
            assert not errors

    def test_failed(self):
        """Test incorrect inputs."""
        grammar = test_data.book_example
        list_inputs_errors = [
            ([], ["Unexpected character:$. Expected: ['(', 'id']"]),
            (["+"], ["Unexpected character:+. Expected: ['(', 'id']"]),
            (["id", "+"], ["Unexpected character:$. Expected: ['(', 'id']"]),
            (["+", "id"], ["Unexpected character:+. Expected: ['(', 'id']"]),
            (["+", "id", ")"], ["Unexpected character:+. Expected: ['(', 'id']", 'Expected $']),
            (
                ["id", "+", "+", "id", "*", "*", "id"],
                ["Unexpected character:+. Expected: ['(', 'id']", "Unexpected character:*. Expected: ['(', 'id']"],
            )
        ]
        for words, error_list in list_inputs_errors:
            result, tree, errors = parse(grammar, words)
            assert not result
            assert errors == error_list



mytest = TestParse()
#mytest.test_ambiguous_grammar()
#mytest.test_failed()
mytest.test_success()


