from sudoku_connections import SudokuConnections
from sudoku import Sudoku
import random

# define SudokuBoard class
class SudokuBoard : 

    # initialize class instance
    def __init__(self) : 

        # call getBoard() method to get the initial board state
        self.board = self.getBoard()

        # set exists attribute to True
        self.exists = True
        
        # create SudokuConnections instance to store the connections between the cells
        self.sudokuGraph = SudokuConnections()

        # call __getMappedMatrix() method to map cell IDs to their position in the matrix
        self.mappedGrid = self.__getMappedMatrix() 

    # define __getMappedMatrix() method to map cell IDs to their position in the matrix
    def __getMappedMatrix(self) : 
        
        # create a 16x16 matrix filled with zeros
        matrix = [[0 for cols in range(16)] for rows in range(16)]

        # initialize count to 1
        count = 1

        # loop through the rows and columns of the matrix
        for rows in range(16) : 
            for cols in range(16):
                # map the current cell ID to its position in the matrix
                matrix[rows][cols] = count
                count+=1

        # return the mapped matrix
        return matrix

    # define getBoard() method to generate a Sudoku board with a specified difficulty level
    def getBoard(self) :

        puzzle = Sudoku(4).difficulty(0.3)

        board = puzzle.board

        # initialize errorCase to False
        errorCase = False

        # prompt the user to enter a number
        num = int(input())

        # handle cases based on the user's input
        if(num == 1):
            errorCase = False
            
        elif(num == 2):
            errorCase = True

        else:
            # print an error message and exit the program if an invalid value is entered
            print("\nINVALID VALUE ENTERED, BYE!")
            exit()
            
        # if errorCase is True, randomly choose an integer between 1 and 9
        if(errorCase == True):
            random_integer = random.randint(1, 9)

            # set each cell on the main diagonal of the board to the randomly chosen integer,
            # THIS MAKES THE SUDOKU ILLEGAL!
            for i in range (15):
                board[i][i] = random_integer
                board[i][i+1] = random_integer
        
        # replace None values with 0
        for row in range (len(board)):
            for col in range (len(board[row])):
                if board[row][col] == None:
                    board[row][col] = 0

        # return the board state
        return board


    def printBoard(self) :

        dictionary = {10 : "A", 11 : "B", 12 : "C", 13 : "D", 14 : "E", 15 : "F", 16 : "G"}

        for i in range(len(self.board)) : 
            if i%4 == 0  :
                print("  - - - - - - - - - - - - - - - - - - - - - - - - ")

            for j in range(len(self.board[i])) : 
                if j %4 == 0 :
                    print(" |  ", end = "")
                if j == 15 :
                    if(self.board[i][j] >= 10):
                        print(dictionary[self.board[i][j]]," | ")
                    else:
                        print(self.board[i][j]," | ")
                        
                else :

                    if(self.board[i][j] >= 10):
                        print(f"{ dictionary[self.board[i][j]] } ", end = "")
                    else:
                        print(f"{ self.board[i][j] } ", end="")
        print("  - - - - - - - - - - - - - - - - - - - - - - - - ")

    def is_Blank(self):
        # Find the first blank cell in the Sudoku board.
        for row in range(len(self.board)):
            for col in range(len(self.board[row])):
                if self.board[row][col] == 0:
                    # Return the (row, col) coordinates of the blank cell.
                    return (row, col)
        # If there are no blank cells, return None.
        return None

    def graphColoringInitializeColor(self):
        """
        Fill in the already given colors.
        """
        # Create a list to hold the colors of each node in the graph.
        # The list is initialized with zeros, which represent no color.
        color = [0] * (self.sudokuGraph.graph.totalV + 1)
        # Create a list to hold the IDs of the nodes that have already been colored.
        given = []
        # Loop through each cell in the Sudoku board.
        for row in range(len(self.board)):
            for col in range(len(self.board[row])):
                if self.board[row][col] != 0:
                    # If the cell has a value, get the corresponding ID of the node in the graph.
                    idx = self.mappedGrid[row][col]
                    # Update the color of the node with the value of the cell.
                    color[idx] = self.board[row][col]
                    # Add the ID of the node to the list of given nodes.
                    given.append(idx)
        # Return the list of colors and the list of given node IDs.
        return color, given

    def solveGraphColoring(self, m=16):
        # Initialize the colors of the graph nodes using the given values in the Sudoku board.
        color, given = self.graphColoringInitializeColor()
        # Try to find a solution for the graph coloring problem using a backtracking algorithm.
        if self.__graphColorUtility(m=m, color=color, v=1, given=given) is None:
            # If no solution is found, set the exists flag to False, print a message, and return False.
            self.exists = False
            print("SORRY, NO SOLUTION EXISTS!")
            return False
        # If a solution is found, update the Sudoku board with the node colors and return the list of colors.
        count = 1
        for row in range(16):
            for col in range(16):
                self.board[row][col] = color[count]
                count += 1
        return color

    def __graphColorUtility(self, m, color, v, given):
        # This is a recursive function that tries to color the nodes in the graph starting with node v.
        # If a valid color is found for all nodes, the function returns True. Otherwise, it returns None.
        if v == self.sudokuGraph.graph.totalV + 1:
            # If all nodes have been colored, return True.
            return True
        for c in range(1, m+1):
            if self.__isSafe2Color(v, color, c, given) == True:
                # If color c is safe for node v, set the color of node v to c and move on to the next node.
                color[v] = c
                if self.__graphColorUtility(m, color, v+1, given):
                    # If a valid color is found for all nodes starting from node v+1, return True.
                    return True
            if v not in given:
                # If node v has not been colored yet, reset its color to zero.
                color[v] = 0


    def __isSafe2Color(self, v, color, c, given) : 
        
        if v in given and color[v] == c: 
            return True
        elif v in given : 
            return False

        for i in range(1, self.sudokuGraph.graph.totalV+1) :
            if color[i] == c and self.sudokuGraph.graph.isNeighbour(v, i) :
                return False
        return True

    
def main() :
    print('***WELCOME TO 16x16 RANDOM SUDOKO SOLVER***')
    print('PRESS\n1 - Generate a Valid Sudoku and Solve it\n2 - Generate an erraneous Sudoku and show that it cannot be solved\n\n')
    s = SudokuBoard()
    print("\n\nTHE RANDOM SUDOKU GENERATED IS:")
    print("\n\n")
    s.printBoard()
    print("\n\n\nSOLVING ...")
    print("\n\n")
    s.solveGraphColoring(m=16)
    if(s.exists):
        print("SOLUTION IS:\n")
        s.printBoard()

if __name__ == "__main__" : 
    main()
