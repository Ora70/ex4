This program finds the shortest path in a weighted matrix.
How to use:
The program recieves as an argument a port to listen on.
Once you connect to the server, send the values of the matrix, seperated by commas, and with '\n' at the end of every line.
Once you finished sending the matrix, send "end" and after that send 2 more lines, in each line 2 numbers split by a comma. The first line being the starting point in the search, and the second the finishing point.
The server will calculate the shortest path from start to end, using A star algorithm and send a string of the path to take (up/down/left/right), along with the price of the path to each square.
*In the matrux, the number -1 symbolizes a "wall"

Implementation:
The program implemented 4 search algorithms: A star, Best First Search, BFS, DFS, and chose A star as the best algorithm for searching.
The program saves the solved problems in files on the computer, so in the event of a new problem, it will first check if the problem was already solved, and if so, it will return the anser in the file and not run a search. If not - it will solve the problem and save the solution for future use.

The program can handle multiple clients in parallel.
