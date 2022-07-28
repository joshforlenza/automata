# automata
/**
 * This program simulates the evolution of a group of cells over a number of generations.
 * 
 * It must be run two arguments: the number of generations 
 * and a text file that contains a 5x5 matrix of integers 0 and 1.
 * ex. ./automata.c 5 input.txt
 * 
 * In the text file the 0s represent dead cells and the 1s are alive cells.
 * These are rules that dictate whether a cell lives or dies in each generation:
 * 1) A live cell with fewer than two neighbors dies.
 * 2) A live cell with more than three neighbors dies.
 * 3) A live cell with exactly two or three neighbors lives
 * 4) A dead cell with exactly three live neighbors becomes alive
 * 
 * After the cells have evolved through the given number of generations,
 * an output text file is generated that contains the final generation.
 * 
 * @author Joshua Forlenza
