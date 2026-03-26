# Alexandra Chase
# amchas26@g.holycross.edu
# CSCI 347 - Spring 2026
# Assignment 1 - BFS Swap Characters

from collections import deque


#   generate all valid NewNode nodes by changing one letter at a time
#   a NewNode is valid only if it exists in the word dictionary
def generate_NewNodes(word, word_dict):
    
    NewNodes = [] # list to store valid NewNodes
    word_list = list(word) # convert word to list for swapping chars
    
    for i in range(len(word_list)):                 # for each char in the word
        original_char = word_list[i]                # store the original char
        for c in 'abcdefghijklmnopqrstuvwxyz':      # try each letter of the alphabet
            if c != original_char:                  
                word_list[i] = c                    # change the char to a new char
                NewNode = ''.join(word_list)       # convert back to string
                if NewNode in word_dict:           # only add if the word is in the dictionary
                    NewNodes.append(NewNode)      
        word_list[i] = original_char                # restore original character
    return NewNodes 

def find_path(startWord, goalWord, word_dict):
    """Returns a tuple of (shortest_path_length, list_of_all_shortest_paths)
    that form the shortest path from startWord to goalWord, using BFS.
    Returns (None, []) if no such path exists."""
    
    # BFS initialization
    queue = deque([(startWord, [startWord])]) # BFS queue of (current_word, path_to_current)
    visited = set([startWord]) # set of visited words to avoid cycles
    solutions = [] # list to store all shortest paths
    shortest_length = None # track the length of the shortest path 
    
    while queue:  # while there are still nodes to explore
        current, path = queue.popleft()  # get the next node and path
        
        # If we've already found solutions, end loop if this path is longer
        if shortest_length is not None and len(path) > shortest_length:
            break
        
        if current == goalWord:  # if we found the goal word
            if shortest_length is None: # and if it is the first solution, record its length
                shortest_length = len(path)
            if len(path) == shortest_length: # add this path to solutions, if its of the shortest path
                solutions.append(path)
        else: 
            if shortest_length is None or len(path) < shortest_length: # only explore NewNodes if this path hasn't exceeded shortest length
                for NewNode in generate_NewNodes(current, word_dict): # generate valid NewNodes
                    if NewNode not in visited: # only explore unvisited NewNodes
                        visited.add(NewNode) # mark NewNode as visited
                        queue.append((NewNode, path + [NewNode])) # add NewNode and updated path to queue
    
    return (shortest_length, solutions)  # return tuple of (length, list of all shortest paths)