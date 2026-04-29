# Filename: rooks.py
# Author: Zack Fitzsimmons 
# Date: Fall 2020
#
# Description: Implementation of the nrooks problem to be
# solved using the Glucose3 SAT solver.

import sys
from pysat.solvers import Glucose3
from itertools import combinations

def main():
    if len(sys.argv) != 2:
        print('Usage: python3 rooks.py n')
        return

    n = int(sys.argv[1])
    # Create a variable for each square on the board.
    val = 1
    gridVariables = dict()
    for r in range(n):
        for c in range(n):
            gridVariables[(r,c)] = val
            val += 1

    phi = Glucose3()

# constraints for rooks: exactly one (at least one, at most one) rook per row AND per column
    
    # each row (y-value) must contain exactly one rook:
    for r in range(n):
        row_vars = [gridVariables[(r,c)] for c in range(n)]
        # at least one rook per row (R1,1 OR R1,2 OR ... OR R1,n)
        phi.add_clause(row_vars)
        # at most one rook (NOT R1,1 OR NOT R1,2) ... AND (NOT R1,n-1 OR NOT R1,n)
        # this is done by adding a clause for each pair of variables in the row, saying that they cannot both be true
        for v1, v2 in combinations(row_vars, 2): # combinations is a function from itertools that generates all pairs of variables in the row
            phi.add_clause([-v1, -v2]) 

    # each column (x-value) must contain exactly one (at least one, at most one) rook
    for c in range(n):
        col_vars = [gridVariables[(r,c)] for r in range(n)]
        # at least one rook per col (R1,1 OR R2,1 OR ... OR Rn,1)
        phi.add_clause(col_vars)
        # at most one rook (NOT R1,1 OR NOT R2,1) ... AND (NOT Rn-1,1 OR NOT Rn,1)
        # this is done the same way as for rows
        for v1, v2 in combinations(col_vars, 2):
            phi.add_clause([-v1, -v2])
            
    phi.solve()
    m = phi.get_model()
    print("Solution:")
    for r in range(n):
        for c in range(n):
            if(gridVariables[(r,c)] in m):
                print("R",end="")
            else:
                print(".",end="")
        print()
    print()

    count = 0
    for s in phi.enum_models():
        count +=1
    print("Total number of models: %d" %(count))


if __name__ == "__main__":
    main()

