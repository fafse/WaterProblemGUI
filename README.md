# WaterProblemGUI
Task
Write a program which: 

reads from the standard input a size of the chessboard and heights of cuboids put on the fields,
computes maximal water volume, which may gather in puddles after the rain,
writes results in the standard output.
Input
The number of test cases t is in the first line of input, then t test cases follow separated by an empty line. In the first line of each test case two positive integers 1 <= n <= 100, 1 <= m <= 100 are written. They are the size of the mesh. In each of the following n lines there are m integers from the interval [1..10000]; i-th number in j-th line denotes a height of a cuboid given in inches put on the field in the i-th column and j-th raw of the chessboard.

Output
Your program should write for each tes case one integer equal to the maximal volume of water (given in cubic inches), which may gather in puddles on the construction. 

Example
Sample input:
1
3 6
3 3 4 4 4 2
3 1 3 2 1 4
7 3 1 6 4 1

Sample output:
5
