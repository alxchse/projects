import sys
# Author: Prof. Fitzsimmons
# Filename: words.py
#
# Description: Implementation of a search algorithm to find a
# shortest path of words from a given start word to a given
# goal word. At each step, any single letter in the word
# can be changed to any other letter, provided
# that the resulting word is also in the dictionary.
# 
# A dictionary of English words a text file, a start word,
# and a goal word are passed as command line arguments.
# 
# Usage: python3 words.py dictionaryFile startWord endWord

# Python queue implementation (https://docs.python.org/3.5/library/collections.html?highlight=deque#collections.deque)
from collections import deque

# Usage of deque: 
#   q = deque()   # declare new deque
#   q.append('A') # append A to the rear of the queue.
#   q.popleft()   # pop from the front of the queue.

class Node:
    def __init__(self, state, parent):
        self.state = state
        self.parent = parent

    # Nodes with the same state are viewed as equal
    def __eq__(self, other_node):
        return isinstance(other_node, Node) and self.state == other_node.state
    
    # Nodes with the same state hash to the same value
    # (e.g., when storing them in a set or dictionary)
    def __hash__(self):
        return hash(self.state)

def read_file(filename):
    """Read in each word from a dictionary where each
    word is listed on a single line."""
    print("Reading dictionary: " +filename)
    word_dict = set()
    dictionary = open(filename)
    # Read each word from the dictionary
    for word in dictionary:
        # Remove the trailing newline character
        word = word.rstrip('\n')
        # Convert to lowercase
        word = word.lower()
        word_dict.add(word)
    dictionary.close()
    return word_dict

def generate_newNodes(word, word_dict):
    
    newNodes = []                                                  # list to store valid newNodes
    word_list = list(word)                                          # convert word to list for swapping chars
    
    for i in range(len(word_list)):                                 # for each char in the word
        original_char = word_list[i]                                # store the original char
        for c in 'abcdefghijklmnopqrstuvwxyz':                      # try each letter of the alphabet
            if c != original_char:                  
                word_list[i] = c                                    # swap the char to a new char
                newNode = ''.join(word_list)                       # convert back to string
                if newNode in word_dict:                           # only add if the word is in the dictionary
                    newNodes.append(newNode)      
        word_list[i] = original_char                                # restore original character
    return newNodes 

def find_path(startWord, goalWord, word_dict):
    """Returns a list of words in word_dict
    that form the shortest path from startWord to goalWord,
    and returns None if no such path exists."""

    # BFS initialization
    start_node = Node(startWord, None)                              # create start node with start word and parent
    queue = deque([start_node])                                     # initialize queue with start node
    visited = set([startWord])                                      # set of visited words
    
    while queue:
        current_node = queue.popleft()

        if current_node.state == goalWord:                          # node state (word) matches goal word 
            path = []                                               # list to store the path
            node = current_node                                     # start from the goal node
            while node is not None:                                 # backtrack to construct the path
                path.append(node.state)                             # add the word to the path
                node = node.parent                                  # move up tree to the parent node
            return path[::-1]                                       # return reversed path from start to goal
        
        for newNode in generate_newNodes(current_node.state, word_dict): # generate valid new word nodes
            if newNode not in visited:                             # if new word has not been visited
                visited.add(newNode)                               # mark new word as visited
                newNode_node = Node(newNode, current_node)        # create new word
                queue.append(newNode_node)                         # add new word to the queue
    return None

def main():
    if len(sys.argv) != 4:
        print("Usage: python3 words.py dictionaryFile startWord goalWord")
    else:
        dictionaryFile = sys.argv[1]
        startWord = sys.argv[2]
        goalWord = sys.argv[3]

        word_dict = set()
        word_dict = read_file(dictionaryFile)

        if startWord not in word_dict:
            print(startWord + " is not in the given dictionary.")
        else:
            print("-- Shortest path from " + startWord + " to " + goalWord + " --")
            solutions = find_path(startWord, goalWord, word_dict)
            if(solutions is None):
                print("None exists!")
            else:
                for word in solutions:
                    print(word)

if __name__ == "__main__":
    main()
